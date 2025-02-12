#include "conveyorbelt.h"


static void belt_toggle_on(void){
    std::cout<<"Belt Toggle On"<<std::endl;
    belt_toggle_state = true;
}

static void belt_toggle_off(void){
    std::cout<<"Belt Toggle Off"<<std::endl;
    belt_toggle_state = false;
}

static void belt_control(void){
    while(true){
        int belt_position = abs((((int)belt_motor.position(vex::rotationUnits::deg)) % BELT_THROW_POSITION));
        //Brain.Screen.printAt(1, 150, "Belt Position: %6d", belt_position);
        //belt_motor.position(vex::rotationUnits::deg);

        if(color_detected){
            wait(0.15, sec); // Wait until at peak
            std::cout<<"Ejecting Ring!"<<std::endl;
            belt_motor.stop(vex::brakeType::brake); // Briefly stop
            wait(0.45, sec);
            //belt_motor.setVelocity(BELTSPEED, vex::percentUnits::pct);
            belt_motor.spin(forward);
            wait(0.7, sec);
    }

    if(belt_toggle_state){
        if(reverse_belt)
            belt_motor.setVelocity(-BELTSPEED, vex::percentUnits::pct);
        else
            belt_motor.setVelocity(BELTSPEED, vex::percentUnits::pct);
        
        belt_motor.spin(forward);  
    }
    else{
        belt_motor.stop(brake);
    }


    }
}