#include "vision.h"

// Vision Sensor Thread
int vision_sensor_thread() {

    vSens.setBrightness((uint8_t) 50);
    while (true) {
        // Check if Button A is pressed to toggle vision state
        if(SWITCH_COLOR_FILTERING) {
            // Cycle through the states: RED -> BLUE -> OFF -> RED
            currentState = static_cast<VisionState>((currentState + 1) % 3);

            // Wait a short period to prevent multiple toggles
            vex::this_thread::sleep_for(200);
        }

        // Take a snapshot if vision is active
        if (currentState != OFF) vSens.takeSnapshot(currentState == RED ? CUS_RED : CUS_BLUE);

        // Display the current status on the screen
        // Check if an object is detected
        if (vSens.objects[0].exists) {
            // TODO: Add code to eject ring
            color_detected = true;
            vex::this_thread::sleep_for(250);
            //std::cout<<"Color Detected!"<<std::endl;
        }
        else{
            color_detected = false;
        }

        vex::this_thread::sleep_for(50); 
    }
}

