#include "auto_control.h"
#include <iostream>
// PID Control
double PIDControl(double target, double position){
    return (target - position) * KP;
}

void rotateTo(double target) {
    vex::timer timer = vex::timer();

    bool is_negative = (target < 0);
    double magnitude = fabs(target);
    double avg_pos = 0;
    
    left_motor_group.setPosition(0, vex::degrees);
    right_motor_group.setPosition(0, vex::degrees);

    timer.reset();
    double start_time = timer.value();

    // PID Loop
    while (!(avg_pos <= target && avg_pos >= target - 1)) {
        
        double left_pos = fabs(left_motor_group.position(vex::degrees));
        double right_pos = fabs(right_motor_group.position(vex::degrees));
        avg_pos = (left_pos + right_pos) / 2.0;
        double drive = PIDControl(target, avg_pos);
        std::cout<<"L: "<<left_motor_group.position(vex::degrees)<<" R: "<<right_pos<<" t: "<<avg_pos<<std::endl;
        // Clamp voltage to min and max 
        drive = (drive < MINVOLTAGE && drive > 0) ? MINVOLTAGE : drive;
        drive = (drive > -MINVOLTAGE && drive < 0) ? -MINVOLTAGE : drive;

        if (drive < MAXVOLTAGE) {
            drive = MAXVOLTAGE;
        } else if (drive < -MAXVOLTAGE) {
            drive = -MAXVOLTAGE;
        }
        
        double left_drive = drive;
        double right_drive = drive;

        if (left_pos > right_pos) {
            left_drive += (right_pos - left_pos) * LR_KP;
        } else {
            right_drive += (left_pos - right_pos) * LR_KP;
        }

        if (is_negative) { 
            left_motor_group.spin(vex::forward, -left_drive, vex::voltageUnits::volt); // Reversed
            right_motor_group.spin(vex::forward, right_drive, vex::voltageUnits::volt);
        } else {
            left_motor_group.spin(vex::forward, left_drive, vex::voltageUnits::volt);
            right_motor_group.spin(vex::forward, -right_drive, vex::voltageUnits::volt); // Reversed
        } 
        if ((timer.value() - start_time) > TIMEOUT_TIME) {
            break;
        }
    }

    left_motor_group.stop();
    right_motor_group.stop();
}

void driveForward(int tiles){
    int t = (int)(tiles * (TILEREVOLUTIONS(MANUAL_OFFSET)) * 360.0);
    //std::cout<<((TILEREVOLUTIONS(MANUAL_OFFSET)) * 360.0)<<std::endl;
    //std::cout<<TILEREVOLUTIONS(MANUAL_OFFSET)<<std::endl;
    //std::cout<<"Target: "<<t<<std::endl;
    float avg_position = 0;

    left_motor_group.setPosition(0, vex::degrees);
    right_motor_group.setPosition(0, vex::degrees);

    uint32_t start_time = Brain.Timer.time();
    std::cout<<"driveForward"<<std::endl;
    while(!(t+1 > avg_position && avg_position > t-1)){
        double left_position = left_motor_group.position(vex::rotationUnits::deg);
        double right_position = right_motor_group.position(vex::rotationUnits::deg);
        avg_position = (left_position + right_position) / 2;
        double drive = PIDControl(t, avg_position); // Calculate the drive value

        std::cout<<"L: "<<left_motor_group.position(vex::rotationUnits::deg)<<" R: "<<right_position<<" t: "<<avg_position<<std::endl;

        // Don't allow drive to go below minimum voltage (speed)
        drive = (drive < MINVOLTAGE && drive > 0) ? MINVOLTAGE : drive;
        drive = (drive > -MINVOLTAGE && drive < 0) ? -MINVOLTAGE : drive;

        if (drive > MAXVOLTAGE) {
            drive = MAXVOLTAGE;
        } else if (drive < -MAXVOLTAGE) {
            drive = -MAXVOLTAGE;
        }

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
