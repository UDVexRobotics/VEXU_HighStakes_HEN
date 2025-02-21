#ifndef VISION_H
#define VISION_H

#include "vex.h"

enum VisionState { RED, BLUE, OFF};

// External variable definitions
extern volatile bool color_detected;
extern vex::controller primary_controller;
extern vex::controller secondary_controller;
extern vex::vision vSens;
extern vex::vision::signature CUS_RED;
extern vex::vision::signature CUS_BLUE;
extern VisionState currentState;


// Button Mapping
#define SWITCH_COLOR_FILTERING primary_controller.ButtonA.pressing()

// Function prototypes
int vision_sensor_thread(void);

#endif // VISION_H