#ifndef MAIN_H_
#define MAIN_H_

#include <API.h>

#ifdef __cplusplus
extern "C" {
#endif

#define lowerRightLift 2
#define backRight 3
#define upperLift 4
#define fingerY 5
#define frontLeft 6
#define backLeft 7
#define frontRight 8
#define lowerLeftLift 9


const int MOTOR_NUM = 10;
const int MOTOR_MAX_VALUE = 127;
const int MOTOR_MIN_VALUE = -127;
int MOTOR_DEFAULT_SLEW_RATE = 15;      // Default value of 10 will cause 375mS from full fwd to rev
																							//15 will cause 254 mS from full fwd to rev
const int MOTOR_FAST_SLEW_RATE = 256;   // essentially off
const int MOTOR_TASK_DELAY = 15;      // task 1/frequency in mS (about 66Hz)
const int MOTOR_DEADBAND = 10;
const int MOTOR_SLEW_TOTAL_TIME = ((MOTOR_MAX_VALUE * 2)/MOTOR_DEFAULT_SLEW_RATE) * MOTOR_TASK_DELAY;

enum WheelDirection{
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
};

float PI = 3.14159265359;
float WHEEL_CIR=PI * 4;
float TOLERANCE = .8;
int FULL = (int)((360/WHEEL_CIR)*(PI*14.25) * TOLERANCE);
int QUARTER = FULL / 4;
int HALF = FULL / 2;
int THREE_QUARTER = FULL / 1.5;

int motorSlew[MOTOR_NUM];
int motorReq[MOTOR_NUM];
int DRIVEBASE_POWER;
int CLAW_POWER;
int LIFT_POWER;

int autonSelection;
const int SEGMENTS = 8;
int wheelTargetTicks;
int liftTargetTicks;

bool downPressure;
bool runFinger;
bool fingerNeedsToOpen;

enum WheelDirection wheelDir;
bool dLeftDirection;
bool dRightDirection;
bool runWheels;
bool leftDone;
bool rightDone;

bool runLift;

void autonomous();
void initializeIO();
void initialize();
void operatorControl();
void fingerMonitor(void *parameter);
void liftMonitor(void *parameter);
void wheelMonitor(void *parameter);
void motorSlewTask(void *parameter);
void analogDrive();
void waitForTasks();
void setSyncMove(WheelDirection d,int targetTicks);
void dLeft(bool backwards, bool bypassSlew);
void dRight(bool backwards, bool bypassSlew);
void setSyncLift(int targetTicks);
void dLift(bool down);
void strafeRight(int millis);
void strafeLeft(int millis);
void closeClaw(int millis);
void openClaw();
void stopLift();
void stopLeft();
void stopRight();
void stopDrive();
void stopAllMotors();
void zeroDriveSensors();
int programSelected(int segments);
int clamp(int var, int min, int max);

void autonZero();
void autonOne();
void autonTwo();
void autonThree();
void autonFour();
void autonFive();
void autonSix();
void autonSeven();
void autonEight();
void autonNine();
void autonTen();
void autonEleven();
void autonTwelve();
void autonThirteen();
void autonFourteen();

#ifdef __cplusplus
}
#endif

#endif
