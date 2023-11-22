#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"
#include "mpu6050.h"

#ifndef PID_H
#define PID_H
typedef struct {
    double ki;
    double kp;
    double kd;

    // error to pass into feedback loop 
    double error;

    // previous error that was passed 
    double pastError;

    int integralCap;

    double porportional;
    double derivative;
    double integral;

    double setPoint;
    double output;
} pid;

void setParam(pid* pid, double kp, double ki, double kd, double setPoint);

void calculatePID(pid* pid, MPU6050* imu);
#endif
