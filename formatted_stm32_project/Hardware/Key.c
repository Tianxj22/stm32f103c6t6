/*
 * @Author: Tianxj22 3456053429@qq.com
 * @Date: 2024-08-13 13:55:58
 * @LastEditors: Tianxj22 3456053429@qq.com
 * @LastEditTime: 2024-08-13 15:14:35
 * @FilePath: \f103c6t6\formatted_stm32_project\Hardware\Key.c
 * @Description: 
 * 
 * Copyright (c) 2024 by Tianxj22, All Rights Reserved. 
 */
#include "Key.h"

uint32_t _Key_RCC_APB2Periph;
GPIO_TypeDef* _Key_GPIO_GROUP;
uint16_t* _Used_Key_GPIO;
uint8_t _TotalUsedKeyNum;

/**
 * @brief: 初始化按键模块
 * @param Key_RCC_APB2Periph 按键模块的时钟源设置, 如RCC_APB2Periph_GPIOA
 * @param Key_GPIO_GROUP 按键输入模块的GPIO族, 如GPIOA
 * @param UsedGPIO 使用的GPIO数组, 其中的数据可用如GPIO_Pin_0
 * @param TotalUsedNum 所有的GPIO个数
 * @return 无
 */
void Key_Init(uint32_t Key_RCC_APB2Periph, GPIO_TypeDef* Key_GPIO_GROUP, uint16_t* UsedGPIO, uint8_t TotalUsedNum)
{
    uint8_t i;
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = 0;
    for(i = 0; i < TotalUsedNum; i++)
    {
        GPIO_InitStructure.GPIO_Pin |= UsedGPIO[i];
    }
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;


    RCC_APB2PeriphClockCmd(Key_RCC_APB2Periph, ENABLE);
    GPIO_Init(Key_GPIO_GROUP, &GPIO_InitStructure);

    _Key_RCC_APB2Periph = Key_RCC_APB2Periph;
    _Key_GPIO_GROUP = Key_GPIO_GROUP;
    _Used_Key_GPIO = UsedGPIO;
    _TotalUsedKeyNum = TotalUsedNum;
}


/**
 * @brief: 读取键值
 * @return 若有按键被按下, 则会在按键放开时返回按键的顺序值. 注意此处的顺序从1开始计算. 
 *         若没有按键被按下, 则会返回0
 */
uint8_t GetKey(void)
{
    uint8_t KeyNum = 0;
    uint8_t i;
    
    for(i = 0; i < _TotalUsedKeyNum; i++)
    {
        if(GPIO_ReadInputDataBit(_Key_GPIO_GROUP, _Used_Key_GPIO[i]) == 0)
        {
            Delay_ms(20);
            while(GPIO_ReadInputDataBit(_Key_GPIO_GROUP, _Used_Key_GPIO[i]) == 0);
            Delay_ms(20);
            KeyNum = i + 1;
        }
    }
    return KeyNum;

}