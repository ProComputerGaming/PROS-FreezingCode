#include "main.h"
#include "Lift.h"


void liftMonitor(void *parameter){
    while(true){
        while(runLift){
            bool needsToLower = (abs(encoderGet(liftQuad)) > liftTargetTicks) ? true : false;
            switch(needsToLower){
                case true:
                while(abs(encoderGet(liftQuad)) > liftTargetTicks){
                    dLift(needsToLower);
                }
                stopLift();
                runLift = false;
                break;
                case false:
                while(abs(encoderGet(liftQuad)) < liftTargetTicks){
                    dLift(needsToLower);
                }
                stopLift();
                runLift = false;
                break;
            }
        }
    }
}

void setSyncLift(int targetTicks){
    liftTargetTicks = targetTicks;
    runLift = true;
}

void dLift(bool down){
    motorReq[upperLift] = down ? -LIFT_POWER : LIFT_POWER;
    motorReq[lowerRightLift] = down ? -LIFT_POWER : LIFT_POWER;
    motorReq[lowerLeftLift] = down ? -LIFT_POWER : LIFT_POWER;
}

void stopLift(){
    motorReq[upperLift] = 0;
    motorReq[lowerRightLift] = 0;
    motorReq[lowerLeftLift] = 0;
    motorStop(upperLift);
    motorStop(lowerRightLift);
    motorStop(lowerLeftLift);
}
