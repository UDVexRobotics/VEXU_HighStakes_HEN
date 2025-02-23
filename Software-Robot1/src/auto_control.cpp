#include "auto_control.h"
#include <iostream>
// PID Control
double PIDControl(double target, double position){
    return (target - position) * KP;
}


void rotateTo(double target) {
    bool is_negative = (target < 0); // Check if the target is negative (counter-clockwise vs clockwise)
    target = fabs(target);
    double avg_pos = 0;
    
    left_motor_group.setPosition(0, vex::degrees);
    right_motor_group.setPosition(0, vex::degrees);

    uint32_t start_time = Brain.Timer.time();

    // PID Loop
    while (!(target+1 > avg_pos && avg_pos > target-1)) {
        vex::this_thread::sleep_for(20); // Sleep for 20 milliseconds

        double left_pos = fabs(left_motor_group.position(vex::degrees));
        double right_pos = fabs(right_motor_group.position(vex::degrees));
        avg_pos = (left_pos + right_pos) / 2.0;
        double drive = PIDControl(target, avg_pos);
        std::cout<<"Avg: "<<avg_pos<<" target: "<<target<<" drive: "<<drive<<std::endl;

        // Clamp voltage to min and max 
        drive = (drive < MINVOLTAGE && drive > 0) ? MINVOLTAGE : drive; // Don't allow drive to go below minimum voltage (+speed)
        drive = (drive > -MINVOLTAGE && drive < 0) ? -MINVOLTAGE : drive; // Don't allow drive to go below minimum voltage (-speed)

        drive = (drive > MAXVOLTAGE) ? MAXVOLTAGE : drive; // Don't allow drive to go above maximum voltage (+speed)
        drive = (drive < -MAXVOLTAGE) ? -MAXVOLTAGE : drive; // Don't allow drive to go below maximum voltage (-speed)

        double left_drive = drive;
        double right_drive = drive;

        // Correct the drive values between the left and right motors (Fix Off-balanced drive)
        if (left_pos > right_pos) {
            left_drive += (right_pos - left_pos) * LR_KP;
        } else {
            right_drive += (left_pos - right_pos) * LR_KP;
        }

        // If the target is negative, turn counter-clockwise
        if (is_negative) { 
            left_motor_group.spin(vex::forward, -left_drive, vex::voltageUnits::volt); // Reversed
            right_motor_group.spin(vex::forward, right_drive, vex::voltageUnits::volt);
        }else {
            std::cout<<"Left: "<<left_drive<<" Right: "<<right_drive<<std::endl;
            left_motor_group.spin(vex::forward, left_drive, vex::voltageUnits::volt);
            right_motor_group.spin(vex::forward, -right_drive, vex::voltageUnits::volt); // Reversed
        }

        uint32_t elapsed_time = Brain.Timer.time() - start_time;
        if (elapsed_time > TIMEOUT_TIME) {
            std::cout<<"Timeout"<<std::endl;
            //break;
        }
    }
    std::cout<<"Done"<<std::endl;
    left_motor_group.stop(vex::brakeType::brake);
    right_motor_group.stop(vex::brakeType::brake);
}

void driveForward(int tiles){
    int t = (int)(tiles * (TILEREVOLUTIONS(MANUAL_OFFSET)) * 360.0); // Convert tiles to degrees
    float avg_position = 0;

    // Reset the motor positions
    left_motor_group.setPosition(0, vex::degrees);
    right_motor_group.setPosition(0, vex::degrees);

    uint32_t start_time = Brain.Timer.time();
    
    while(!(t+1 > avg_position && avg_position > t-1)){
        vex::this_thread::sleep_for(20);
        double left_position = left_motor_group.position(vex::degrees);
        double right_position = right_motor_group.position(vex::degrees);
        avg_position = (left_position + right_position) / 2;
        double drive = PIDControl(t, avg_position); // Calculate the drive value

        std::cout<<"Avg: "<<avg_position<<"target: "<<t<<std::endl;

        // Don't allow drive to go below minimum voltage (speed)
        drive = (drive < MINVOLTAGE && drive > 0) ? MINVOLTAGE : drive;
        drive = (drive > -MINVOLTAGE && drive < 0) ? -MINVOLTAGE : drive;

        // Don't allow drive to go above maximum voltage (speed)
        drive = (drive > MAXVOLTAGE) ? MAXVOLTAGE : drive;
        drive = (drive < -MAXVOLTAGE) ? -MAXVOLTAGE : drive;


        // P-Control between left and right motors
        double left_voltage_drive = drive;
        double right_voltage_drive = drive;

        // Set the motor voltages
        left_motor_group.spin(vex::forward, left_voltage_drive, vex::voltageUnits::volt);
        right_motor_group.spin(vex::forward, right_voltage_drive, vex::voltageUnits::volt);
        
        uint32_t elapsed_time = Brain.Timer.time() - start_time;
        if(elapsed_time > TIMEOUT_TIME)
            break; // Break if the command takes too long

    }

    // Stop the motors
    left_motor_group.stop(vex::brakeType::brake);
    right_motor_group.stop(vex::brakeType::brake);

    return;
}

