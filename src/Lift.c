#include "main.h"

void liftMonitorTask(void *parameter){
    while(true){
        mutexTake(runLiftMutex, -1);
        bool run = runLift;
        mutexGive(runLiftMutex);

        mutexTake(liftTicksMutex, -1);
        int target = liftTargetTicks;
        mutexGive(liftTicksMutex);

        while(run){
            LIFT_POWER /= 1.5;
            while(analogRead(liftPot) < target){
                dLift(true);
                delay(20);
            }
            stopLift();
            delay(300);
            while(analogRead(liftPot) > target){
                dLift(false);
                delay(20);
            }
            stopLift();
            run = false;
            mutexTake(runLiftMutex, -1);
            runLift = false;
            mutexGive(runLiftMutex);
            // bool needsToLower = (value > target) ? false : true;
            // switch(needsToLower){
            //     case true:
            //     while(value < target){
            //         value = analogRead(liftPot);
            //         dLift(needsToLower);
            //         delay(20);
            //     }
            //     stopLift();
            //     run = false;
            //     break;
            //     case false:
            //     while(value > target){
            //         value = analogRead(liftPot);
            //         dLift(needsToLower);
            //         delay(20);
            //     }
            //     stopLift();
            //     run = false;
            //     break;
            // }
            LIFT_POWER *= 1.5;
        }

        delay(20);
    }
}

void liftPID(void *parameter){
    liftDerivative = 0;
    liftError = 0;
    liftLastError = 0;
    liftCumError = 0;
    liftOutput = 0;
    while(true){

        liftCumError = 0;

        while(liftPIDRunning){
            int sensorVal = analogRead(liftPot);

            mutexTake(liftTicksMutex, -1);
            int setPoint = liftTargetTicks;
            mutexGive(liftTicksMutex);

            liftError = setPoint - sensorVal;
            liftCumError += liftError;
            liftDerivative = (liftError - lastLiftError)/(liftDeltaTime);
            lastLiftError = liftError;
            liftOutput = -clamp(((liftPGain * liftError) + (liftIGain * liftCumError) + (liftDGain* liftDerivative)), MOTOR_MIN_VALUE, MOTOR_MAX_VALUE);

            mutexTake(motorReqMutex, -1);
            motorReq[upperLift - 1] = -liftOutput;
            motorReq[lowerRightLift - 1] = -liftOutput;
            motorReq[lowerLeftLift - 1] = liftOutput;
            mutexGive(motorReqMutex);

            delay(liftDeltaTime * 1000);
        }
    }
}

void setSyncLift(int targetTicks){
    mutexTake(liftTicksMutex, -1);
    liftTargetTicks = targetTicks;
    mutexGive(liftTicksMutex);

    mutexTake(runLiftMutex, -1);
    runLift = true;
    mutexGive(runLiftMutex);
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
