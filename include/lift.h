#ifndef LIFT_H_
#define LIFT_H_

#include <API.h>
#include "motor.h"

//Lift Motors
#define LIFT_ONE_PORT 4
#define LIFT_TWO_PORT 7
#define LIFT_THREE_PORT 5

//Digital Sensors
#define LIFT_QUAD_PORT 1

#define HIGH_HEIGHT 930
#define MID_HEIGHT 650
#define DOWN_HEIGHT 15

Motor liftOne;
Motor liftTwo;
Motor liftThree;

//Quadrature Encoders
Encoder liftQuad;

//LiftMonitorTask variables
bool runLift;
int liftTargetTicks;
int LIFT_POWER;

TaskHandle liftMonitorHandle;

void liftMonitorTask(void *parameter);
void liftPID(void *parameter);
void setSyncLift(int targetTicks);
void dLift(bool down);
void stopLift();

#endif
