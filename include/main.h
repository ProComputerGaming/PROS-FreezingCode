#ifndef MAIN_H_
#define MAIN_H_

#include <API.h>
#include "motor.h"
#include "claw.h"
#include "lift.h"
#include "drive_base.h"

#ifdef __cplusplus
extern "C" {
    #endif

    #define PI 3.14159265359
    #define OFF 0

    //Drive Motors
    #define BACK_RIGHT_PORT 9
    #define FRONT_LEFT_PORT 3
    #define BACK_LEFT_PORT 6
    #define FRONT_RIGHT_PORT 2

    //Lift Motors
    #define LIFT_ONE_PORT 4
    #define LIFT_TWO_PORT 7
    #define LIFT_THREE_PORT 5

    //Claw Motors
    #define CLAW_PORT 8

    //Digital Sensors
    #define LIFT_QUAD_PORT 1
    #define LEFT_CLAW_SWITCH_PORT 3
    #define RIGHT_CLAW_SWITCH_PORT 4
    #define RIGHT_QUAD_PORT 5
    #define LEFT_QUAD_PORT 7

    //Analog Sensors
    #define GYRO_ONE_PORT 5
    #define GYRO_TWO_PORT 4
    #define POT_ONE_PORT 7
    #define POT_TWO_PORT 8

    #define ANALOG_DEADZONE 10

    #define MUTEX_TIMEOUT 100
    #define MID_HEIGHT 600
    #define HIGH_HEIGHT 650
    #define DOWN_HEIGHT 20

    //Index of the autonomous routine to run based on the two potentiometers mounted on the back of the robot
    int autonSelection;

    bool useGyro;

    Motor backRight;
    Motor backLeft;
    Motor frontLeft;
    Motor frontRight;
    Motor liftOne;
    Motor liftTwo;
    Motor liftThree;
    Motor claw;

    //Quadrature Encoders
    Encoder liftQuad;
    Encoder rightQuad;
    Encoder leftQuad;
    Gyro gyroOne;
    Gyro gyroTwo;

    TaskHandle clawMonitorHandle;
    TaskHandle wheelMonitorHandle;
    TaskHandle liftMonitorHandle;
    TaskHandle liftPIDHandle;
    TaskHandle motorSlewHandle;
    TaskHandle taskMonitorHandle;

    int programSelected(int segments);
    int clamp(int var, int min, int max);

    void waitForTasks();
    void stopAllMotors();

    void zeroDriveSensors();
    void zeroAllSensors();

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

    void autonomous();
    void initializeIO();
    void initialize();
    void operatorControl();

    #ifdef __cplusplus
}
#endif

#endif
