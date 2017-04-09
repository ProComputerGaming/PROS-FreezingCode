#include "main.h"

void initializeIO() {
    pinMode(LEFT_CLAW_SWITCH_PORT, INPUT);
    pinMode(RIGHT_CLAW_SWITCH_PORT, INPUT);
}

void initialize() {
    lcdInit(uart1);
    lcdClear(uart1);
    lcdSetBacklight(uart1, 1);

    initMotor(&backRight, BACK_RIGHT_PORT, MOTOR_DEFAULT_SLEW_RATE, true);
    initMotor(&backLeft, BACK_LEFT_PORT, MOTOR_DEFAULT_SLEW_RATE, false);
    initMotor(&frontLeft, FRONT_LEFT_PORT, MOTOR_DEFAULT_SLEW_RATE, true);
    initMotor(&frontRight, FRONT_RIGHT_PORT, MOTOR_DEFAULT_SLEW_RATE, false);
    initMotor(&liftOne, LIFT_ONE_PORT, MOTOR_DEFAULT_SLEW_RATE, false);
    initMotor(&liftTwo, LIFT_TWO_PORT, MOTOR_DEFAULT_SLEW_RATE, false);
    initMotor(&liftThree, LIFT_THREE_PORT, MOTOR_DEFAULT_SLEW_RATE, false);
    initMotor(&claw, CLAW_PORT, MOTOR_DEFAULT_SLEW_RATE, true);

    motors[0] = &backRight;
    motors[1] = &backLeft;
    motors[2] = &frontLeft;
    motors[3] = &frontRight;
    motors[4] = &liftOne;
    motors[5] = &liftTwo;
    motors[6] = &liftThree;
    motors[7] = &claw;



    gyroOne = gyroInit(GYRO_ONE_PORT, 250);
    gyroTwo = gyroInit(GYRO_TWO_PORT, 0);

    WHEEL_CIR = PI * 4;
    TOLERANCE = .8;
    FULL = (int)((360/WHEEL_CIR)*(PI*14.25) * TOLERANCE);
    QUARTER = FULL / 4;
    HALF = FULL / 2;
    THREE_QUARTER = FULL / 1.5;

    DRIVEBASE_POWER = 63;
    CLAW_POWER = 127;
    LIFT_POWER = 127;
    TURN_MULTIPLIER = 1;

    wheelTargetTicks = 0;
    liftTargetTicks = 0;

    downPressure = false;
    runFinger = false;
    fingerNeedsToOpen = false;
    clawDown = false;
    clawClosing = false;

    wheelDir = FORWARD;
    runWheels = false;

    runLift = false;

    useGyro = false;

    liftQuad = encoderInit(LIFT_QUAD_PORT + 1, LIFT_QUAD_PORT, false);
    rightQuad = encoderInit(RIGHT_QUAD_PORT + 1, RIGHT_QUAD_PORT, false);
    leftQuad = encoderInit(LEFT_QUAD_PORT + 1, LEFT_QUAD_PORT, false);

    liftMonitorHandle = taskCreate(liftMonitorTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
    wheelMonitorHandle = taskCreate(wheelMonitorTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
    motorSlewHandle = taskCreate(motorSlewTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
    clawMonitorHandle = taskCreate(clawMonitorTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

    autonSelection = programSelected(8);
}
