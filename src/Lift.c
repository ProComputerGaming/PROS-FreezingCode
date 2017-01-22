#include "main.h"

void liftMonitorTask(void *parameter){
    while(true){
        while(runLift){
            bool needsToLower = (abs(encoderGet(liftQuad)) > liftTargetTicks) ? true : false;
            switch(needsToLower){
                case true:
                while(abs(encoderGet(liftQuad)) > liftTargetTicks){
                    dLift(needsToLower);
                    delay(10);
                }
                stopLift();
                runLift = false;
                break;
                case false:
                while(abs(encoderGet(liftQuad)) < liftTargetTicks){
                    dLift(needsToLower);
                    delay(10);
                }
                stopLift();
                runLift = false;
                break;
            }
            delay(10);
        }
        delay(10);
    }
}

void setSyncLift(int targetTicks){
    liftTargetTicks = targetTicks;
    runLift = true;
}

void dLift(bool down){
    mutexTake(motorReqMutex, -1);
    motorReq[upperLift - 1] = down ? LIFT_POWER : -LIFT_POWER;
    motorReq[lowerRightLift - 1] = down ? LIFT_POWER : -LIFT_POWER;
    motorReq[lowerLeftLift - 1] = down ? -LIFT_POWER : LIFT_POWER;
    mutexGive(motorReqMutex);
}

void stopLift(){
    mutexTake(motorReqMutex, -1);
    motorReq[upperLift - 1] = 0;
    motorReq[lowerRightLift - 1] = 0;
    motorReq[lowerLeftLift - 1] = 0;
    mutexGive(motorReqMutex);

    mutexTake(motorMutexes[upperLift - 1], -1);
    motorStop(upperLift);
    mutexGive(motorMutexes[upperLift - 1]);

    mutexTake(motorMutexes[lowerRightLift - 1], -1);
    motorStop(lowerRightLift);
    mutexGive(motorMutexes[lowerRightLift - 1]);

    mutexTake(motorMutexes[lowerLeftLift - 1], -1);
    motorStop(lowerLeftLift);
    mutexGive(motorMutexes[lowerLeftLift - 1]);
}
