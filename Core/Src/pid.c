#include "pid.h"

void setParam(pid* pid, double kp, double ki, double kd, double setPoint) {
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->pastError = 0;
    pid->integral = 0;
    pid->setPoint = setPoint;

    pid->integralCap = 150;
}

void calculatePID(pid* pid, MPU6050* imu) {
    pid->error = pid->setPoint - imu->yawAngle;

    pid->porportional = pid->kp*pid->error;

    if (abs(pid->integral + pid->error*imu->dt) > pid->integralCap) {
        pid->integral = 0;
        pid->integral = pid->integral + pid->error*imu->dt;
    }
    else {
        pid->integral = pid->integral + pid->error*imu->dt;
    }

    pid->derivative = pid->kd*(pid->error-pid->pastError);

    pid->pastError = pid->error;
    pid->output = pid->porportional + pid->integral + pid->derivative;
}
