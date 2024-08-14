/*
 * @Author: Tianxj22 3456053429@qq.com
 * @Date: 2024-08-13 15:33:18
 * @LastEditors: Tianxj22 3456053429@qq.com
 * @LastEditTime: 2024-08-13 15:46:42
 * @FilePath: \formatted_stm32_project\Hardware\MyI2C.h
 * @Description: 
 * 
 * Copyright (c) 2024 by Tianxj22, All Rights Reserved. 
 */
#ifndef __MY_I2C__
#define __MY_I2C__

#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"

void MyI2C_Init(uint32_t I2C_RCC_APB2PERIPH, GPIO_TypeDef* I2C_GPIO_GROUP, uint16_t I2C_SCL, uint16_t I2C_SDA);
void MyI2C_Start(void);
void MyI2C_Stop(void);
void MyI2C_SendByte(uint8_t Byte);
uint8_t MyI2C_ReadByte(void);
void MyI2C_SendAck(uint8_t AckBit);
uint8_t MyI2C_ReceiveAck(void);

#endif