#include "main.h"

void clawMonitorTask(void *parameter){
    while(true){
        bool down = downPressure;
        bool run = runFinger;
        bool closing = clawClosing;

        bool open = (digitalRead(LEFT_CLAW_SWITCH_PORT) == 1 || digitalRead(RIGHT_CLAW_SWITCH_PORT) == 1);

        if(closing == false){ //If in Auto and CLAW_PORT is not closing
            if(run == false){
                if(down == true){
                    setMotor(&claw, 15);
                }else if(down == false){
                    setMotor(&claw, -5);
                }else{
                    open = (digitalRead(LEFT_CLAW_SWITCH_PORT) == 1 || digitalRead(RIGHT_CLAW_SWITCH_PORT) == 1);
                }
            }
        }

        while(run && open){
            setMotor(&claw, -127);
            open = (digitalRead(LEFT_CLAW_SWITCH_PORT) == 1 || digitalRead(RIGHT_CLAW_SWITCH_PORT) == 1);
            if(open == false || (joystickGetDigital(1, 5, JOY_DOWN) && !isAutonomous())){
                run = false;

                runFinger = false;
            }
            delay(20);
        }
        delay(20);
    }
}

void closeClaw(int millis){
    downPressure = true;

    runFinger = false;

    clawClosing = true;

    if(millis != 0){
        setMotor(&claw, CLAW_POWER);

        delay(millis);

        setMotor(&claw, 0);

        clawClosing = false;
    }else{
        setMotor(&claw, CLAW_POWER);
    }

}

void openClaw(){

    clawClosing = false;

    setMotor(&claw, -CLAW_POWER);

    downPressure = false;

    runFinger = true;

}
