/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       University of Delaware Team 1                             */
/*    Created:      5/17/2024, 2:33:21 PM                                     */
/*    Description:  Software for Robot HEN of UD's VEXU Team                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "main.h"

// Actuator Control
bool actuatorToggle = false;
void actuator_thread(void){
    while(true){
        if(ACTUATOR_TOGGLE_BUTTON){
            (actuatorToggle) ? Actuator.set(false) : Actuator.set(true);
            actuatorToggle = !actuatorToggle;
            this_thread::sleep_for(250);
        }
        this_thread::sleep_for(20);
    }
}

void highstake_motor_thread(void){
    while (true) { 
        if (HIGHSTAKE_WALL_POSITION) {
            highstake_motor.spinToPosition(-323, rotationUnits::deg, 75, velocityUnits::pct);
            highstake_motor.stop(vex::brakeType::hold);
        } else if (HIGHSTAKE_BELT_POSITION) {
            highstake_motor.spinToPosition(-78, rotationUnits::deg, 100, velocityUnits::pct);
            highstake_motor.stop(vex::brakeType::hold);
        } else if (HIGHSTAKES_FORWARD_MOTOR_BUTTON) {
            highstake_motor.setVelocity(20, vex::percentUnits::pct);
            highstake_motor.spin(forward);
        } else if (HIGHSTAKES_BACKWARD_MOTOR_BUTTON) {
            highstake_motor.setVelocity(-20, vex::percentUnits::pct);
            highstake_motor.spin(forward);
        } else {
            highstake_motor.stop(vex::brakeType::hold);
        }
        this_thread::sleep_for(20);
    }
}

int delayed_actuator_toggle(void *params){
    uint32_t* delay = static_cast<uint32_t*>(params);
    this_thread::sleep_for(*delay);
    (actuatorToggle) ? Actuator.set(false) : Actuator.set(true);
    actuatorToggle = !actuatorToggle;
    return 0;
}

// Code block for Pre-Autonomous 
void pre_auton(void) {
    //Brain.Screen.print("Pre-Autonomous start!");
    //Brain.Screen.newLine();


    // All activities that occur before the competition starts
    //Brain.Screen.print("Pre-Autonomous complete.");
    //Brain.Screen.newLine();
}

const float ROTATION_FACTOR = 6.98;
const int MOTOR_SPEED = 100;

// Helper function to clear belt jams
void unJamBelt() {
    belt_motor.setVelocity(MOTOR_SPEED, vex::percentUnits::pct);
    belt_motor.spin(forward);
    wait(500, msec);
    
    belt_motor.setVelocity(-MOTOR_SPEED, vex::percentUnits::pct);
    belt_motor.spin(forward);
}

// Helper function to start both the intake and belt for ring collection
void startRingIntake() {
    intake_motor.setVelocity(-MOTOR_SPEED, vex::percentUnits::pct);
    intake_motor.spin(forward);
    
    belt_motor.setVelocity(-MOTOR_SPEED, vex::percentUnits::pct);
    belt_motor.spin(forward);
}

// Autonomous routine
void autonomous(void) {

    auto start_time = std::chrono::steady_clock::now();

    // === Mobile Goal 1 ===
    driveForward(.73);
    rotateTo(45 * ROTATION_FACTOR);
    uint32_t delay = 600;
    task delayTask(delayed_actuator_toggle, (void *)&delay); // Grab Mobile Goal
    driveForward(0.73);
    wait(200, msec);
    
    // === Ring 1 ===
    rotateTo(135 * ROTATION_FACTOR);
    startRingIntake();
    driveForward(-0.68);
    
    // === Rings 2 & 3 ===
    rotateTo(-140 * ROTATION_FACTOR);
    unJamBelt();
    driveForward(-2.45);
    unJamBelt();
    
    // === Ring 4 ===
    rotateTo(-138 * ROTATION_FACTOR);
    driveForward(-1.78);
    unJamBelt();
    
    // === Ring 5 and mobile goal in corner ===
    rotateTo(30 * ROTATION_FACTOR);
    driveForward(-.85);
    unJamBelt();
    driveForward(0.25);
    rotateTo(180 * ROTATION_FACTOR);
    driveForward(0.25);
    unJamBelt();
    
    // Stop ring intake and reset actuator
    Actuator.set(false);
    wait(200, msec);
    intake_motor.stop(brake);
    belt_motor.stop(brake);

    // === Mobile Goal 2 ===
    driveForward(-0.85);
    rotateTo(-125 * ROTATION_FACTOR);
    driveForward(-1);
    driveForward(2.5);
    rotateTo(-30 * ROTATION_FACTOR);
    driveForward(1.40);
    Actuator.set(true);
    wait(300, msec);
    
    // === Ring 1 ===
    rotateTo(-134 * ROTATION_FACTOR);
    startRingIntake();
    driveForward(-.45);

    // === Ring 2 ===
    rotateTo(110 * ROTATION_FACTOR);
    unJamBelt();
    driveForward(-1.2);

    // === Ring 3 ===
    rotateTo(-125 * ROTATION_FACTOR);
    unJamBelt();
    driveForward(-.9);

    // === Ring 4 and obile goal in corner ===
    rotateTo(35 * ROTATION_FACTOR);
    driveForward(-.8);
    driveForward(0.3);
    rotateTo(178 * ROTATION_FACTOR);
    unJamBelt();
    driveForward(0.55);
    belt_motor.setVelocity(MOTOR_SPEED, vex::percentUnits::pct);
    belt_motor.spin(forward);
    Actuator.set(false);
    wait(300, msec);
    startRingIntake();

    // Stop ring intake and reset actuator
    driveForward(-0.3);
    intake_motor.stop(brake);
    belt_motor.stop(brake);

    rotateTo(-125 * ROTATION_FACTOR);
    driveForward(-1);
    driveForward(2.3);
    Actuator.set(true);
    wait(200, msec);
    rotateTo(180 * ROTATION_FACTOR);
    startRingIntake();
    driveForward(-.7);
    rotateTo(130 * ROTATION_FACTOR);
    wait(600, msec);
    intake_motor.stop(brake);
    belt_motor.stop(brake);
    // driveForward(2);
    // Actuator.set(false);
    // wait(200, msec);
    // driveForward(-0.5);

    auto end_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - start_time;
    
    std::cout << "Autonomous complete in " 
              << elapsed_seconds.count() << " seconds" << std::endl;
}

void set_up_highstate_motor(){
    highstake_motor.setStopping(vex::brakeType::hold);
    highstake_motor.stop(vex::brakeType::hold);
    highstake_motor.setPosition(0, rotationUnits::deg);
}

// Code block for User Control
void usercontrol(void) { 
    // Usercontrol loopdriveForward(.8);

    set_up_highstate_motor();
    while(true){
        if(INTAKE_FORWARD_BUTTON && !INTAKE_REVERSE_BUTTON){
            intake_motor.setVelocity(-100, vex::percentUnits::pct);
            intake_motor.spin(forward);
        }
        else if(INTAKE_REVERSE_BUTTON && !INTAKE_FORWARD_BUTTON){
            intake_motor.setVelocity(100, vex::percentUnits::pct);
            intake_motor.spin(forward); 
        }
        else{
            intake_motor.stop(brake);
        }

        if(abs(BELT_CONTROL) > 0){
            belt_motor.setVelocity(-BELT_CONTROL, vex::percentUnits::pct);
            belt_motor.spin(forward);
        }
        else{
            belt_motor.stop(brake);
        }

        // if(HIGHSTAKE_WALL_POSITION){
        //     highstake_motor.spinToPosition(-323, rotationUnits::deg, 75, velocityUnits::pct);
        //     highstake_motor.stop(vex::brakeType::hold);
        // }
        // else if(HIGHSTAKE_BELT_POSITION){
        //     highstake_motor.spinToPosition(-78, rotationUnits::deg, 100, velocityUnits::pct);
        //     highstake_motor.stop(vex::brakeType::hold);
        // }
        // else if(HIGHSTAKES_FORWARD_MOTOR_BUTTON){
        //     highstake_motor.setVelocity(20, vex::percentUnits::pct);
        //     highstake_motor.spin(forward);
        // }
        // else if(HIGHSTAKES_BACKWARD_MOTOR_BUTTON){
        //     highstake_motor.setVelocity(-20, vex::percentUnits::pct);
        //     highstake_motor.spin(forward);
        // }
        // else{
        //     highstake_motor.stop(vex::brakeType::hold);
        // }

        if(SWITCH_DRIVE_TANK)
            currentDriveMode = TANK;
        else if(SWITCH_DRIVE_DUAL)
            currentDriveMode = DUAL_STICK;

        switch (currentDriveMode){
            case TANK:
                tank_drive();
                break;
            case DUAL_STICK:
                dual_stick_drive();
                break;
        }

        this_thread::sleep_for(10);
    }
}

int main() {
    // Set up callbacks for autonomous and driver control periods.
    compete.autonomous(autonomous);
    compete.drivercontrol(usercontrol);

    primary_controller.ButtonR1.pressed(intake_toggle);
    //primary_controller.ButtonL1.pressed(belt_toggle_on);
    //primary_controller.ButtonL2.pressed(belt_toggle_off);

    thread display_Status = thread(displayStatus);
    thread actuatorThread = thread(actuator_thread);
    thread visionThread = thread(vision_sensor_thread);
    thread highstakeThread = thread(highstake_motor_thread);

    // Run the pre-autonomous function.
    pre_auton();

    // Prevent main from exiting with an infinite loop.
    while (true) {
        // Allow other tasks to run
        this_thread::sleep_for(10);
    }
}