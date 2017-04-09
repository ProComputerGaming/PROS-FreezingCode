#include "main.h"

void motorSlewTask(void *parameter){
    int motorIndex;
    int motorTmp;

    while( true )
    {
        int requestCopy[8];

        for(int i = 0; i < 8; i++){
            requestCopy[i] = motors[i]->requestedSpeed;
        }

        for(motorIndex = 0; motorIndex<8; motorIndex++)
        {
            if(requestCopy[motorIndex] == 0){
                motorSet(motors[motorIndex]->port, 0);
                continue;
            }

            motorTmp = motorGet(motors[motorIndex]->port);
            if( motorTmp != requestCopy[motorIndex] )
            {

                if( requestCopy[motorIndex] > motorTmp )
                {

                    motorTmp += motors[motorIndex]->slewRate;

                    if( motorTmp > requestCopy[motorIndex] )
                    motorTmp = requestCopy[motorIndex];
                }

                if( requestCopy[motorIndex] < motorTmp )
                {
                    motorTmp -= motors[motorIndex]->slewRate;

                    if( motorTmp < requestCopy[motorIndex] )
                    motorTmp = requestCopy[motorIndex];
                }
                motors[motorIndex]->speed = motorTmp;
                motorSet(motors[motorIndex]->port, motorTmp);
            }
        }
        delay( MOTOR_TASK_DELAY );
    }
}


void initMotor(Motor *motor, int port, int slewRate, bool reversed){
    motor->speed = 0;
    motor->requestedSpeed = 0;
    motor->slewRate = slewRate;
    motor->port = port;
    motor->reversed = reversed;
}

bool setMotor(Motor *motor, int speed){
    if(motor->port < 1 || motor->port > 10) return false;

    if(speed > 127) speed = 127;
    if(speed < -127) speed = -127;
    if(motor->reversed) speed = -speed;

    motor->requestedSpeed = speed;

    return true;
}
