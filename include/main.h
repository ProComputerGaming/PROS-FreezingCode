#ifndef MAIN_H_
#define MAIN_H_

#include <API.h>
#include "auto.h"
#include "DriveBase.h"
#include "Lift.h"
#include "Claw.h"

#ifdef __cplusplus
extern "C" {
    #endif

    #define PI 3.14159265359
    #define OFF 0

    //Drive Motors
    #define backRight 3
    #define frontLeft 6
    #define backLeft 7
    #define frontRight 8

    //Lift Motors
    #define lowerRightLift 2
    #define upperLift 4
    #define lowerLeftLift 9

    //Claw Motors
    #define fingerY 5

    //Digital Sensors
    #define liftQuadPort 1
    #define leftFingerSwitchPort 3
    #define rightFingerSwitchPort 4
    #define rightQuadPort 5
    #define leftQuadPort 7

    //Analog Sensors
    #define gyroPort 1
    #define liftPot 6
    #define potOne 7
    #define potTwo 8

    #define MOTOR_NUM 10
    #define MOTOR_MAX_VALUE 127
    #define MOTOR_MIN_VALUE -127
    #define MOTOR_DEFAULT_SLEW_RATE 10
    #define MOTOR_FAST_SLEW_RATE 256
    #define MOTOR_TASK_DELAY 15
    #define MOTOR_DEADBAND 10

    int motorSlew[MOTOR_NUM];
    int motorReq[MOTOR_NUM];


    Encoder liftQuad;
    Encoder rightQuad;
    Encoder leftQuad;
    Gyro gyro;

    TaskHandle fingerMonitorHandle;
    TaskHandle wheelMonitorHandle;
    TaskHandle liftMonitorHandle;
    TaskHandle motorSlewHandle;

    void autonomous();
    void initializeIO();
    void initialize();
    void operatorControl();

    void motorSlewTask(void *parameter);
    void waitForTasks();
    void stopAllMotors();
    void zeroDriveSensors();
    void zeroAllSensors();

    int clamp(int var, int min, int max);

    #ifdef __cplusplus
}
#endif

#endif
