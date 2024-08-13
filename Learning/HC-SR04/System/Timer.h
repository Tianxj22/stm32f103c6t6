#ifndef __TIMER__
#define __TIMER__

#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"

void Timer_Init(void);
uint32_t Timer_GetTime_us(void);
void Timer_ResetTime(void);

#endif