#include "main.h"

void waitForTasks(){
    bool finger = true;
    bool lift = true;
    bool wheels = true;

    while(finger == true || wheels == true || lift == true){

        finger = runFinger;
        lift = runLift;
        wheels = runWheels;

        delay(20);
    }
}

void stopAllMotors(){
    stopDrive();
    stopLift();

    mutexTake(claw.mutex, MUTEX_TIMEOUT);
    motorStop(CLAW_PORT);
    mutexGive(claw.mutex);
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
    int oneValue = clamp(analogRead(POT_ONE_PORT)/(4095 / segments),0,segments - 1);
    int twoValue = clamp(analogRead(POT_TWO_PORT)/(4095 / segments),0,segments - 1);
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
