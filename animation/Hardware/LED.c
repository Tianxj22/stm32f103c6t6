/*
 * @Author: Tianxj22 3456053429@qq.com
 * @Date: 2024-08-13 13:55:58
 * @LastEditors: Tianxj22 3456053429@qq.com
 * @LastEditTime: 2024-08-13 15:16:23
 * @FilePath: \f103c6t6\formatted_stm32_project\Hardware\LED.c
 * @Description: 
 * 
 * Copyright (c) 2024 by Tianxj22, All Rights Reserved. 
 */
#include "LED.h"

uint32_t _LED_RCC_APB2Periph;
GPIO_TypeDef* _LED_GPIO_GROUP;
uint16_t* _Used_LED_GPIO;
uint8_t _TotalUsedLEDNum;

/**
 * @brief: 初始化LED灯
 * @param LED_RCC_APB2Periph LED灯的时钟源, 常见参数如RCC_APB2Periph_GPIOA
 * @param LED_GPIO_GROUP 需要使用的GPIO引脚族, 如GPIOA
 * @param UsedGPIO 使用的GPIO引脚数组, 其中的数值可为GPIO_Pin_0 ~ GPIO_Pin_13
 * @param TotalUsedNum 整个使用的GPIO引脚数
 * @return 无
 */
void LED_Init(uint32_t LED_RCC_APB2Periph, GPIO_TypeDef* LED_GPIO_GROUP, uint16_t* UsedGPIO, uint8_t TotalUsedNum)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    while(TotalUsedNum--)
    {
        GPIO_InitStruct.GPIO_Pin |= UsedGPIO[TotalUsedNum];
    }
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    RCC_APB2PeriphClockCmd(LED_RCC_APB2Periph, ENABLE);

    GPIO_Init(LED_GPIO_GROUP, &GPIO_InitStruct);
    _LED_RCC_APB2Periph = LED_RCC_APB2Periph;
    _LED_GPIO_GROUP = LED_GPIO_GROUP;
    _Used_LED_GPIO = UsedGPIO;
    _TotalUsedLEDNum = TotalUsedNum;
}

/**
 * @brief: 点亮某个LED引脚(此处认为是低电平点亮)
 * @param LED_Order 要点亮的LED序号, 该序号是相对于原先给定的使用引脚的数组顺序
 * @return 若参数正确则返回1, 否则返回0
 *                   参数错误可能的原因为数组越界
 */
uint8_t LED_On(uint8_t LED_Order)
{
    if(LED_Order >= _TotalUsedLEDNum)
    {
        return 0;
    }
    GPIO_ResetBits(_LED_GPIO_GROUP, _Used_LED_GPIO[LED_Order]);
    return 1;
}

/**
 * @brief: 关闭指定顺序的LED(此处认为低电平点亮)
 * @param LED_Order 要点亮的LED序号, 该序号是相对于原先给定的使用引脚的数组顺序
 * @return 若参数正确则返回1, 否则返回0
 *                   参数错误可能的原因为数组越界
 */
uint8_t LED_Off(uint8_t LED_Order)
{
    if(LED_Order >= _TotalUsedLEDNum)
    {
        return 0;
    }
    GPIO_SetBits(_LED_GPIO_GROUP, _Used_LED_GPIO[LED_Order]);
    return 1;
}

/**
 * @brief: 翻转指定顺序的LED亮灭状态(此处认为低电平点亮)
 * @param LED_Order 要点亮的LED序号, 该序号是相对于原先给定的使用引脚的数组顺序
 * @return 若参数正确则返回1, 否则返回0
 *                   参数错误可能的原因为数组越界
 */
uint8_t LED_Turn(uint8_t LED_Order)
{
    if(LED_Order >= _TotalUsedLEDNum)
    {
        return 0;
    }
    if(GPIO_ReadOutputDataBit(_LED_GPIO_GROUP, _Used_LED_GPIO[LED_Order]))
    {
        LED_On(LED_Order);
    }
    else
    {
        LED_Off(LED_Order);
    }
    return 1;
}