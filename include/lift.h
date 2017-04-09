#ifndef LIFT_H_
#define LIFT_H_

//LiftMonitorTask variables
bool runLift;
int liftTargetTicks;
int LIFT_POWER;

void liftMonitorTask(void *parameter);
void liftPID(void *parameter);
void setSyncLift(int targetTicks);
void dLift(bool down);
void stopLift();

#endif
