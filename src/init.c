#include "main.h"

void initializeIO() {
    pinMode(leftFingerSwitchPort, INPUT);
    pinMode(rightFingerSwitchPort, INPUT);
}

void initialize() {
    WHEEL_CIR = PI * 4;
    TOLERANCE = .8;
    FULL = (int)((360/WHEEL_CIR)*(PI*14.25) * TOLERANCE);
    QUARTER = FULL / 4;
    HALF = FULL / 2;
    THREE_QUARTER = FULL / 1.5;

    DRIVEBASE_POWER = 63;
    CLAW_POWER = 127;
    LIFT_POWER = 127;
    TURN_MULTIPLIER = .5;

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

    lcdInit(uart1);
    lcdClear(uart1);

    liftQuad = encoderInit(liftQuadPort + 1, liftQuadPort, false);
    rightQuad = encoderInit(rightQuadPort + 1, rightQuadPort, false);
    leftQuad = encoderInit(leftQuadPort + 1, leftQuadPort, false);

    //liftMonitorHandle = taskCreate(liftMonitorTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
    //wheelMonitorHandle = taskCreate(wheelMonitorTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
    motorSlewHandle = taskCreate(motorSlewTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
    clawMonitorHandle = taskCreate(clawMonitorTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
    //taskMonitorHandle = taskCreate(taskMonitorTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT + 1);

    motorReqMutex =   mutexCreate();
    for(int i = 0; i < 10; i++){
        motorMutexes[i] = mutexCreate();
    }
    autonSelection = programSelected(8);
}
