/*
 * @Author: Tianxj22 3456053429@qq.com
 * @Date: 2024-08-13 13:55:58
 * @LastEditors: Tianxj22 3456053429@qq.com
 * @LastEditTime: 2024-08-13 14:38:09
 * @FilePath: \f103c6t6\formatted_stm32_project\Hardware\LED.h
 * @Description: 
 * 
 * Copyright (c) 2024 by Tianxj22, All Rights Reserved. 
 */
#ifndef __LED__
#define __LED__

#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"

void LED_Init(uint32_t _LED_RCC_APB2Periph, GPIO_TypeDef* _LED_GPIO_GROUP, uint16_t* UsedGPIO, uint8_t TotalUsedNum);
uint8_t LED_On(uint8_t LED_Order);
uint8_t LED_Off(uint8_t LED_Order);
uint8_t LED_Turn(uint8_t LED_Order);

#endif