#ifndef LIFT_H_
#define LIFT_H_

bool runLift;
int liftTargetTicks;
int LIFT_POWER;

void liftMonitor(void *parameter);
void setSyncLift(int targetTicks);
void dLift(bool down);
void stopLift();
#endif
