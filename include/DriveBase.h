#ifndef DRIVE_BASE_H_
#define DRIVE_BASE_H_

enum WheelDirection{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
};

float WHEEL_CIR;
float TOLERANCE;
int FULL;
int QUARTER;
int HALF;
int THREE_QUARTER;

int wheelTargetTicks;
enum WheelDirection wheelDir;
bool dLeftDirection;
bool dRightDirection;
bool runWheels;
bool leftDone;
bool rightDone;
int DRIVEBASE_POWER;

void wheelMonitor(void *parameter);
void setSyncMove(enum WheelDirection d,int targetTicks);
void dLeft(bool backwards, bool bypassSlew);
void dRight(bool backwards, bool bypassSlew);
void strafeRight(int millis);
void strafeLeft(int millis);
void analogDrive();
void stopLeft();
void stopRight();
void stopDrive();

#endif
