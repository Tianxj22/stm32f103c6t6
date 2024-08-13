#ifndef __LED__
#define __LED__

#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"

#define LED_RCC_APB2Periph RCC_APB2Periph_GPIOC
#define LED_GPIO_GROUP GPIOC

void LED_Init(uint16_t* UsedGPIO, uint8_t TotalUsedNum);
uint8_t LED_On(uint8_t LED_Order);
uint8_t LED_Off(uint8_t LED_Order);
uint8_t LED_Turn(uint8_t LED_Order);

#endif