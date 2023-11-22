#include "mpu6050.h"

#define RAD_TO_DEG 57.295779513082320876798154814105

#define MPU6050_ADDR 0X68 << 1
#define MPU6050_WHO_AM_I 0x75
#define MPU6050_PWR_MGMT_REG 0x6B
#define MPU6050_SMPLPT_DIV_REG 0x19
#define MPU6050_ACCEL_CONFIG_REG 0x1C
#define MPU6050_GYRO_CONFIG_REG 0x1B
#define MPU6050_ACCEL_MEASR_REG 0x3B
#define MPU6050_GYRO_MEASR_REG 0x43
#define MPU6050_TEMP_MEASR_REG 0x41
#define HAL_TIMEOUT 5
#define INTEGRAL_CAP_STRAIGHT_LINE 15

#define ERROR_
double timer = 0;

int mpu6050Init(I2C_HandleTypeDef *hi2c) {
    uint8_t check;
    uint8_t data;
    HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, MPU6050_WHO_AM_I, 1, &check, 1, HAL_TIMEOUT);
    if (check != 0x68) {
        return 0;
    }
    // wake up mpu6050 by clearing all bits in 0x6B register
    data = 0;
    HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, MPU6050_PWR_MGMT_REG, 1, &data, 1, HAL_TIMEOUT);

    // configer data sample rate to 1khz
    data = 0x07;
    HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, MPU6050_SMPLPT_DIV_REG, 1, &data, 1, HAL_TIMEOUT);

    // Set accelerometer config to +- 2g
    data = 0x00;
    HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, MPU6050_ACCEL_CONFIG_REG, 1, &data, 1, HAL_TIMEOUT);

    // Set gyroscope config to +- 250dps
    data = 0x00;
    HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, MPU6050_GYRO_CONFIG_REG, 1, &data, 1, HAL_TIMEOUT);
    return 1;
}

void readAccelData(I2C_HandleTypeDef *hi2c, MPU6050* data) {
    uint8_t rawData[6];
    HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, MPU6050_ACCEL_MEASR_REG, 1, rawData, 6, HAL_TIMEOUT);
    data->accelX_RAW = (((int16_t)(rawData[0] << 8 | rawData[1])));
    data->accelY_RAW = (((int16_t)(rawData[2] << 8 | rawData[3])));
    data->accelZ_RAW = (((int16_t)(rawData[4] << 8 | rawData[5])));

    data->accelX = data->accelX_RAW / 16384.0 - 0.20849609375; 
    data->accelY = data->accelY_RAW / 16384.0 - 0.02587890625;
    data->accelZ = data->accelZ_RAW / 16384.0 - 0.154541015625;

}

void readGyroData(I2C_HandleTypeDef *hi2c, MPU6050* data) {
    uint8_t rawData[6];
    HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, MPU6050_GYRO_MEASR_REG, 1, rawData, 6, HAL_TIMEOUT);
    data->gyroX_RAW = (((int16_t)(rawData[0] << 8 | rawData[1])));
    data->gyroY_RAW = (((int16_t)(rawData[2] << 8 | rawData[3])));
    data->gyroZ_RAW = (((int16_t)(rawData[4] << 8 | rawData[5])));

    data->gyroX = data->gyroX_RAW / 131.0 + 3.0;
    data->gyroY = data->gyroY_RAW / 131.0 - 3.282442748091603;
    data->gyroZ = data->gyroZ_RAW / 131.0 + 2.9847328244274811;
}

void readTempData(I2C_HandleTypeDef *hi2c, MPU6050* data) {
    int8_t rawData[2];
    HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, MPU6050_TEMP_MEASR_REG, 1, rawData, 2, HAL_TIMEOUT);
    data->temp_RAW = (((int16_t)(rawData[0] << 8 | rawData[1])));

    data->temp = ((double)data->temp_RAW / 340.0) + 36.53;
}

void calculateAngleAccel(I2C_HandleTypeDef *hi2c, MPU6050* data) {
    double rollDenominator = sqrt(pow((double)(data->accelX),2) + pow((double)(data->accelZ),2)); 
    double pitchDenominator = sqrt(pow((double)(data->accelY),2) + pow((double)(data->accelZ),2)); 

    if (rollDenominator != 0.0) {
        data->rollAngle = atan((double)(data->accelY)/rollDenominator) * RAD_TO_DEG;
    }
    else {
        data->rollAngle = 0.0;
    }
    if (pitchDenominator != 0.0) {
        data->pitchAngle = atan((-1*(double)(data->accelX))/pitchDenominator) * RAD_TO_DEG;
    }
    else {
        data->pitchAngle = 0.0;
    }
}

void calculateAngleGyro(MPU6050* data) {
    data->normalizeTick = ((double)(HAL_GetTick()) / 1000.0 ) - 5.0;
    data->dt = (data->normalizeTick - timer) / 1000.0;
    if (abs(data->yawAngle) + abs(data->gyroZ*data->dt) > INTEGRAL_CAP_STRAIGHT_LINE) {
        data->yawAngle = 0;
        data->yawAngle = data->yawAngle + data->gyroZ*data->dt;
    }
    else {
        data->yawAngle = data->yawAngle + data->gyroZ*data->dt;
    }
    timer = ((double)HAL_GetTick() / 1000.0) - 5;
}

void readGyroGx(I2C_HandleTypeDef *hi2c, MPU6050*data) {
    uint8_t rawData[2];
    HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, MPU6050_GYRO_MEASR_REG, 1, rawData, 2, HAL_TIMEOUT);
    data->gyroX_RAW = (int16_t)(rawData[0] << 8 | rawData[1]);
    data->gyroX = data->gyroX_RAW / 131.0;
}

void readAccelAx(I2C_HandleTypeDef *hi2c, MPU6050*data) {
    uint8_t rawData[2];
    HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, MPU6050_ACCEL_MEASR_REG, 1, rawData, 2, HAL_TIMEOUT);
    data->accelX_RAW = (int16_t)(rawData[0] << 8 | rawData[1]);
    data->accelX = data->accelX_RAW / 131.0;
    return;
}