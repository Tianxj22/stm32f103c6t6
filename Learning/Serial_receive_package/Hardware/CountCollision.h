#ifndef __COUNT_COLLISION__
#define __COUNT_COLLISION__

#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"

void CountCollision_Init(void);
uint8_t CountCollision_Get(void);
void EXTI15_10_IRQHandler(void);

#endif