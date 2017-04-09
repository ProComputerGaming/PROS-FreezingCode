#include "main.h"

void liftMonitorTask(void *parameter){
    while(true){
        bool run = runLift;

        int target = liftTargetTicks;

        while(run){
            bool needsToLower = (abs(encoderGet(liftQuad)) > target) ? true : false;
            switch(needsToLower){
                case true:
                    while(abs(encoderGet(liftQuad)) > target){
                        dLift(needsToLower);
                        delay(20);
                    }
                    stopLift();
                    run = false;
                    break;
                case false:
                    while(abs(encoderGet(liftQuad)) < target){
                        dLift(needsToLower);
                        delay(20);
                    }
                    stopLift();
                    run = false;
                    break;
            }

            runLift = false;
        }

        delay(20);
    }
}

void setSyncLift(int targetTicks){
    liftTargetTicks = targetTicks;

    runLift = true;
}

void dLift(bool down){
    setMotor(&liftThree, down ? -LIFT_POWER : LIFT_POWER);
    setMotor(&liftTwo, down ? -LIFT_POWER : LIFT_POWER);
    setMotor(&liftOne, down ? -LIFT_POWER : LIFT_POWER);
}

void stopLift(){
    setMotor(&liftThree, 0);
    setMotor(&liftTwo, 0);
    setMotor(&liftOne, 0);
}
