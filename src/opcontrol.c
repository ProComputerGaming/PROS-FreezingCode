#include "main.h"

void operatorControl() {
			autonSelection = programSelected(8);
	while (1) {

		printf("Degrees: %d\n", gyroGet(gyro));
		taskDelay(500);
		bool liftTooHigh = analogRead(liftPot) < 825;
		bool liftTooLow = analogRead(liftPot) > 3000;

		if(joystickGetDigital(1, 6, JOY_UP) && !liftTooHigh){
					dLift(false);
		}else if(joystickGetDigital(1, 6, JOY_DOWN) && !liftTooLow){
					dLift(true);
		}else{
			stopLift();
		}

		if(joystickGetDigital(1, 5, JOY_DOWN)){
			closeClaw(OFF);
		}else if(joystickGetDigital(1, 5, JOY_UP) == 1){
			openClaw();
		}

		if(joystickGetDigital(1, 7, JOY_RIGHT)){
			strafeRight(OFF);
		}
		if(joystickGetDigital(1, 7, JOY_LEFT)){
			strafeLeft(OFF);
		}
		if(joystickGetDigital(1, 7, JOY_RIGHT) == OFF && joystickGetDigital(1, 7, JOY_LEFT) == OFF){
			analogDrive();
		}
	}
}
