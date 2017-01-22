#include "main.h"

void clawMonitorTask(void *parameter){
    fingerNeedsToOpen = (digitalRead(leftFingerSwitchPort) == 1 || digitalRead(rightFingerSwitchPort) == 1);
    while(true){
        if(downPressure == true && runFinger == false){
            motorSet(fingerY, 30);
        }else if(downPressure == false && runFinger == false){
            motorSet(fingerY, -5);
        }else if(runFinger == true){
            fingerNeedsToOpen = (digitalRead(leftFingerSwitchPort) == 1 || digitalRead(rightFingerSwitchPort) == 1);
        }
        while(runFinger && fingerNeedsToOpen){
            motorSet(fingerY, -127);
            fingerNeedsToOpen = (digitalRead(leftFingerSwitchPort) == 1 || digitalRead(rightFingerSwitchPort) == 1);
            if(fingerNeedsToOpen == false || (joystickGetDigital(1, 5, JOY_DOWN) && !isAutonomous())){
                runFinger = false;
            }
            delay(10);
        }
        delay(10);
    }
}

void closeClaw(int millis){
    if(millis != 0){
        mutexTake(motorMutexes[fingerY - 1], -1);
        motorSet(fingerY, CLAW_POWER);
        mutexGive(motorMutexes[fingerY - 1]);

        mutexTake(motorReqMutex, -1);
        motorReq[fingerY - 1] = CLAW_POWER;
        mutexGive(motorReqMutex);

        delay(millis);

        mutexTake(motorMutexes[fingerY - 1], -1);
        motorStop(fingerY);
        mutexGive(motorMutexes[fingerY - 1]);
    }else{
        mutexTake(motorMutexes[fingerY - 1], -1);
        motorSet(fingerY, CLAW_POWER);
        mutexGive(motorMutexes[fingerY - 1]);
    }
    downPressure = true;
}

void openClaw(){
    mutexTake(motorMutexes[fingerY - 1], -1);
    motorSet(fingerY, -CLAW_POWER);
    mutexGive(motorMutexes[fingerY - 1]);

    downPressure = false;
    fingerNeedsToOpen = true;
    runFinger = true;
}
