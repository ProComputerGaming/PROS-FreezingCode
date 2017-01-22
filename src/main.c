#include "main.h"

void motorSlewTask(void *parameter){
    int motorIndex;
    int motorPort;
    int motorTmp;

    mutexTake(motorReqMutex, -1);
    for(motorIndex=0;motorIndex<MOTOR_NUM;motorIndex++)
    {
        motorReq[motorIndex] = 0;
        motorSlew[motorIndex] = MOTOR_DEFAULT_SLEW_RATE;
    }
    mutexGive(motorReqMutex);

    while( true )
    {
        int requestCopy[10];

        mutexTake(motorReqMutex, -1);
        for(int i = 0; i < 10; i++){
            requestCopy[i] = motorReq[i];
        }
        mutexGive(motorReqMutex);
        for( motorIndex=0; motorIndex<MOTOR_NUM; motorIndex++)
        {
            motorPort = motorIndex + 1;
            mutexTake(motorMutexes[motorIndex], -1);
            motorTmp = motorGet(motorPort);
            mutexGive(motorMutexes[motorIndex]);
            if( motorTmp != requestCopy[motorIndex] )
            {

                if( requestCopy[motorIndex] > motorTmp )
                {

                    motorTmp += motorSlew[motorIndex];

                    if( motorTmp > requestCopy[motorIndex] )
                    motorTmp = requestCopy[motorIndex];
                }

                if( requestCopy[motorIndex] < motorTmp )
                {
                    motorTmp -= motorSlew[motorIndex];

                    if( motorTmp < requestCopy[motorIndex] )
                    motorTmp = requestCopy[motorIndex];
                }

                mutexTake(motorMutexes[motorIndex], -1);
                motorSet(motorPort, motorTmp);
                mutexGive(motorMutexes[motorIndex]);
            }
        }
        delay( MOTOR_TASK_DELAY );
    }
}

void waitForTasks(){
    while(runFinger == true || runWheels == true || runLift == true){

    }
}

void stopAllMotors(){
    stopDrive();
    stopLift();

    mutexTake(motorMutexes[fingerY - 1], -1);
    motorStop(fingerY);
    mutexGive(motorMutexes[fingerY - 1]);
}

void zeroDriveSensors(){
    encoderReset(leftQuad);
    encoderReset(rightQuad);
}

void zeroAllSensors(){
    zeroDriveSensors();
    encoderReset(liftQuad);
}

int programSelected(int segments){
    int oneValue = clamp(analogRead(potOne)/(4095 / segments),0,segments - 1);
    int twoValue = clamp(analogRead(potTwo)/(4095 / segments),0,segments - 1);
    return oneValue + twoValue;
}

int clamp(int var, int min, int max){
    if(var > max){
        return max;
    }else if( var < min){
        return min;
    }else{
        return var;
    }
}
