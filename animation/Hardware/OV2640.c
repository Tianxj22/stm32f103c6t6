/*
 * @Author: Tianxj22 3456053429@qq.com
 * @Date: 2024-08-14 13:08:51
 * @LastEditors: Tianxj22 3456053429@qq.com
 * @LastEditTime: 2024-08-14 13:11:07
 * @FilePath: \formatted_stm32_project\Hardware\OV2640.c
 * @Description: 
 * 
 * Copyright (c) 2024 by Tianxj22, All Rights Reserved. 
 */
#include "OV2640.h"


void OV2640_Init(uint32_t OV2640_RCC_APB2PERIPH, GPIO_TypeDef* OV2640_GPIO_GROUP, uint16_t OV2640_SCL, uint16_t OV2640_SDA)
{
    MyI2C_Init(OV2640_RCC_APB2PERIPH, OV2640_GPIO_GROUP, OV2640_SCL, OV2640_SDA);
    
}