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
    runWheels = false;

    runLift = false;

    liftPIDRunning = false;
    liftPGain = .05;
    liftIGain = .025;
    liftDGain = .015;
    liftDerivative = 0;
    lastLiftError = 0;
    liftError = 0;
    liftLastError = 0;
    liftCumError = 0;
    liftOutput = 0;
    liftDeltaTime = .5;

    lcdInit(uart2);
    lcdSetBacklight(uart2, true);
    lcdClear(uart2);


    liftQuad = encoderInit(liftQuadPort + 1, liftQuadPort, false);
    rightQuad = encoderInit(rightQuadPort + 1, rightQuadPort, false);
    leftQuad = encoderInit(leftQuadPort + 1, leftQuadPort, false);

    liftMonitorHandle = taskCreate(liftMonitorTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
    wheelMonitorHandle = taskCreate(wheelMonitorTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
    motorSlewHandle = taskCreate(motorSlewTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
    clawMonitorHandle = taskCreate(clawMonitorTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

    motorReqMutex =   mutexCreate();
    for(int i = 0; i < 10; i++){
        motorMutexes[i] = mutexCreate();
    }

    runWheelsMutex = mutexCreate();
    wheelDirMutex = mutexCreate();
    driveTicksMutex = mutexCreate();

    runLiftMutex = mutexCreate();
    liftTicksMutex = mutexCreate();

    runFingerMutex = mutexCreate();
    downPressureMutex = mutexCreate();

    autonSelection = programSelected(8);
}
