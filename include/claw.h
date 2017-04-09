#ifndef CLAW_H_
#define CLAW_H_

//ClawMonitorTask variables
bool downPressure;
bool runFinger;
bool fingerNeedsToOpen;
bool clawClosing;
bool clawDown;
int CLAW_POWER;


    void clawMonitorTask(void *parameter);
    void closeClaw(int millis);
    void openClaw();

#endif
