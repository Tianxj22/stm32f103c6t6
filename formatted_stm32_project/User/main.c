/*
 * @Author: Tianxj22 3456053429@qq.com
 * @Date: 2024-08-13 13:55:59
 * @LastEditors: Tianxj22 3456053429@qq.com
 * @LastEditTime: 2024-09-05 22:48:41
 * @FilePath: \formatted_stm32_project\User\main.c
 * @Description: 
 * 
 * Copyright (c) 2024 by Tianxj22, All Rights Reserved. 
 */
#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "OLED.h"
#include "Timer.h"
#include "PWM.h"
#include "Serial.h"

uint16_t UsedLED[] = {GPIO_Pin_13};
uint16_t UsedKey[] = {GPIO_Pin_0, GPIO_Pin_1};
uint8_t TotalUsedNum = 2;
uint32_t i = 60;
uint8_t KeyNum;

int main()
{
    LED_Init(RCC_APB2Periph_GPIOC, GPIOC, UsedLED, 1);
    PWM_Init(RCC_APB2Periph_GPIOA, GPIOA, 3, 20);
    // OLED_Init(RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_8, GPIO_Pin_9);
    // OLED_Clear();
    // OLED_printf(OLED_FONTSIZE_8X16, "Hello World");
    // OLED_Update();
    while (1)
    {
        LED_Turn(0);
        i = (i + 5) % 125;
        PWM_SetCompare(i, 3);
        // OLED_SetCursor(0, 0);
		// OLED_Clear();
        // OLED_printf(OLED_FONTSIZE_8X16, "compare: %d", i);
        // OLED_Update();
        Delay_ms(200);
    }
}