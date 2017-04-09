#ifndef CLAW_H_
#define CLAW_H_

#include <API.h>
#include "motor.h"

//Claw Motors
#define CLAW_PORT 8

#define LEFT_CLAW_SWITCH_PORT 3
#define RIGHT_CLAW_SWITCH_PORT 4

    Motor claw;

//ClawMonitorTask variables
bool downPressure;
bool runFinger;
bool fingerNeedsToOpen;
bool clawClosing;
bool clawDown;
int CLAW_POWER;

  TaskHandle clawMonitorHandle;
  
    void clawMonitorTask(void *parameter);
    void closeClaw(int millis);
    void openClaw();

#endif
