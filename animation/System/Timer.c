/*
 * @Author: Tianxj22 3456053429@qq.com
 * @Date: 2024-08-13 18:08:30
 * @LastEditors: Tianxj22 3456053429@qq.com
 * @LastEditTime: 2024-08-13 18:13:37
 * @FilePath: \formatted_stm32_project\System\Timer.c
 * @Description: 
 * 
 * Copyright (c) 2024 by Tianxj22, All Rights Reserved. 
 */
#include "Timer.h"

/**
 * @brief: 计时器初始化
 * @param ms 每多少毫秒触发中断
 * @return 
 */
void Timer_Init(uint16_t ms)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_InternalClockConfig(TIM2);

    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 10 * ms - 1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM2, ENABLE);
}

/**
 * @brief TIM2中断函数
 */
// void TIM2_IRQHandler(void)
// {
//     if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
//     {
//         Num++;
//         TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//     }
// }