#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include "vex.h"
#include <math.h>
#include "vision.h"
#include "display.h"
#include "belt_control.h"
#include "drive_control.h"
#include "auto_control.h"

using namespace vex;


// Definitions
#define TURN_SPEED_RATIO 0.5




// Button Mapping
#define ACTUATOR_TOGGLE_BUTTON primary_controller.ButtonR1.pressing()
#define BELT_A (secondary_controller.ButtonA.pressing())
#define INTAKE_FORWARD_BUTTON secondary_controller.ButtonR2.pressing()
#define INTAKE_REVERSE_BUTTON secondary_controller.ButtonR1.pressing()
#define REVERSE_BELT_BUTTON secondary_controller.ButtonY.pressing()
#define SWITCH_DRIVE_TANK primary_controller.ButtonUp.pressing()
#define SWITCH_DRIVE_DUAL primary_controller.ButtonDown.pressing()
#define HIGHSTAKES_FORWARD_MOTOR_BUTTON secondary_controller.ButtonL2.pressing()
#define HIGHSTAKES_BACKWARD_MOTOR_BUTTON secondary_controller.ButtonL1.pressing()
#define BELT_CONTROL secondary_controller.Axis2.position()
#define BELT_C secondary_controller.Axis2.position()

// TODO: BUTTON MAP, TOGGLE BELT ON ONE BUTTON, REVERSE BELT ON ANOTHER BUTTON, INTAKE STAY BACK AND FORTH, TRIGGER FOR ACTUATOR

// Global Constants-+
// Make sure to define a motor with the right gear ratio (motor gear color)
const gearSetting RED_GEAR = ratio36_1; // 100 RPM - high torque & low speed (e.g. lifting arms & moving claws,)
const gearSetting GREEN_GEAR = ratio18_1; // 200 RPM - standard gear ratio for drivetrain applications 
const gearSetting BLUE_GEAR = ratio6_1; // 600 RPM - low torque & high speed (e.g.  intake rollers & flywheels))

// A global instance of vex::brain
vex::brain Brain;

// Global instance of competition
competition compete;
// Global instance of controller
controller primary_controller = controller(primary);
controller secondary_controller = controller(partner);

// define your global instances of motors and other devices here
motor left_motor_front = motor(PORT17, BLUE_GEAR, false);
motor left_motor_mid = motor(PORT14, BLUE_GEAR, false);
motor left_motor_back = motor(PORT10, BLUE_GEAR, false);
motor_group left_motor_group = motor_group(left_motor_front, left_motor_mid, left_motor_back);

motor right_motor_front = motor(PORT15, BLUE_GEAR, true);
motor right_motor_mid = motor(PORT8, BLUE_GEAR, true);
motor right_motor_back = motor(PORT9, BLUE_GEAR, true);
motor_group right_motor_group = motor_group(right_motor_front, right_motor_mid, right_motor_back);

motor intake_motor = motor(PORT13, GREEN_GEAR, false);
motor belt_motor = motor(PORT16, BLUE_GEAR, false);
motor highstake_motor = motor(PORT5, RED_GEAR, false);

digital_out Actuator = digital_out(Brain.ThreeWirePort.H);


// Vision Sensor Definitions
vex::vision::signature CUS_BLUE = vex::vision::signature(7, -4767, -3699, -4233, 6899, 8623, 7761, 3.2, 0);
vex::vision::signature CUS_RED = vex::vision::signature(6, 8849, 11299, 10074, -1761, -911, -1336, 1.9, 0);
vision vSens = vision(PORT20, 50, CUS_RED, CUS_BLUE);
VisionState currentState = RED;

driveMode currentDriveMode = DUAL_STICK;

// Global Variables
volatile bool belt_toggle_state = false;
volatile bool color_detected = true; // TODO: Set up control to vision sensor
volatile bool reverse_belt = false;

#endif // MAIN_H