#ifndef __KEY__
#define __KEY__

#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"
#include "Delay.h"

void Key_Init(void);
uint8_t GetKey(void);

#endif