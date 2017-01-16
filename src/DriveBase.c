#include "main.h"
#include "DriveBase.h"

void wheelMonitor(void *parameter){
    while(true){
        while(runWheels){
            if(abs(encoderGet(leftQuad)) < wheelTargetTicks){
                switch(wheelDir){
                    case FORWARD: dLeftDirection = false; break;
                    case BACKWARD: dLeftDirection = true; break;
                    case LEFT: dLeftDirection = true; break;
                    case RIGHT: dLeftDirection = false; break;
                }
                dLeft(dLeftDirection, false);
            }else{
                leftDone = true;
                stopLeft();
            }
            if(abs(encoderGet(rightQuad)) < wheelTargetTicks){
                switch(wheelDir){
                    case FORWARD: dRightDirection = false; break;
                    case BACKWARD: dRightDirection = true; break;
                    case LEFT: dRightDirection = false; break;
                    case RIGHT: dRightDirection = true; break;
                }
                dRight(dRightDirection, false);
            }else{
                rightDone = true;
                stopRight();
            }
            if(leftDone && rightDone)
            runWheels = false;
        }
        stopDrive();
    }
}

void setSyncMove(enum WheelDirection d, int targetTicks){
    wheelTargetTicks = targetTicks;
    wheelDir = d;
    leftDone = false;
    rightDone = false;
    zeroDriveSensors();
    runWheels = true;
}

void dLeft(bool backwards, bool bypassSlew){
    if(bypassSlew){
        motorSet(backLeft, backwards ?  -DRIVEBASE_POWER : DRIVEBASE_POWER);
        motorSet(frontLeft, backwards ?  -DRIVEBASE_POWER : DRIVEBASE_POWER);
        motorReq[backLeft] = backwards ?  -DRIVEBASE_POWER : DRIVEBASE_POWER;
        motorReq[frontLeft] = backwards ? -DRIVEBASE_POWER : DRIVEBASE_POWER;
    }else{
        motorReq[backLeft] = backwards ?  -DRIVEBASE_POWER : DRIVEBASE_POWER;
        motorReq[frontLeft] = backwards ? -DRIVEBASE_POWER : DRIVEBASE_POWER;
    }
}

void dRight(bool backwards, bool bypassSlew){
    if(bypassSlew){
        motorSet(backRight, backwards ?  -DRIVEBASE_POWER : DRIVEBASE_POWER);
        motorSet(frontRight, backwards ?  -DRIVEBASE_POWER : DRIVEBASE_POWER);
        motorReq[backRight] = backwards ?  -DRIVEBASE_POWER : DRIVEBASE_POWER;
        motorReq[frontRight] = backwards ? -DRIVEBASE_POWER : DRIVEBASE_POWER;
    }else{
        motorReq[backRight] = backwards ?  -DRIVEBASE_POWER : DRIVEBASE_POWER;
        motorReq[frontRight] = backwards ? -DRIVEBASE_POWER : DRIVEBASE_POWER;
    }
}

void analogDrive(){
    motorReq[backRight] = joystickGetAnalog(1, 2);
    motorReq[frontRight] = joystickGetAnalog(1, 2);
    motorReq[backLeft] = joystickGetAnalog(1, 3);
    motorReq[frontLeft] = joystickGetAnalog(1, 3);
}

void strafeLeft(int millis){
    if(millis != 0){
        motorReq[backRight] = -127;
        motorReq[frontRight] = 127;
        motorReq[backLeft] = 127;
        motorReq[frontLeft] = -127;
        taskDelay(millis);
        stopDrive();
    }else{
        motorReq[backRight] = -127;
        motorReq[frontRight] = 127;
        motorReq[backLeft] = 127;
        motorReq[frontLeft] = -127;
    }
}

void strafeRight(int millis){
    if(millis != 0){
        motorReq[backRight] = 127;
        motorReq[frontRight] = -127;
        motorReq[backLeft] = -127;
        motorReq[frontLeft] = 127;
        taskDelay(millis);
        stopDrive();
    }else{
        motorReq[backRight] = 127;
        motorReq[frontRight] = -127;
        motorReq[backLeft] = -127;
        motorReq[frontLeft] = 127;
    }
}

void stopLeft(){
    if(isAutonomous()){
        motorStop(backLeft);
        motorStop(frontLeft);
        motorReq[backLeft] = 0;
        motorReq[frontLeft] = 0;
    }else{
        motorReq[backLeft] = 0;
        motorReq[frontLeft] = 0;
    }
}

void stopRight(){
    if(isAutonomous()){
        motorStop(backRight);
        motorStop(frontRight);
        motorReq[backRight] = 0;
        motorReq[frontRight] = 0;
    }else{
        motorReq[backRight] = 0;
        motorReq[frontRight] = 0;
    }
}

void stopDrive(){
    stopLeft();
    stopRight();
}
