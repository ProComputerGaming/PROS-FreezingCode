#ifndef CLAW_H_
#define CLAW_H_

bool downPressure;
bool runFinger;
bool fingerNeedsToOpen;
int CLAW_POWER;

void fingerMonitor(void *parameter);
void closeClaw(int millis);
void openClaw();

#endif
