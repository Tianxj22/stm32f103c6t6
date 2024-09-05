/*
 * @Author: Tianxj22 3456053429@qq.com
 * @Date: 2024-08-13 18:15:51
 * @LastEditors: Tianxj22 3456053429@qq.com
 * @LastEditTime: 2024-08-13 18:28:14
 * @FilePath: \formatted_stm32_project\Hardware\PWM.c
 * @Description: 
 * 
 * Copyright (c) 2024 by Tianxj22, All Rights Reserved. 
 */
#include "PWM.h"

uint16_t _Cycle_ms;

/**
 * @brief: 初始化PWM接口
 * @param PWM_RCC_APB2Periph GPIO接口的时钟源, 可选参数如RCC_APB2Periph_GPIOA
 * @param PWM_GPIO_GROUP GPIO族, 可选参数如GPIOA
 * @param UsedGPIO 使用的接口, 可用如0-3
 * @param Cycle_ms 一个周期为多少ms
 * @return 
 */
void PWM_Init(uint32_t PWM_RCC_APB2Periph, GPIO_TypeDef* PWM_GPIO_GROUP, uint16_t UsedGPIO, uint16_t Cycle_ms)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = UsedGPIO;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    RCC_APB2PeriphClockCmd(PWM_RCC_APB2Periph, ENABLE);

    GPIO_Init(PWM_GPIO_GROUP, &GPIO_InitStructure);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_InternalClockConfig(TIM2);

    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 1000 * Cycle_ms - 1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 90;
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);

    TIM_Cmd(TIM2, ENABLE);

    _Cycle_ms = Cycle_ms;
}

/**
 * @brief 修改PWM波的compare值
 * @param Compare PWM波中高电平的占比(单位为千分之一)
 */
void PWM_SetCompare1(uint16_t Compare)
{
    TIM_SetCompare1(TIM2, Compare * _Cycle_ms);
}