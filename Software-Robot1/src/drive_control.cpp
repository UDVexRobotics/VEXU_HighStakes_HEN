#include "drive_control.h"

void dual_stick_drive(void){

    // Controls for Up-Down and Left-Right movement
    float leftStick = (float)(primary_controller.Axis3.position() / 100.0);             // Vertical Movement
    float rightStick = primary_controller.Axis1.position() / (float)-100.0;            // Horizontal Movement
   
    
    // Motor speed percentage based on cubed function
    float ySpeed = pow(leftStick, 3);
    float xSpeed = pow(rightStick /*TURN_SPEED_RATIO*/, 3);

    //if(controller.buttonL2.pressing()):
        //xSpeed = (rightAxis_LR * SHIFT_TURN_SPEED_RATIO) ** 3

    
    if(fabs(ySpeed) > 0.05 or fabs(xSpeed) > 0.05){
        //Set the velocity depending on the axis position
        left_motor_group.setVelocity((ySpeed + xSpeed) * 100,vex::percentUnits::pct);
        right_motor_group.setVelocity((ySpeed - xSpeed) * 100,vex::percentUnits::pct); 

        left_motor_group.spin(vex::forward);
        right_motor_group.spin(vex::forward);

    }
    else {
        left_motor_group.stop(vex::coast);
        right_motor_group.stop(vex::coast);
    }

    return;
}

void tank_drive(void){
    // Controls for Up-Down and Left-Right movement
    float rightStick = (primary_controller.Axis3.position() / (float)100.0);             // Vertical Movement
    float leftStick = (primary_controller.Axis2.position() / (float)100.0);            // Horizontal Movement
   
    // Motor speed percentage based on cubed function
    float leftSpeed = pow(leftStick, 3);
    float rightSpeed = pow(rightStick, 3);

    if(fabs(leftSpeed) > 0.05){
        //Set the velocity depending on the axis position
        left_motor_group.setVelocity(leftSpeed * 100,vex::percentUnits::pct);
        left_motor_group.spin(vex::forward);
    }
    else{
        left_motor_group.stop(vex::coast);
    }

    if(fabs(rightSpeed) > 0.05){
        right_motor_group.setVelocity(rightSpeed * 100,vex::percentUnits::pct); 
        right_motor_group.spin(vex::forward);
    }
    else{
        right_motor_group.stop(vex::coast);

    }  

}
