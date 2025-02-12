#ifndef CONVEYORBELT_H
#define CONVEYORBELT_H

#include <iostream>
#include "vex.h"
#include "main.h"

using namespace vex;

#define BELT_THROW_POSITION 638 // (DEPRECATED) Farthest Number of Degrees from starting position needed to throw ring (No more than 1 revolution around BELT)
#define BELTRANGE 10 // Margin of error around throw position
#define BELTSPEED -100 // Speed of belt motor

extern vex::brain Brain;
extern vex::controller primary_controller;
extern vex::motor belt_motor;

extern volatile bool belt_toggle_state;
extern volatile bool reverse_belt;
extern volatile bool belt_toggle_state;
extern bool color_detected;

class ConveyorBelt {
public:
    

    ConveyorBelt();
    void belt_toggle_on(void);
    void belt_toggle_off(void);
    void belt_control(void);

};


#endif