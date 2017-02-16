#include "main.h"

void operatorControl() {
	mutexTake(runFingerMutex, -1);
	runFinger = false;
	mutexGive(runFingerMutex);

	mutexTake(runLiftMutex, -1);
	runLift = false;
	mutexGive(runLiftMutex);

	mutexTake(runWheelsMutex, -1);
	runWheels = false;
	mutexGive(runWheelsMutex);
	lcdPrint(uart1, 1, "Auto");
	autonSelection = programSelected(8);

	int lastTime = millis();
	int lastTimeTwo = millis();
	while (1) {
		autonSelection = programSelected(8);
		if(millis() - lastTime > 100){
			lastTime = millis();
			lcdPrint(uart1, 1, "%d, %d", gyroGet(gyroOne), gyroGet(gyroTwo));
			lcdPrint(uart1, 2, "%d, %d", abs((gyroGet(gyroOne) + gyroGet(gyroTwo))) / 2, autonSelection);
		}

		if(millis() - lastTimeTwo > 400){
			lastTimeTwo = millis();
			printf("Lift Quad: %d\n", abs(encoderGet(liftQuad)));
		}

		int liftPotValue = analogRead(liftPot);
		bool liftTooLow = liftPotValue < 825;
		bool liftTooHigh = liftPotValue > 3100;

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
		}else{
			mutexTake(clawClosingMutex, -1);
			clawClosing = false;
			mutexGive(clawClosingMutex);
		}

		if(joystickGetDigital(1, 7, JOY_UP)){
			gyroReset(gyroOne);
			gyroReset(gyroTwo);
			delay(500);
		}

		analogDrive();

		delay(20);
	}
}
