/*
 * @Author: Tianxj22 3456053429@qq.com
 * @Date: 2024-08-13 13:55:58
 * @LastEditors: Tianxj22 3456053429@qq.com
 * @LastEditTime: 2024-08-13 15:00:44
 * @FilePath: \f103c6t6\formatted_stm32_project\Hardware\Key.h
 * @Description: 
 * 
 * Copyright (c) 2024 by Tianxj22, All Rights Reserved. 
 */
#ifndef __KEY__
#define __KEY__

#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"
#include "Delay.h"

void Key_Init(uint32_t Key_RCC_APB2Periph, GPIO_TypeDef* Key_GPIO_GROUP, uint16_t* UsedGPIO, uint8_t TotalUsedNum);
uint8_t GetKey(void);

#endif