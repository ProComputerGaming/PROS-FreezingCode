#include "main.h"

void autonZero(){
    //Left
    setSyncMove(FORWARD, 400);
    waitForTasks();
    setSyncMove(RIGHT, QUARTER);
    waitForTasks();
    openClaw();
    waitForTasks();
    setSyncMove(FORWARD, 475);
    waitForTasks();
    closeClaw(750);
    setSyncLift(HIGH_HEIGHT);
    waitForTasks();
    setSyncMove(LEFT, QUARTER);
    waitForTasks();
    setSyncMove(FORWARD, 400);
    setSyncLift(HIGH_HEIGHT);
    waitForTasks();
    openClaw();
    setSyncLift(HIGH_HEIGHT - 20);
}

void autonOne(){
    autonZero();

    waitForTasks();
    setSyncMove(BACKWARD, 300);
    waitForTasks();
    setSyncMove(RIGHT, HALF + 10);
    waitForTasks();
    setSyncMove(BACKWARD, 75);
    setSyncLift(DOWN_HEIGHT);
    waitForTasks();
    setSyncMove(FORWARD, 350);
    waitForTasks();
    closeClaw(750);
    setSyncMove(BACKWARD, 100);
    waitForTasks();
    setSyncLift(HIGH_HEIGHT);
    waitForTasks();
    setSyncMove(LEFT, HALF + 85);
    waitForTasks();
    setSyncMove(FORWARD, 400);
    waitForTasks();
    setSyncMove(FORWARD, 75);
    openClaw();
    waitForTasks();
}

void autonTwo(){
    //Right square
    setSyncMove(FORWARD, 400);
    waitForTasks();
    setSyncMove(LEFT, QUARTER);
    waitForTasks();
    openClaw();
    waitForTasks();
    setSyncMove(FORWARD, 475);
    waitForTasks();
    closeClaw(750);
    setSyncLift(HIGH_HEIGHT);
    waitForTasks();
    setSyncMove(RIGHT, QUARTER);
    waitForTasks();
    setSyncMove(FORWARD, 400);
    setSyncLift(HIGH_HEIGHT);
    waitForTasks();
    openClaw();
    setSyncLift(HIGH_HEIGHT - 20);
}

void autonThree(){
    //Right Square with Stars
    autonTwo();

    waitForTasks();
    setSyncMove(BACKWARD, 300);
    waitForTasks();
    setSyncMove(LEFT, HALF + 50);
    waitForTasks();
    setSyncMove(BACKWARD, 75);
    setSyncLift(DOWN_HEIGHT);
    waitForTasks();
    setSyncMove(FORWARD, 350);
    waitForTasks();
    closeClaw(750);
    setSyncMove(BACKWARD, 100);
    waitForTasks();
    setSyncLift(HIGH_HEIGHT);
    waitForTasks();
    setSyncMove(RIGHT, HALF + 100);
    waitForTasks();
    setSyncMove(FORWARD, 350);
    waitForTasks();
    openClaw();
    waitForTasks();
}

void autonFour(){
//Left Anti-Middle
    setSyncMove(FORWARD, 100);
    waitForTasks();
    openClaw();
    waitForTasks();
    setSyncLift(HIGH_HEIGHT + 35);
    waitForTasks();
    setSyncMove(FORWARD, 750);
    waitForTasks();
    setSyncMove(RIGHT, THREE_QUARTER + 100);
    waitForTasks();
    setSyncLift(DOWN_HEIGHT);
    waitForTasks();
    setSyncMove(FORWARD, 750);
    waitForTasks();
    closeClaw(750);
    waitForTasks();
    setSyncMove(BACKWARD, 250);
    waitForTasks();
    setSyncLift(HIGH_HEIGHT);
    waitForTasks();
    setSyncMove(LEFT, HALF + 100);
    waitForTasks();
    setSyncMove(FORWARD, 700);
    waitForTasks();
    openClaw();
    waitForTasks();

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

}

void autonFourteen(){
    setSyncMove(FORWARD, 100);
    waitForTasks();
    openClaw();
    waitForTasks();
    taskDelay(200);
    setSyncLift(650);
    waitForTasks();
    setSyncMove(BACKWARD, 100);
    waitForTasks();
    taskDelay(1500);
    closeClaw(750);
    taskDelay(1500);
    setSyncMove(FORWARD, 950);
    waitForTasks();
    openClaw(); //Drop 3 star and cube combo
    waitForTasks();

    setSyncMove(BACKWARD, 950);
    waitForTasks();
    taskDelay(1000);
    closeClaw(750);
    taskDelay(1000);
    setSyncMove(FORWARD, 950);
    waitForTasks();
    openClaw();
    waitForTasks(); //Drop the one cube preload

    setSyncMove(BACKWARD, 475);
    waitForTasks();
    setSyncMove(RIGHT, QUARTER);
    waitForTasks();
    setSyncLift(25);
    waitForTasks();
    setSyncMove(FORWARD, 350);
    waitForTasks();
    closeClaw(400);
    setSyncLift(625);
    waitForTasks();
    setSyncMove(FORWARD, 100);
    waitForTasks();
    taskDelay(400);
    setSyncMove(LEFT, QUARTER);
    waitForTasks();
    setSyncMove(FORWARD, 475);
    waitForTasks();
    openClaw(); //Drop field cube

    waitForTasks();
    setSyncMove(BACKWARD, 275);
    waitForTasks();
    taskDelay(400);
    setSyncMove(RIGHT, HALF + 50);
    waitForTasks();
    setSyncMove(BACKWARD, 100);
    waitForTasks();
    setSyncLift(25);
    waitForTasks();
    DRIVEBASE_POWER = 127;
    setSyncMove(FORWARD, 350);
    waitForTasks();
    closeClaw(750);
    setSyncMove(BACKWARD, 275);
    waitForTasks();
    setSyncLift(625);
    waitForTasks();
    DRIVEBASE_POWER = 63;
    setSyncMove(LEFT, HALF + 50);
    waitForTasks();
    taskDelay(400);
    setSyncMove(FORWARD, 350);
    waitForTasks();
    openClaw(); //Drop field stars

    waitForTasks();
    setSyncMove(BACKWARD, 400);
    waitForTasks();
    setSyncLift(50);
    waitForTasks();
    setSyncMove(FORWARD, 400);
    waitForTasks();
    closeClaw(750);
    setSyncMove(BACKWARD, 400);
    waitForTasks();
    setSyncLift(625);
    waitForTasks();
    setSyncMove(FORWARD, 500);
    waitForTasks();
    openClaw();
    waitForTasks(); //Drop fence stars
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
