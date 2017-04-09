#include "main.h"

void wheelMonitorTask(void *parameter){
    while(true){
        bool dLeftDirection = false;
        bool dRightDirection = false;
        bool leftDone = false;
        bool rightDone = false;
        bool gyroStepOne = false;
        bool gyroStepTwo = false;
        int targetOffset = 0;

        bool run = runWheels;

        int target = wheelTargetTicks;

        enum WheelDirection d = wheelDir;

        bool gyro = useGyro;

        while(run){
            run = runWheels;

            int gyroAverage = (gyroGet(gyroOne) + gyroGet(gyroTwo)) / 2;
            if(gyro){
                if((!leftDone || !rightDone) && !gyroStepOne){
                    targetOffset =  abs(target) < 45 ? 30 : abs(target * .6);
                    if(gyroAverage < target - (targetOffset)){
                        dLeft(true);
                        dRight(false);
                    }else if(gyroAverage > target + (targetOffset)){
                        dLeft(false);
                        dRight(true);
                    }else{
                        gyroStepOne = true;
                        stopDrive();
                        delay(400);
                    }
                }else if((!leftDone || !rightDone) && !gyroStepTwo){
                    DRIVEBASE_POWER /= 2;
                    if(gyroAverage < target){
                        dLeft(true);
                        dRight(false);
                    }else if(gyroAverage > target){
                        dLeft(false);
                        dRight(true);
                    }else{
                        gyroStepTwo = true;
                    }
                    DRIVEBASE_POWER *= 2;
                }else{

                    leftDone = true;
                    rightDone = true;
                    stopDrive();
                }

                if(leftDone && rightDone){
                    run = false;

                    runWheels = false;
                    stopDrive();
                }
            }else{
                if(abs(encoderGet(leftQuad)) < target){
                    switch(d){
                        case FORWARD: dLeftDirection = false; break;
                        case BACKWARD: dLeftDirection = true; break;
                        case LEFT: dLeftDirection = true; break;
                        case RIGHT: dLeftDirection = false; break;
                    }
                    dLeft(dLeftDirection);
                }else{
                    leftDone = true;
                    stopLeft();
                }

                if(abs(encoderGet(rightQuad)) < target){
                    switch(d){
                        case FORWARD: dRightDirection = false; break;
                        case BACKWARD: dRightDirection = true; break;
                        case LEFT: dRightDirection = false; break;
                        case RIGHT: dRightDirection = true; break;
                    }
                    dRight(dRightDirection);
                }else{
                    rightDone = true;
                    stopRight();
                }

                if(leftDone && rightDone){
                    run = false;

                    runWheels = false;
                    stopDrive();
                }
            }
            if(leftDone && rightDone){
                run = false;

                runWheels = false;

                stopDrive();
            }

            delay(20);
        }
        delay(20);
    }
}

void setSyncMove(enum WheelDirection d, int targetTicks, bool enableGyro){
    wheelTargetTicks = targetTicks;
    wheelDir = d;

    zeroDriveSensors();

    runWheels = true;

    useGyro = enableGyro;
}

void dLeft(bool backwards){
        setMotor(&backLeft, backwards ?  -DRIVEBASE_POWER : DRIVEBASE_POWER);
        setMotor(&frontLeft, backwards ? -DRIVEBASE_POWER : DRIVEBASE_POWER);
}

void dRight(bool backwards){
    setMotor(&backRight, backwards ?  -DRIVEBASE_POWER : DRIVEBASE_POWER);
    setMotor(&frontRight, backwards ? -DRIVEBASE_POWER : DRIVEBASE_POWER);
}

void analogDrive(){
    bool leftDead = (abs(joystickGetAnalog(1, 3)) > ANALOG_DEADZONE);
    bool rightDead = (abs(joystickGetAnalog(1, 2)) > ANALOG_DEADZONE);
    bool turning = (joystickGetAnalog(1, 2) > 0 && joystickGetAnalog(1, 3) < 0) || (joystickGetAnalog(1, 2) < 0 && joystickGetAnalog(1, 3) > 0);

    int leftSpeed = joystickGetAnalog(1, 3);
    int rightSpeed = joystickGetAnalog(1, 2);

    if(leftDead){
        if(turning){
            setMotor(&frontLeft, leftSpeed * TURN_MULTIPLIER);
            setMotor(&backLeft, leftSpeed * TURN_MULTIPLIER);
        }else{
            setMotor(&frontLeft, leftSpeed);
            setMotor(&backLeft, leftSpeed);
        }
    }else{
        stopLeft();
    }

    if(rightDead){
        if(turning){
            setMotor(&frontRight, rightSpeed * TURN_MULTIPLIER);
            setMotor(&backRight, rightSpeed * TURN_MULTIPLIER);
        }else{
            setMotor(&frontRight, rightSpeed);
            setMotor(&backRight, rightSpeed);
        }
    }else{
        stopRight();
    }

}

void stopLeft(){
    setMotor(&frontLeft, 0);
    setMotor(&backLeft, 0);
}

void stopRight(){
    setMotor(&frontRight, 0);
    setMotor(&backRight, 0);
}

void stopDrive(){
    stopLeft();
    stopRight();
}
