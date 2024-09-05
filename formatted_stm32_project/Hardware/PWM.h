/*
 * @Author: Tianxj22 3456053429@qq.com
 * @Date: 2024-08-13 18:15:51
 * @LastEditors: Tianxj22 3456053429@qq.com
 * @LastEditTime: 2024-08-13 18:31:58
 * @FilePath: \formatted_stm32_project\Hardware\PWM.h
 * @Description: 
 * 
 * Copyright (c) 2024 by Tianxj22, All Rights Reserved. 
 */
#ifndef __PWM__
#define __PWM__

#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"

void PWM_Init(uint32_t PWM_RCC_APB2Periph, GPIO_TypeDef* PWM_GPIO_GROUP, uint16_t UsedGPIO, uint16_t Cycle_ms);
void PWM_SetCompare(uint16_t Compare, uint8_t Order);

#endif