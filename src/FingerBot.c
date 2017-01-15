#include "main.h"

void fingerMonitor(void *parameter){
        fingerNeedsToOpen = (SensorValue[leftFingerSwitch] == 1 || SensorValue[rightFingerSwitch] == 1);
        while(true){
                if(downPressure == true && runFinger == false){
                        motorSet(fingerY, 30);
                }else if(downPressure == false && runFinger == false){
                        motorSet(fingerY, -5);
                }else if(runFinger == true){
                        fingerNeedsToOpen = (SensorValue[leftFingerSwitch] == 1 || SensorValue[rightFingerSwitch] == 1);
                }
                while(runFinger && fingerNeedsToOpen){
                        motorSet(fingerY, -127);
                        fingerNeedsToOpen = (SensorValue[leftFingerSwitch] == 1 || SensorValue[rightFingerSwitch] == 1);
                        if(fingerNeedsToOpen == false || (joystickGetDigital(1, 5, JOY_DOWN) && !isAutonomous())){
                                runFinger = false;
                        }
              }
        }
}

void wheelMonitor(void *parameter){
        while(true){
                while(runWheels){
                        if(abs(SensorValue(leftQuad)) < wheelTargetTicks){
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
                        if(abs(SensorValue(rightQuad)) < wheelTargetTicks){
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

void liftMonitor(void *parameter){
    while(true){
        while(runLift){
        		bool needsToLower = (abs(SensorValue(liftQuad)) > liftTargetTicks) ? true : false;
        		switch(needsToLower){
        			case true:
        				while(abs(SensorValue(liftQuad)) > liftTargetTicks){
        					dLift(needsToLower);
        				}
        				stopLift();
        				runLift = false;
        				break;
        			case false:
        				while(abs(SensorValue(liftQuad)) < liftTargetTicks){
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
            motorTmp = motor[ motorIndex ];

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
                motor[motorIndex] = motorTmp;
                }
            }
        wait1Msec( MOTOR_TASK_DELAY );
        }
}

void analogDrive(){
        motorReq[backRight] = vexRT[Ch2];
        motorReq[frontRight] = vexRT[Ch2];
        motorReq[backLeft] = vexRT[Ch3];
        motorReq[frontLeft] = vexRT[Ch3];
}

void waitForTasks(){
    while(runFinger == true || runWheels == true || runLift == true){

    }
}

void strafeLeft(int millis){
        if(millis != 0){
                clearTimer(T1);
                while(time1[T1] < millis){
                        motorReq[backRight] = -127;
                        motorReq[frontRight] = 127;
                        motorReq[backLeft] = 127;
                        motorReq[frontLeft] = -127;
                }
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
                clearTimer(T1);
                while(time1[T1] < millis){
                        motorReq[backRight] = 127;
                        motorReq[frontRight] = -127;
                        motorReq[backLeft] = -127;
                        motorReq[frontLeft] = 127;
                }
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
                clearTimer(T1);
                while(time1[T1] < millis){
                        motor[fingerY] = CLAW_POWER;
                }
                motor[fingerY] = 0;
        }else{
                motor[fingerY] = CLAW_POWER;
        }
        downPressure = true;
}

void openClaw(){
        motor[fingerY] = -CLAW_POWER;
        downPressure = false;
        fingerNeedsToOpen = true;
        runFinger = true;
}

void stopLeft(){
  if(inAutonomous){
		motor[backLeft] = 0;
    motor[frontLeft] = 0;
    motorReq[backLeft] = 0;
    motorReq[frontLeft] = 0;
	}else{
		motorReq[backLeft] = 0;
    motorReq[frontLeft] = 0;
  }
}

void stopRight(){
	if(inAutonomous){
		motor[backRight] = 0;
    motor[frontRight] = 0;
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
  motor[upperLift] = 0;
  motor[lowerRightLift] = 0;
  motor[lowerLeftLift] = 0;
}

void stopAllMotors(){
        stopDrive();
        stopLift();
        motor[fingerY] = 0;
}

void zeroDriveSensors(){
        SensorValue(leftQuad) = 0;
        SensorValue(rightQuad) = 0;
}

void zeroAllSensors(){
        zeroDriveSensors();
        SensorValue(liftQuad) = 0;
}

int programSelected(int segments){
        int oneValue = clamp(SensorValue(potOne)/(4095 / segments),0,SEGMENTS - 1);
        int twoValue = clamp(SensorValue(potTwo)/(4095 / segments),0,SEGMENTS - 1);
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
