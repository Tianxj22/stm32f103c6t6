#ifndef __HC_SR04__
#define __HC_SR04__

#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"
#include "Timer.h"

#define HCSR04_RCC_APB2Periph RCC_APB2Periph_GPIOA
#define HCSR04_GPIO_GROUP GPIOA
#define HCSR04_TRIG_PIN GPIO_Pin_3
#define HCSR04_ECHO_PIN GPIO_Pin_4

void HCSR04_Init(void);
float HCSR04_GetDistance(void);

#endif