#include "IRSesnsor.h"

ADC_HandleTypeDef IRInitialize(int waittime) {
  // GPIO
  // Configuration for one pin
  GPIO_InitTypeDef GPIOConfig = {
    .Pin = PINOUTPUT,
    .Mode = GPIO_MODE_IT_FALLING,
    .Pull = GPIO_NOPULL,
    .Speed = GPIO_SPEED_FREQ_LOW
  };
  HAL_GPIO_Init(PINGROUP, &GPIOConfig);

  // ADC Initialization
  ADC_ChannelConfTypeDef ADCConfig = {
    .Channel = ADC_CHANNEL_0, // GPIO0
    .Rank = 1,
    .SamplingTime = ADC_SAMPLETIME_3CYCLES
  };

  ADC_HandleTypeDef hadc1 = {
    .Instance = ADC1,
    .Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4,
    .Init.Resolution = ADC_RESOLUTION_12B,
    .Init.ScanConvMode = DISABLE,
    .Init.ContinuousConvMode = DISABLE,
    .Init.DiscontinuousConvMode = DISABLE,
    .Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE,
    .Init.ExternalTrigConv = ADC_SOFTWARE_START,
    .Init.DataAlign = ADC_DATAALIGN_RIGHT,
    .Init.NbrOfConversion = 1,
    .Init.DMAContinuousRequests = DISABLE,
    .Init.EOCSelection = ADC_EOC_SINGLE_CONV
  };
  if (HAL_ADC_Init(&hadc1) != HAL_OK || HAL_ADC_ConfigChannel(&hadc1, &ADCConfig) != HAL_OK) {
    Error_Handler();
  }

  HAL_ADC_Start(&hadc1);
  HAL_ADC_PollForConversion(&hadc1, waittime);

  return hadc1;
}

uint32_t Configure(ADC_HandleTypeDef setup) {
  /*
  uint32_t whiteValue = NULL, blackValue = NULL;
  while(whiteValue == NULL && blackValue == NULL) {
    uint32_t adcValue = HAL_ADC_GetValue(&setup);
    // Get Button Press to indicate white paper is over
    // Get Button Press to indicate black paper is over
  }
  return (whiteValue + blackValue) / 2;\
  */

  // Temporary solution manually finding the threshold
  uint32_t adcValue = HAL_ADC_GetValue(&setup);
}

void Deinitialize(ADC_HandleTypeDef programkey) {
  HAL_ADC_Stop(&programkey);
}

#define WINDOW_SIZE 10
// Get Color using simple moving aver
bool GetColor(ADC_HandleTypeDef setup, int iterations) {
  int *arr = (int*)malloc(sizeof(int)*iterations);
  for (int i = 0; i < iterations; i++) {
    arr[i] = HAL_ADC_GetValue(&setup);
  }
  uint32_t threshold = Configure(setup);
  uint32_t valueaverage = FilterData(arr, iterations);
  free(arr);
  return (valueaverage > threshold ? true : false);
}

double FilterData(int* datainput, size_t arrsize) {
  double sum = 0.0;

  for (int i = 0; i < WINDOW_SIZE; i++) {
      sum += datainput[i % arrsize];
  }

  return sum / WINDOW_SIZE;
}