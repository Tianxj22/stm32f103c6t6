/*
 * @Author: Tianxj22 3456053429@qq.com
 * @Date: 2024-08-13 13:55:59
 * @LastEditors: Tianxj22 3456053429@qq.com
 * @LastEditTime: 2024-08-13 15:00:12
 * @FilePath: \f103c6t6\formatted_stm32_project\System\Delay.c
 * @Description: 
 * 
 * Copyright (c) 2024 by Tianxj22, All Rights Reserved. 
 */
#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"
#include "Delay.h"

/**
 * @brief 实现微秒级的延时
 * @param us 延时的微秒数
 * @retval 无
 */
void Delay_us(uint32_t us)
{
    SysTick->LOAD = 72 * us;    // 设置定时器重装值
    SysTick->VAL = 0X00;
    SysTick->CTRL = 0X00000005; // 启动定时器
    while(!(SysTick->CTRL & 0X00010000));
    SysTick->CTRL = 0X00000004;
}

/**
 * @brief 实现毫秒级的延时
 * @param ms 延时的毫秒数
 * @retval 无
 */
void Delay_ms(uint32_t ms)
{
    while(ms--)
    {
        Delay_us(1000);
    }
}

/**
 * @brief 实现秒级的延时
 * @param s 延时的秒数
 * @retval 无
 */
void Delay_s(uint32_t s)
{
    while(s--)
    {
        Delay_ms(1000);
    }
}