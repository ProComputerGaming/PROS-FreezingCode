#include "main.h"

void initializeIO() {
    pinMode(leftFingerSwitchPort, INPUT);
    pinMode(rightFingerSwitchPort, INPUT);
}

void initialize() {

    printf("Defining Global Variables...\n");

    WHEEL_CIR = PI * 4;
    TOLERANCE = .8;
    FULL = (int)((360/WHEEL_CIR)*(PI*14.25) * TOLERANCE);
    QUARTER = FULL / 4;
    HALF = FULL / 2;
    THREE_QUARTER = FULL / 1.5;

    DRIVEBASE_POWER = 63;
    CLAW_POWER = 127;
    LIFT_POWER = 127;

    wheelTargetTicks = 0;
    liftTargetTicks = 0;

    downPressure = false;
    runFinger = false;
    fingerNeedsToOpen = false;

    wheelDir = FORWARD;
    dLeftDirection = false;
    dRightDirection = false;
    runWheels = false;
    leftDone = false;
    rightDone = false;

    runLift = false;

    printf("Initializing Sensors...\n");
    liftQuad = encoderInit(liftQuadPort + 1, liftQuadPort, false);
    rightQuad = encoderInit(rightQuadPort + 1, rightQuadPort, false);
    leftQuad = encoderInit(leftQuadPort + 1, leftQuadPort, false);
    gyro = gyroInit(gyroPort, 230);

    printf("Creating Custom Task Handles...\n");
    liftMonitorHandle = taskCreate(liftMonitorTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
    wheelMonitorHandle = taskCreate(wheelMonitorTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
    motorSlewHandle = taskCreate(motorSlewTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
    clawMonitorHandle = taskCreate(clawMonitorTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
    //debugHandle = taskCreate(debugTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT + 1);

    printf("Reading Autonomous Potentiometers...\n");
    autonSelection = programSelected(8);
    printf("Selected Autonomous: %d\n", autonSelection);
}
