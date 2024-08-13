#ifndef __ENCODER__
#define __ENCODER__

#include "stm32f10x.h"                  // Device header
// #define USE_STDPERIPH_DRIVER
// #include "stm32f10x_conf.h"

void Encoder_Init(void);
uint8_t Encoder_Get(void);

#endif