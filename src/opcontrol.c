#include "main.h"

void operatorControl() {
	autonSelection = programSelected(8);

	while (1) {

		bool liftTooHigh = analogRead(6) < 800;
		bool liftTooLow = analogRead(6) > 3000;

		if(joystickGetDigital(1, 6, JOY_UP) && !liftTooHigh){
			dLift(false);
		}else if(joystickGetDigital(1, 6, JOY_DOWN) && !liftTooLow){
			dLift(true);
		}else{
			stopLift();
		}

		if(joystickGetDigital(1, 5, JOY_DOWN)){
			closeClaw(OFF);
		}else if(joystickGetDigital(1, 5, JOY_UP)){
			openClaw();
		}

		analogDrive();

		delay(20);
	}
}
