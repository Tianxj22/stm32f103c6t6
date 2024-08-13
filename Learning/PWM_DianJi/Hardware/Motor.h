#ifndef __MOTOR__
#define __MOTOR__

#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"
#include "PWM.h"

void Motor_Init(void);
void Motor_SetSpeed(int8_t Speed);

#endif