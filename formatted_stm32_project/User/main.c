/*
 * @Author: Tianxj22 3456053429@qq.com
 * @Date: 2024-08-13 13:55:59
 * @LastEditors: Tianxj22 3456053429@qq.com
 * @LastEditTime: 2024-08-13 21:25:50
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
uint16_t UsedKey[] = {GPIO_Pin_0};
uint8_t TotalUsedNum = 1;
uint32_t i = 890;
uint32_t Direct = 1;

int main()
{
    OLED_Init(RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_7, GPIO_Pin_6);
    // PWM_Init(RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_0, 20);
    // PWM_SetCompare1(600);
    Serial_Init(RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_9, GPIO_Pin_10, USART1_IRQn, 115200);

    while(1)
    {
        if(Serial_GetRxFlag())
        {
            i = Serial_GetRxData();
            OLED_SetCursor(8, 2);
            OLED_printf(OLED_FONTSIZE_8X16, "I heard %2x", i);
            OLED_Update();
            u1_printf("I heard %2x", i);
        }
    }
}