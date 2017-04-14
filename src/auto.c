#include "main.h"

void autonZero(){
    //Left
    DRIVEBASE_POWER = 127;
    setSyncMove(FORWARD, 425 * 1.546, false);
    waitForTasks();
    DRIVEBASE_POWER = 63;
    setSyncMove(RIGHT, QUARTER, false);
    waitForTasks();
    openClaw();
    waitForTasks();
    DRIVEBASE_POWER = 127;
    setSyncMove(FORWARD, 450 * 1.546, false);
    waitForTasks();
    closeClaw(400);
    setSyncLift(HIGH_HEIGHT);
    waitForTasks();
    DRIVEBASE_POWER = 63;
    setSyncMove(LEFT, QUARTER * .85, false);
    waitForTasks();
    DRIVEBASE_POWER = 63;
    setSyncMove(FORWARD, 500 * 1.546, false);
    waitForTasks();
    openClaw();
    setSyncLift(HIGH_HEIGHT + 30);
}

void autonOne(){
    autonZero();

    waitForTasks();
    DRIVEBASE_POWER = 127;
    setSyncMove(BACKWARD, 300 * 1.546, false);
    waitForTasks();
    DRIVEBASE_POWER = 63;
    setSyncMove(RIGHT, HALF, false);
    waitForTasks();
    DRIVEBASE_POWER = 127;
    setSyncMove(BACKWARD, 125 * 1.546, false);
    waitForTasks();
    setSyncLift(DOWN_HEIGHT);
    waitForTasks();
    setSyncMove(FORWARD, 450 * 1.546, false);
    waitForTasks();
    closeClaw(500);
    setSyncMove(BACKWARD, 100 * 1.546, false);
    waitForTasks();
    setSyncLift(HIGH_HEIGHT);
    waitForTasks();
    DRIVEBASE_POWER = 63;
    setSyncMove(LEFT, HALF, false);
    waitForTasks();
    DRIVEBASE_POWER = 127;
    setSyncMove(FORWARD, 600 * 1.546, false);
    waitForTasks();
    openClaw();
    waitForTasks();
}

void autonTwo(){
    //Right
    DRIVEBASE_POWER = 127;
    setSyncMove(FORWARD, 425 * 1.546, false);
    waitForTasks();
    DRIVEBASE_POWER = 63;
    setSyncMove(LEFT, QUARTER, false);
    waitForTasks();
    openClaw();
    waitForTasks();
    DRIVEBASE_POWER = 127;
    setSyncMove(FORWARD, 450 * 1.546, false);
    waitForTasks();
    closeClaw(400);
    setSyncLift(HIGH_HEIGHT);
    waitForTasks();
    DRIVEBASE_POWER = 63;
    setSyncMove(RIGHT, QUARTER * .85, false);
    waitForTasks();
    DRIVEBASE_POWER = 63;
    setSyncMove(FORWARD, 500 * 1.546, false);
    waitForTasks();
    openClaw();
    setSyncLift(HIGH_HEIGHT + 30);
}

void autonThree(){
    //Right Square with Stars
    autonTwo();

    waitForTasks();
    DRIVEBASE_POWER = 127;
    setSyncMove(BACKWARD, 300 * 1.546, false);
    waitForTasks();
    DRIVEBASE_POWER = 63;
    setSyncMove(LEFT, HALF, false);
    waitForTasks();
    DRIVEBASE_POWER = 127;
    setSyncMove(BACKWARD, 125 * 1.546, false);
    waitForTasks();
    setSyncLift(DOWN_HEIGHT);
    waitForTasks();
    setSyncMove(FORWARD, 450 * 1.546, false);
    waitForTasks();
    closeClaw(500);
    setSyncMove(BACKWARD, 100 * 1.546, false);
    waitForTasks();
    setSyncLift(HIGH_HEIGHT);
    waitForTasks();
    DRIVEBASE_POWER = 63;
    setSyncMove(RIGHT, HALF, false);
    waitForTasks();
    DRIVEBASE_POWER = 127;
    setSyncMove(FORWARD, 600 * 1.546, false);
    waitForTasks();
    openClaw();
    waitForTasks();
}

void autonFour(){

}

void autonFive(){

}

void autonSix(){

}

void autonSeven(){

}

void autonEight(){

}

void autonNine(){

}

void autonTen(){

}

void autonEleven(){

}

void autonTwelve(){

}

void autonThirteen(){
    setSyncMove(FORWARD, 100 * 1.546, false);
    waitForTasks();
    openClaw();
    waitForTasks();
    taskDelay(200);
    setSyncLift(650);
    waitForTasks();
    setSyncMove(BACKWARD, 100 * 1.546, false);
    waitForTasks();
    taskDelay(1500);
    closeClaw(750);
    taskDelay(1500);
    setSyncMove(FORWARD, 950 * 1.546, false);
    waitForTasks();
    openClaw(); //Drop 3 star and cube combo
    waitForTasks();

    setSyncMove(BACKWARD, 950 * 1.546, false);
    waitForTasks();
    taskDelay(1000);
    closeClaw(750);
    taskDelay(1000);
    setSyncMove(FORWARD, 950 * 1.546, false);
    waitForTasks();
    openClaw();
    waitForTasks(); //Drop the one cube preload

    setSyncMove(BACKWARD, 475 * 1.546, false);
    waitForTasks();
    setSyncMove(RIGHT, QUARTER, false);
    waitForTasks();
    setSyncLift(25);
    waitForTasks();
    setSyncMove(FORWARD, 350 * 1.546, false);
    waitForTasks();
    closeClaw(400);
    setSyncLift(HIGH_HEIGHT);
    waitForTasks();
    setSyncMove(FORWARD, 100 * 1.546, false);
    waitForTasks();
    taskDelay(400);
    setSyncMove(LEFT, QUARTER, false);
    waitForTasks();
    setSyncMove(FORWARD, 475 * 1.546, false);
    waitForTasks();
    openClaw(); //Drop field cube

    waitForTasks();
    setSyncMove(BACKWARD, 275 * 1.546, false);
    waitForTasks();
    taskDelay(400);
    setSyncMove(RIGHT, HALF, false);
    waitForTasks();
    setSyncMove(BACKWARD, 100 * 1.546, false);
    waitForTasks();
    setSyncLift(DOWN_HEIGHT);
    waitForTasks();
    DRIVEBASE_POWER = 127;
    setSyncMove(FORWARD, 350 * 1.546, false);
    waitForTasks();
    closeClaw(750);
    setSyncMove(BACKWARD, 275 * 1.546, false);
    waitForTasks();
    setSyncLift(625);
    waitForTasks();
    DRIVEBASE_POWER = 63;
    setSyncMove(LEFT, HALF, false);
    waitForTasks();
    taskDelay(400);
    setSyncMove(FORWARD, 350 * 1.546, false);
    waitForTasks();
    openClaw(); //Drop field stars

    waitForTasks();
    setSyncMove(BACKWARD, 400 * 1.546, false);
    waitForTasks();
    setSyncLift(50);
    waitForTasks();
    setSyncMove(FORWARD, 400 * 1.546, false);
    waitForTasks();
    closeClaw(750);
    setSyncMove(BACKWARD, 400 * 1.546, false);
    waitForTasks();
    setSyncLift(625);
    waitForTasks();
    setSyncMove(FORWARD, 500 * 1.546, false);
    waitForTasks();
    openClaw();
    waitForTasks(); //Drop fence stars
}

void autonFourteen(){
    setSyncMove(FORWARD, 200 * 1.546, false);
    waitForTasks();
    openClaw();
    waitForTasks();
    delay(200);
    setSyncLift(HIGH_HEIGHT);
    waitForTasks();
    setSyncMove(BACKWARD, 200 * 1.546, false);
    waitForTasks();
    delay(1500);
    closeClaw(300);
    delay(1500);
    setSyncMove(FORWARD, 1300 * 1.546, false);
    waitForTasks();
    openClaw(); //Drop 3 star and cube combo
    waitForTasks();

    setSyncMove(BACKWARD, 1300 * 1.546, false);
    waitForTasks();
    delay(1000);
    closeClaw(300);
    delay(1000);
    setSyncMove(FORWARD, 1300 * 1.546, false);
    waitForTasks();
    openClaw();
    waitForTasks(); //Drop the one cube preload

    setSyncMove(BACKWARD, 1300 * 1.546, false);
    waitForTasks();
    gyroReset(gyroOne);
    gyroReset(gyroTwo);
    delay(1500);
    setSyncMove(FORWARD,450 * 1.546, false);
    waitForTasks();
    delay(400);
    setSyncMove(RIGHT, -90, true);
    waitForTasks();
    setSyncLift(DOWN_HEIGHT);
    waitForTasks();
    setSyncMove(FORWARD, 500 * 1.546, false);
    waitForTasks();
    closeClaw(300);
    waitForTasks();
    setSyncLift(HIGH_HEIGHT);
    waitForTasks();
    setSyncMove(FORWARD, 850 * 1.546, false);
    waitForTasks();
    setSyncMove(LEFT, 0, true);
    waitForTasks();
    setSyncMove(FORWARD, 500 * 1.546, false);
    waitForTasks();
    openClaw();
    waitForTasks();

    setSyncMove(BACKWARD, 400 * 1.546, false);
    waitForTasks();
    setSyncMove(RIGHT, -150, true);
    waitForTasks();
    setSyncMove(BACKWARD, 200 * 1.546, false);
    waitForTasks();
    setSyncLift(DOWN_HEIGHT);
    waitForTasks();
    setSyncMove(FORWARD, 600 * 1.546, false);
    waitForTasks();
    closeClaw(300);
    setSyncMove(BACKWARD, 400 * 1.546, false);
    waitForTasks();
    setSyncLift(HIGH_HEIGHT);
    waitForTasks();
    setSyncMove(LEFT, -5, true);
    waitForTasks();
    setSyncMove(FORWARD, 800 * 1.546, false);
    waitForTasks();
    openClaw();
    waitForTasks();

    setSyncMove(BACKWARD, 200 * 1.546, false);
    waitForTasks();
    setSyncMove(LEFT, 150, true);
    waitForTasks();
    setSyncLift(DOWN_HEIGHT);
    waitForTasks();
    setSyncMove(FORWARD, 900 * 1.546, false);
    waitForTasks();
    closeClaw(400);
    setSyncMove(BACKWARD, 500 * 1.546, false);
    waitForTasks();
    setSyncLift(HIGH_HEIGHT);
    waitForTasks();
    setSyncMove(RIGHT, 0, true);
    waitForTasks();
    setSyncMove(FORWARD, 500 * 1.546, false);
    waitForTasks();
    openClaw();
    waitForTasks();
}

void autonomous() {
    autonSelection = programSelected(8);
    switch(autonSelection){
        case 0:
        autonZero();
        break;
        case 1:
        autonOne();
        break;
        case 2:
        autonTwo();
        break;
        case 3:
        autonThree();
        break;
        case 4:
        autonFour();
        break;
        case 5:
        autonFive();
        break;
        case 6:
        autonSix();
        break;
        case 7:
        autonSeven();
        break;
        case 8:
        autonEight();
        break;
        case 9:
        autonNine();
        break;
        case 10:
        autonTen();
        break;
        case 11:
        autonEleven();
        break;
        case 12:
        autonTwelve();
        break;
        case 13:
        autonThirteen();
        break;
        case 14:
        autonFourteen();
        break;
        default:
        break;
    }

}
