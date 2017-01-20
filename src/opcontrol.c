#include "main.h"

void operatorControl() {
	autonSelection = programSelected(8);

	while (1) {

		// if(joystickGetDigital(1, 6, JOY_UP) && !liftTooHigh){
		// 	dLift(false);
		// }else if(joystickGetDigital(1, 6, JOY_DOWN) && !liftTooLow){
		// 	dLift(true);
		// }else{
		// 	stopLift();
		// }

		if(joystickGetDigital(1, 6, JOY_UP)){
			dLift(false);
		}else if(joystickGetDigital(1, 6, JOY_DOWN)){
			dLift(true);
		}else{
			stopLift();
		}

		if(joystickGetDigital(1, 5, JOY_DOWN)){
			closeClaw(OFF);
		}else if(joystickGetDigital(1, 5, JOY_UP)){
			openClaw();
		}

		if(joystickGetDigital(1, 7, JOY_RIGHT)){
			strafeRight(OFF);
		}else if(joystickGetDigital(1, 7, JOY_LEFT)){
			strafeLeft(OFF);
		}else{
			analogDrive();
		}
	}
}
