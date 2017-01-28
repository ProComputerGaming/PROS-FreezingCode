#include "main.h"

void operatorControl() {
	autonSelection = programSelected(8);
	delay(500);

	while (1) {
		autonSelection = programSelected(8);

		lcdSetText(uart2, 1, "Auton Selection:");
		lcdPrint(uart2, 2, "%lu", millis());
		delay(500);

		int liftPotValue = analogRead(liftPot);
		bool liftTooHigh = liftPotValue < 800;
		bool liftTooLow = liftPotValue > 3100;

		if(joystickGetDigital(1, 6, JOY_UP) && !liftTooHigh){
			dLift(false);
		}else if(joystickGetDigital(1, 6, JOY_DOWN) && !liftTooLow){
			dLift(true);
		}else if(joystickGetDigital(1, 8, JOY_UP)){
			setSyncLift(HIGH_HEIGHT);
		}else if(joystickGetDigital(1, 8, JOY_DOWN)){
			setSyncLift(MID_HEIGHT);
		}else{
			if(!runLift)
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
