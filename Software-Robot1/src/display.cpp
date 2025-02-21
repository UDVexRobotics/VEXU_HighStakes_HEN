#include "display.h"

std::string format_decimal_places(double value, int places) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(places) << value;
    return ss.str();
}

// Function to display the current status on the brain screen
void displayStatus() {
    while(true){
        primary_controller.Screen.clearScreen();
        secondary_controller.Screen.clearScreen();

        primary_controller.Screen.setCursor(1, 18);
        secondary_controller.Screen.setCursor(1, 18);

        switch (currentState) {
            case RED:
                Brain.Screen.clearScreen(vex::red);
                Brain.Screen.drawCircle(240, 136, 110, vex::black);
                Brain.Screen.drawCircle(240, 136, 100, vex::blue);
                Brain.Screen.drawCircle(240, 136, 60, vex::black);
                Brain.Screen.drawCircle(240, 136, 50, vex::red);
                
                primary_controller.Screen.print("RED\n");
                secondary_controller.Screen.print("RED\n");
                
                break;
            case BLUE:
                Brain.Screen.clearScreen(vex::blue);
                Brain.Screen.drawCircle(240, 136, 110, vex::black);
                Brain.Screen.drawCircle(240, 136, 100, vex::red);
                Brain.Screen.drawCircle(240, 136, 60, vex::black);
                Brain.Screen.drawCircle(240, 136, 50, vex::blue);
                
                primary_controller.Screen.print("BLU\n");
                secondary_controller.Screen.print("BLU\n");

                
                break;
            case OFF:
                Brain.Screen.clearScreen(vex::black);
                Brain.Screen.drawCircle(240, 136, 110, vex::white);
                Brain.Screen.drawCircle(240, 136, 100, vex::purple);
                Brain.Screen.drawCircle(240, 136, 60, vex::white);
                Brain.Screen.drawCircle(240, 136, 50, vex::black);
                
                primary_controller.Screen.print("OFF\n");
                secondary_controller.Screen.print("OFF\n");
                
                break;
            return; 
        }
        
        primary_controller.Screen.setCursor(1, 1);
        secondary_controller.Screen.setCursor(1, 1);

        switch (currentDriveMode){
            case TANK:
                primary_controller.Screen.print("DRIVE: TANK\n");
                secondary_controller.Screen.print("DRIVE: TANK\n");
                break;
            case DUAL_STICK:
                primary_controller.Screen.print("DRIVE: DUAL\n");
                secondary_controller.Screen.print("DRIVE: DUAL\n");
                break;
        }

        double belt_motor_temp = belt_motor.temperature(vex::temperatureUnits::celsius);
        std::string belt_status = "BELT MTR TMP: " + format_decimal_places(belt_motor_temp, 1);
        double battery_soc = Brain.Battery.capacity();
        std::string battery_status = "BAT: " + format_decimal_places(battery_soc, 1);

        primary_controller.Screen.setCursor(2, 1);
        secondary_controller.Screen.setCursor(2, 1);
        primary_controller.Screen.print(belt_status.c_str());
        secondary_controller.Screen.print(belt_status.c_str());

        primary_controller.Screen.setCursor(3, 1);
        secondary_controller.Screen.setCursor(3, 1);
        primary_controller.Screen.print(battery_status.c_str());
        secondary_controller.Screen.print(battery_status.c_str());
        vex::this_thread::sleep_for(100);
    }
}