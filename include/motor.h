#ifndef MOTOR_H_
#define MOTOR_H_
#include <API.h>

#define MOTOR_NUM 8
#define MOTOR_MAX_VALUE 127
#define MOTOR_MIN_VALUE -127
#define MOTOR_DEFAULT_SLEW_RATE 20
#define MOTOR_FAST_SLEW_RATE 256
#define MOTOR_TASK_DELAY 20
#define MOTOR_DEADBAND 10

    typedef struct Motor{
        int speed;
        int requestedSpeed;
        int slewRate;
        int port;
        bool reversed;
    } Motor;

    Motor *motors[MOTOR_NUM];

    TaskHandle motorSlewHandle;

    void motorSlewTask(void *parameter);
    void initMotor(Motor *motor, int port, int slewRate, bool reversed);
    bool setMotor(Motor *motor, int speed);



#endif
