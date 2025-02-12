#ifndef MAIN_H
#define MAIN_H
#include "vex.h"

// Global Constants
// Make sure to define a motor with the right gear ratio (motor gear color)
const vex::gearSetting RED_GEAR = vex::ratio36_1; // 100 RPM - high torque & low speed (e.g. lifting arms & moving claws,)
const vex::gearSetting GREEN_GEAR = vex::ratio18_1; // 200 RPM - standard gear ratio for drivetrain applications 
const vex::gearSetting BLUE_GEAR = vex::ratio6_1; // 600 RPM - low torque & high speed (e.g.  intake rollers & flywheels))

vex::brain Brain;
vex::controller primary_controller;
vex::motor belt_motor = vex::motor(vex::PORT16, BLUE_GEAR, false); // BLUE_GEAR ratio

volatile bool belt_toggle_state = false;
volatile bool reverse_belt = false;
bool color_detected = true;

#endif