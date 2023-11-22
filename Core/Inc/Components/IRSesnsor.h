#pragma once

#include "stm32f4xx_hal_adc.h"
#include "stm32f4xx_hal_gpio.h"
#include <stdbool.h>
#include "stdint.h"
#include "stm32f401xe.h"

// Define pins spots
#define PINGROUP GPIOA
#define PININPUT GPIO_PIN_0
#define PINOUTPUT GPIO_PIN_4

ADC_HandleTypeDef IRInitialize(int waittime);
uint32_t Configure(ADC_HandleTypeDef setup);

/*
* Returns black as true
* Returns white as false 
*/
bool GetColor();

/*
* Using Simple moving average filter to filter out IR sensor data
*/
double FilterData(int* datainput, size_t arrsize);