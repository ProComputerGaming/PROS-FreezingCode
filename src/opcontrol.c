#include "main.h"

void operatorControl() {
	runFinger = false;

	runLift = false;

	runWheels = false;

	autonSelection = programSelected(8);

	int lastTime = millis();
	while (1) {
		autonSelection = programSelected(8);

		if(millis() - lastTime > 100){
			lastTime = millis();
			lcdPrint(uart1, 1, "%d, %d", gyroGet(gyroOne), gyroGet(gyroTwo));
			lcdPrint(uart1, 2, "%d, %d", abs((gyroGet(gyroOne) + gyroGet(gyroTwo))) / 2, autonSelection);
		}

		if(joystickGetDigital(1, 6, JOY_UP)){
			dLift(false);
		}else if(joystickGetDigital(1, 6, JOY_DOWN)){
			dLift(true);
		}else{
			if(!runLift)
				stopLift();
		}

		if(joystickGetDigital(1, 5, JOY_DOWN)){
			closeClaw(OFF);
		}else if(joystickGetDigital(1, 5, JOY_UP)){
			openClaw();
		}else{
			clawClosing = false;
		}

		analogDrive();

		delay(20);
	}
}
