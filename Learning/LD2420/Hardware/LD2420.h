#ifndef __LD2420__
#define __LD2420__

#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"
#include "Serial.h"

void LD2420_Init(void);
uint8_t LD2420_GetDataFlag(void);
uint32_t LD2420_GetData(void);
void LD2420_GetVersionNum(void);
uint8_t LD2420_GetOT2Data(void);

#endif