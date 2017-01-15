#include "main.h"

void initializeIO() {
}

void initialize() {

enum WheelDirection{
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
};

WHEEL_CIR=PI * 4;
TOLERANCE = .8;
FULL = (int)((360/WHEEL_CIR)*(PI*14.25) * TOLERANCE);
QUARTER = FULL / 4;
HALF = FULL / 2;
THREE_QUARTER = FULL / 1.5;

DRIVEBASE_POWER = 63;
CLAW_POWER = 127;
LIFT_POWER = 127;
autonSelection = 0;

wheelTargetTicks = 0;
liftTargetTicks = 0;

downPressure = false;
runFinger = false;
fingerNeedsToOpen = false;

WheelDirection wheelDir = FORWARD;
dLeftDirection = false;
dRightDirection = false;
runWheels = false;
leftDone = false;
rightDone = false;

runLift = false;
}
