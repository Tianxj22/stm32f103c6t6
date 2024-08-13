#ifndef __PWM__
#define __PWM__

#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"

void PWM_Init(void);
void PWM_SetCompare1(uint16_t Compare);

#endif