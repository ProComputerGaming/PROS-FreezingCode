#include "main.h"

void motorSlewTask(void *parameter){
    int motorIndex;
    int motorTmp;

    for(motorIndex=0;motorIndex<MOTOR_NUM;motorIndex++)
    {
        motorReq[motorIndex] = 0;
        motorSlew[motorIndex] = MOTOR_DEFAULT_SLEW_RATE;
    }

    while( true )
    {
        for( motorIndex=0; motorIndex<MOTOR_NUM; motorIndex++)
        {

            motorTmp = motorGet(motorIndex);

            if( motorTmp != motorReq[motorIndex] )
            {

                if( motorReq[motorIndex] > motorTmp )
                {

                    motorTmp += motorSlew[motorIndex];

                    if( motorTmp > motorReq[motorIndex] )
                    motorTmp = motorReq[motorIndex];
                }

                if( motorReq[motorIndex] < motorTmp )
                {
                    motorTmp -= motorSlew[motorIndex];
                    // limit
                    if( motorTmp < motorReq[motorIndex] )
                    motorTmp = motorReq[motorIndex];
                }
                motorSet(motorIndex, motorTmp);
            }
        }
        taskDelay( MOTOR_TASK_DELAY );
    }
}

void waitForTasks(){
    while(runFinger == true || runWheels == true || runLift == true){

    }
}

void stopAllMotors(){
    stopDrive();
    stopLift();
    motorStop(fingerY);
}

void zeroDriveSensors(){
    encoderReset(leftQuad);
    encoderReset(rightQuad);
}

void zeroAllSensors(){
    zeroDriveSensors();
    encoderReset(liftQuad);
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