#include "main.h"

void clawMonitorTask(void *parameter){
    while(true){
        mutexTake(downPressureMutex, 100);
        bool down = downPressure;
        mutexGive(downPressureMutex);

        mutexTake(runFingerMutex, 100);
        bool run = runFinger;
        mutexGive(runFingerMutex);

        mutexTake(clawClosingMutex, 100);
        bool closing = clawClosing;
        mutexGive(clawClosingMutex);

        bool open = (digitalRead(leftFingerSwitchPort) == 1 || digitalRead(rightFingerSwitchPort) == 1);

        if(closing == false){
            if(down == true && run == false){
                mutexTake(motorMutexes[fingerY - 1], 100);
                motorSet(fingerY, 15);
                mutexGive(motorMutexes[fingerY - 1]);
            }else if(down == false && run == false){
                mutexTake(motorMutexes[fingerY - 1], 100);
                motorSet(fingerY, -5);
                mutexGive(motorMutexes[fingerY - 1]);
            }else if(run == true){
                open = (digitalRead(leftFingerSwitchPort) == 1 || digitalRead(rightFingerSwitchPort) == 1);
            }
        }

        while(run && open){
            mutexTake(motorMutexes[fingerY - 1], 100);
            motorSet(fingerY, -127);
            mutexGive(motorMutexes[fingerY - 1]);
            open = (digitalRead(leftFingerSwitchPort) == 1 || digitalRead(rightFingerSwitchPort) == 1);
            if(open == false || (joystickGetDigital(1, 5, JOY_DOWN) && !isAutonomous())){
                run = false;

                mutexTake(runFingerMutex, 100);
                runFinger = false;
                mutexGive(runFingerMutex);

            }
            taskDelay(20);
        }
        taskDelay(20);
    }
}

void closeClaw(int millis){
    mutexTake(downPressureMutex, 100);
    downPressure = true;
    mutexGive(downPressureMutex);

    mutexTake(runFingerMutex, 100);
    runFinger = false;
    mutexGive(runFingerMutex);

    mutexTake(clawClosingMutex, 100);
    clawClosing = true;
    mutexGive(clawClosingMutex);
    if(millis != 0){
        mutexTake(motorMutexes[fingerY - 1], 100);
        motorSet(fingerY, CLAW_POWER);
        mutexGive(motorMutexes[fingerY - 1]);

        mutexTake(motorReqMutex, 100);
        motorReq[fingerY - 1] = CLAW_POWER;
        mutexGive(motorReqMutex);

        taskDelay(millis);

        mutexTake(motorMutexes[fingerY - 1], 100);
        motorStop(fingerY);
        mutexGive(motorMutexes[fingerY - 1]);

    }else{
        mutexTake(motorMutexes[fingerY - 1], 100);
        motorSet(fingerY, CLAW_POWER);
        mutexGive(motorMutexes[fingerY - 1]);
    }

}

void openClaw(){
    mutexTake(clawClosingMutex, 100);
    clawClosing = false;
    mutexGive(clawClosingMutex);

    mutexTake(motorMutexes[fingerY - 1], 100);
    motorSet(fingerY, -CLAW_POWER);
    mutexGive(motorMutexes[fingerY - 1]);

    mutexTake(downPressureMutex, 100);
    downPressure = false;
    mutexGive(downPressureMutex);

    mutexTake(runFingerMutex, 100);
    runFinger = true;
    mutexGive(runFingerMutex);
}
