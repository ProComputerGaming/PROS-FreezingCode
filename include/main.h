#ifndef MAIN_H_
#define MAIN_H_

#include <API.h>

#ifdef __cplusplus
extern "C" {
  #endif

  #define PI 3.14159265359
  #define OFF 0

  //Motor Config
  #define lowerRightLift 2
  #define backRight 3
  #define upperLift 4
  #define fingerY 5
  #define frontLeft 6
  #define backLeft 7
  #define frontRight 8
  #define lowerLeftLift 9

  //Analog Sensor Config
  #define liftPot 6
  #define potOne 7
  #define potTwo 8

  //Digital Sensor Config
  #define liftQuadPort 1
  #define leftFingerSwitchPort 3
  #define rightFingerSwitchPort 4
  #define rightQuadPort 5
  #define leftQuadPort 7


  #define MOTOR_NUM 10
  #define MOTOR_MAX_VALUE 127
  #define MOTOR_MIN_VALUE -127
  #define MOTOR_DEFAULT_SLEW_RATE 10
  #define MOTOR_FAST_SLEW_RATE 256
  #define MOTOR_TASK_DELAY 15
  #define MOTOR_DEADBAND 10

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

  int motorSlew[MOTOR_NUM];
  int motorReq[MOTOR_NUM];
  int DRIVEBASE_POWER;
  int CLAW_POWER;
  int LIFT_POWER;

  int autonSelection;
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

  Encoder liftQuad;
  Encoder rightQuad;
  Encoder leftQuad;

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
  void setSyncMove(enum WheelDirection d,int targetTicks);
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
