#ifndef BELT_CONTROL_H
#define BELT_CONTROL_H

#include "vex.h"
using namespace vex;

#define BELT_THROW_POSITION 638 // Farthest Number of Degrees from starting position needed to throw ring (No more than 1 revolution around BELT)
#define BELTRANGE 10 // Margin of error around throw position
#define BELTSPEED -100 // Speed of belt motor



extern volatile bool belt_toggle_state;
extern vex::motor belt_motor;
extern volatile bool color_detected;
extern volatile bool reverse_belt;
extern vex::controller secondary_controller;

#define BELT_TOGGLE_BUTTON secondary_controller.ButtonX.pressing()

void intake_toggle(void);
void belt_toggle_on(void);
void belt_toggle_off(void);
void belt_control(void);

#endif // BELT_CONTROL_H