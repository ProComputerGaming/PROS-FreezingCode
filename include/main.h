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

    #define POT_ONE_PORT 7
    #define POT_TWO_PORT 8

    //Index of the autonomous routine to run based on the two potentiometers mounted on the back of the robot
    int autonSelection;

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
