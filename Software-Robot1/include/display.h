#ifndef DISPLAY_H
#define DISPLAY_H

#include "vex.h"
#include "vision.h"
#include <iostream>
#include <sstream>
#include <iomanip>


enum driveMode{ TANK, DUAL_STICK};

extern VisionState currentState;
extern driveMode currentDriveMode;
extern vex::motor belt_motor;
extern vex::controller primary_controller;
extern vex::controller secondary_controller;
extern vex::brain Brain;



std::string format_decimal_places(double value, int decimal_places);
void displayStatus(void);

#endif // DISPLAY_H

