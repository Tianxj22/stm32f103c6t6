/*
 * @Author: Tianxj22 3456053429@qq.com
 * @Date: 2024-08-13 18:15:51
 * @LastEditors: Tianxj22 3456053429@qq.com
 * @LastEditTime: 2024-09-05 22:59:11
 * @FilePath: \formatted_stm32_project\Hardware\PWM.c
 * @Description: 
 * 
 * Copyright (c) 2024 by Tianxj22, All Rights Reserved. 
 */
#include "PWM.h"

uint16_t _Cycle_ms[4] = {1, 1, 1, 1};

/**
 * @brief: 内部函数, 将序号数转化成接口
 * @param Order 序号
 * @retval: 对应的接口
 */
uint16_t _OrderToPin(uint16_t Order)
{
    if(Order == 0)
    {
        return GPIO_Pin_0;
    }
    if(Order == 1)
    {
        return GPIO_Pin_1;
    }
    if(Order == 2)
    {
        return GPIO_Pin_2;
    }
    if(Order == 3)
    {
        return GPIO_Pin_3;
    }
}

/**
 * @brief: 初始化PWM接口
 * @param PWM_RCC_APB2Periph GPIO接口的时钟源, 可选参数如RCC_APB2Periph_GPIOA
 * @param PWM_GPIO_GROUP GPIO族, 可选参数如GPIOA
 * @param UsedOrder 使用的接口, 可选用的值从0-3
 * @param Cycle_ms 一个周期为多少ms
 * @return 
 */
void PWM_Init(uint32_t PWM_RCC_APB2Periph, GPIO_TypeDef* PWM_GPIO_GROUP, uint16_t UsedOrder, uint16_t Cycle_ms)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = _OrderToPin(UsedOrder);
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    RCC_APB2PeriphClockCmd(PWM_RCC_APB2Periph, ENABLE);

    GPIO_Init(PWM_GPIO_GROUP, &GPIO_InitStructure);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_InternalClockConfig(TIM2);

    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 90;
    if(UsedOrder == 0)
    {
        TIM_OC1Init(TIM2, &TIM_OCInitStructure);
    }
    else if(UsedOrder == 1)
    {
        TIM_OC2Init(TIM2, &TIM_OCInitStructure);
    }
    else if(UsedOrder == 2)
    {
        TIM_OC3Init(TIM2, &TIM_OCInitStructure);
    }
    else if(UsedOrder == 3)
    {
        TIM_OC4Init(TIM2, &TIM_OCInitStructure);
    }

    TIM_Cmd(TIM2, ENABLE);

    _Cycle_ms[UsedOrder] = Cycle_ms;
}

/**
 * @brief 修改PWM波的compare值
 * @param Compare PWM波中高电平的占比(单位为千分之一)
 */

/**
 * @brief: 修改PWM波的compare值
 * @param Compare PWM波中高电平的占比(单位为千分之一)
 * @param Order PWM的序号, 
 * @retval: 
 */
void PWM_SetCompare(uint16_t Compare, uint8_t Order)
{
    if(Order == 0)
    {
        TIM_SetCompare1(TIM2, Compare * _Cycle_ms[Order]);
    }
    else if(Order == 1)
    {
        TIM_SetCompare2(TIM2, Compare * _Cycle_ms[Order]);
    }
    else if(Order == 2)
    {
        TIM_SetCompare3(TIM2, Compare * _Cycle_ms[Order]);
    }
    else if(Order == 3)
    {
        TIM_SetCompare4(TIM2, Compare * _Cycle_ms[Order]);
    }
}