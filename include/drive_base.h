#ifndef DRIVE_BASE_H_
#define DRIVE_BASE_H_

#include <API.h>
#include "motor.h"

//Drive Motors
#define BACK_RIGHT_PORT 9
#define FRONT_LEFT_PORT 3
#define BACK_LEFT_PORT 6
#define FRONT_RIGHT_PORT 2

//Digital Sensors
#define RIGHT_QUAD_PORT 5
#define LEFT_QUAD_PORT 7

//Analog Sensors
#define GYRO_ONE_PORT 5
#define GYRO_TWO_PORT 4

#define ANALOG_DEADZONE 10

Motor backRight;
Motor backLeft;
Motor frontLeft;
Motor frontRight;

Encoder rightQuad;
Encoder leftQuad;
Gyro gyroOne;
Gyro gyroTwo;

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
bool useGyro;
float TURN_MULTIPLIER;
int DRIVEBASE_POWER;

TaskHandle wheelMonitorHandle;

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
