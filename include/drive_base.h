#ifndef DRIVE_BASE_H_
#define DRIVE_BASE_H_

//Enumeration defining autonomous movement direction
enum WheelDirection{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
};

enum WheelDirection wheelDir;

//Theoretical Encoder Clicks for turning (Not accurate in practice due to wheels slipping)
float WHEEL_CIR;
float TOLERANCE;
int FULL;
int QUARTER;
int HALF;
int THREE_QUARTER;

//WheelMonitorTask variables
int wheelTargetTicks;

bool runWheels;
int DRIVEBASE_POWER;
float TURN_MULTIPLIER;

void wheelMonitorTask(void *parameter);
void setSyncMove(enum WheelDirection d,int targetTicks, bool enableGyro);
void dLeft(bool backwards);
void dRight(bool backwards);
void strafeRight(int millis);
void strafeLeft(int millis);
void analogDrive();
void stopLeft();
void stopRight();
void stopDrive();

#endif
