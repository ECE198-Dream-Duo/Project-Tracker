#include <stdint.h>
#include <math.h>
#include "main.h"

#ifndef MPU6050_H
#define MPU6050_H
typedef struct {
    int16_t accelX_RAW;
    int16_t accelY_RAW;
    int16_t accelZ_RAW;
    double accelX;
    double accelY;
    double accelZ;

    int16_t gyroX_RAW;
    int16_t gyroY_RAW;
    int16_t gyroZ_RAW;
    double gyroX;
    double gyroY;
    double gyroZ;

    int16_t temp_RAW;
    double temp;

    double pitchAngle;
    double rollAngle;
    double yawAngle;

    double dt;
    double normalizeTick;
} MPU6050;

int mpu6050Init(I2C_HandleTypeDef *hi2c);

void readAccelData(I2C_HandleTypeDef *hi2c, MPU6050* data);

void readGyroData(I2C_HandleTypeDef *hi2c, MPU6050* data);

void readTempData(I2C_HandleTypeDef *hi2c, MPU6050* data);

void calculateAngleAccel(I2C_HandleTypeDef *hi2c, MPU6050* data);

void calculateAngleGyro(MPU6050* data);

void readGyroGx(I2C_HandleTypeDef *hi2c, MPU6050* data);

void readAccelAx(I2C_HandleTypeDef *hi2c, MPU6050* data);

#endif