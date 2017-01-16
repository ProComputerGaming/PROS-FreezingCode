#include "main.h"

void fingerMonitor(void *parameter){
  fingerNeedsToOpen = (digitalRead(leftFingerSwitchPort) == 1 || digitalRead(rightFingerSwitchPort) == 1);
  while(true){
    if(downPressure == true && runFinger == false){
      motorSet(fingerY, 30);
    }else if(downPressure == false && runFinger == false){
      motorSet(fingerY, -5);
    }else if(runFinger == true){
      fingerNeedsToOpen = (digitalRead(leftFingerSwitchPort) == 1 || digitalRead(rightFingerSwitchPort) == 1);
    }
    while(runFinger && fingerNeedsToOpen){
      motorSet(fingerY, -127);
      fingerNeedsToOpen = (digitalRead(leftFingerSwitchPort) == 1 || digitalRead(rightFingerSwitchPort) == 1);
      if(fingerNeedsToOpen == false || (joystickGetDigital(1, 5, JOY_DOWN) && !isAutonomous())){
        runFinger = false;
      }
    }
  }
}

void wheelMonitor(void *parameter){
  while(true){
    while(runWheels){
      if(encoderGet(leftQuad) < wheelTargetTicks){
        switch(wheelDir){
          case FORWARD: dLeftDirection = false; break;
          case BACKWARD: dLeftDirection = true; break;
          case LEFT: dLeftDirection = true; break;
          case RIGHT: dLeftDirection = false; break;
        }
        dLeft(dLeftDirection, false);
      }else{
        //dLeft(!dLeftDirection, false);
        //wait1Msec(100);
        leftDone = true;
        stopLeft();
      }
      if(encoderGet(rightQuad) < wheelTargetTicks){
        switch(wheelDir){
          case FORWARD: dRightDirection = false; break;
          case BACKWARD: dRightDirection = true; break;
          case LEFT: dRightDirection = false; break;
          case RIGHT: dRightDirection = true; break;
        }
        dRight(dRightDirection, false);
      }else{
        //dRight(!dRightDirection, false);
        //wait1Msec(100);
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

void liftMonitor(void *parameter){
  while(true){
    while(runLift){
      bool needsToLower = (encoderGet(liftQuad) > liftTargetTicks) ? true : false;
      switch(needsToLower){
        case true:
        while(encoderGet(liftQuad) > liftTargetTicks){
          dLift(needsToLower);
        }
        stopLift();
        runLift = false;
        break;
        case false:
        while(encoderGet(liftQuad) < liftTargetTicks){
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

void motorSlewTask(void *parameter)
{
  int motorIndex;
  int motorTmp;

  // Initialize stuff
  for(motorIndex=0;motorIndex<MOTOR_NUM;motorIndex++)
  {
    motorReq[motorIndex] = 0;
    motorSlew[motorIndex] = MOTOR_DEFAULT_SLEW_RATE;
  }

  // run task until stopped
  while( true )
  {
    // run loop for every motor
    for( motorIndex=0; motorIndex<MOTOR_NUM; motorIndex++)
    {
      // So we don't keep accessing the internal storage
      motorTmp = motorGet(motorIndex);

      // Do we need to change the motor value ?
      if( motorTmp != motorReq[motorIndex] )
      {
        // increasing motor value
        if( motorReq[motorIndex] > motorTmp )
        {
          motorTmp += motorSlew[motorIndex];
          // limit
          if( motorTmp > motorReq[motorIndex] )
          motorTmp = motorReq[motorIndex];
        }

        // decreasing motor value
        if( motorReq[motorIndex] < motorTmp )
        {
          motorTmp -= motorSlew[motorIndex];
          // limit
          if( motorTmp < motorReq[motorIndex] )
          motorTmp = motorReq[motorIndex];
        }

        // finally set motor
        motorSet(motorIndex, motorTmp);
      }
    }
    taskDelay( MOTOR_TASK_DELAY );
  }
}

void analogDrive(){
  motorReq[backRight] = joystickGetAnalog(1, 2);
  motorReq[frontRight] = joystickGetAnalog(1, 2);
  motorReq[backLeft] = joystickGetAnalog(1, 3);
  motorReq[frontLeft] = joystickGetAnalog(1, 3);
}

void waitForTasks(){
  while(runFinger == true || runWheels == true || runLift == true){

  }
}

void strafeLeft(int millis){
  if(millis != 0){
      motorReq[backRight] = -127;
      motorReq[frontRight] = 127;
      motorReq[backLeft] = 127;
      motorReq[frontLeft] = -127;
    delay(millis);
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
      delay(millis);
    stopDrive();
  }else{
    motorReq[backRight] = 127;
    motorReq[frontRight] = -127;
    motorReq[backLeft] = -127;
    motorReq[frontLeft] = 127;
  }
}

void closeClaw(int millis){
  if(millis != 0){
    motorSet(fingerY, CLAW_POWER);
    delay(millis);
    motorStop(fingerY);
  }else{
    motorSet(fingerY, CLAW_POWER);
  }
  downPressure = true;
}

void openClaw(){
  motorSet(fingerY, -CLAW_POWER);
  downPressure = false;
  fingerNeedsToOpen = true;
  runFinger = true;
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

void stopLift(){
  motorReq[upperLift] = 0;
  motorReq[lowerRightLift] = 0;
  motorReq[lowerLeftLift] = 0;
  motorStop(upperLift);
  motorStop(lowerRightLift);
  motorStop(lowerLeftLift);
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
