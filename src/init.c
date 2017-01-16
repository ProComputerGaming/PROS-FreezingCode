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
  autonSelection = programSelected(8);

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

  liftQuad = encoderInit(liftQuadPort + 1, liftQuadPort, false);
  rightQuad = encoderInit(rightQuadPort + 1, rightQuadPort, false);
  leftQuad = encoderInit(leftQuadPort + 1, leftQuadPort, false);

  digitalWrite(leftFingerSwitchPort, LOW);
  digitalWrite(rightFingerSwitchPort, LOW);

  TaskHandle liftMonitorHandle = taskCreate(liftMonitor, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  TaskHandle wheelMonitorHandle = taskCreate(wheelMonitor, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  TaskHandle motorSlewHandle = taskCreate(motorSlewTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  TaskHandle fingerMonitorHandle = taskCreate(fingerMonitor, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}
