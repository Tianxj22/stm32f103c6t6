/*
 * @Author: Tianxj22 3456053429@qq.com
 * @Date: 2024-08-13 15:33:18
 * @LastEditors: Tianxj22 3456053429@qq.com
 * @LastEditTime: 2024-08-13 15:45:00
 * @FilePath: \formatted_stm32_project\Hardware\MyI2C.c
 * @Description: 
 * 
 * Copyright (c) 2024 by Tianxj22, All Rights Reserved. 
 */
#include "MyI2C.h"

uint32_t _I2C_RCC_APB2PERIPH;
GPIO_TypeDef* _I2C_GPIO_GROUP;
uint16_t _I2C_SCL;
uint16_t _I2C_SDA;

/**
 * @brief SCL线写入数据
 * @param BitVal 要写上的数据
 */
void MyI2C_W_SCL(uint8_t BitVal)
{
    GPIO_WriteBit(_I2C_GPIO_GROUP, _I2C_SCL, (BitAction)BitVal);
}

/**
 * @brief SDA线写入数据
 * @param BitVal 要写上的数据
 */
void MyI2C_W_SDA(uint8_t BitVal)
{
    GPIO_WriteBit(_I2C_GPIO_GROUP, _I2C_SDA, (BitAction)BitVal);
}

/**
 * @brief SDA线读取数据
 * @retval SDA线上面的数据
 */
uint8_t MyI2C_R_SDA(void)
{
    uint8_t BitVal;
    BitVal = GPIO_ReadInputDataBit(_I2C_GPIO_GROUP, _I2C_SDA);
    return BitVal;
}

/**
 * @brief: 自定义的I2C总线初始化
 * @param I2C_RCC_APB2PERIPH 时钟源相关参数, 常见如RCC_APB2Periph_GPIOA
 * @param I2C_GPIO_GROUP 使用的引脚族, 如GPIOA
 * @param I2C_SCL SCL引脚口, 如GPIO_Pin_9
 * @param I2C_SDA SDA引脚口, 如GPIO_Pin_10
 * @return 
 */
void MyI2C_Init(uint32_t I2C_RCC_APB2PERIPH, GPIO_TypeDef* I2C_GPIO_GROUP, uint16_t I2C_SCL, uint16_t I2C_SDA)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    _I2C_RCC_APB2PERIPH = I2C_RCC_APB2PERIPH;
    _I2C_GPIO_GROUP = I2C_GPIO_GROUP;
    _I2C_SCL = I2C_SCL;
    _I2C_SDA = I2C_SDA;

    RCC_APB2PeriphClockCmd(_I2C_RCC_APB2PERIPH, ENABLE);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Pin = _I2C_SCL | _I2C_SDA;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(_I2C_GPIO_GROUP, &GPIO_InitStructure);

    MyI2C_W_SCL(1);
    MyI2C_W_SDA(1);
}

/**
 * @brief I2C总线开始输出
 */
void MyI2C_Start(void)
{
    MyI2C_W_SCL(1);
    MyI2C_W_SDA(1);
    MyI2C_W_SCL(0);
    MyI2C_W_SDA(0);
}

/**
 * @brief 总线关闭
 */
void MyI2C_Stop(void)
{
    MyI2C_W_SCL(1);
    MyI2C_W_SDA(0);
    MyI2C_W_SDA(1);
}

/**
 * @brief I2C总线发送一个字节
 * @param Byte 要发送的字节信息
 */
void MyI2C_SendByte(uint8_t Byte)
{
    uint8_t i;
    for(i = 0; i < 8; i++)
    {
        MyI2C_W_SDA(Byte & (0X80 >> i));
        MyI2C_W_SCL(1);
        MyI2C_W_SCL(0);
    }
}

/**
 * @brief I2C总线读取一个字节
 * @retval 读取到的字节信息
 */
uint8_t MyI2C_ReadByte(void)
{
    uint8_t i;
    uint8_t Byte = 0X00;
    MyI2C_W_SDA(1);
    for(i = 0; i < 8; i++)
    {
        MyI2C_W_SCL(1);
        if(MyI2C_R_SDA()){Byte |= (0X80 >> i);}
        MyI2C_W_SCL(0);
    }
    return Byte;
}

/**
 * @brief I2C发送响应
 * @param AckBit 发送的相应数
 */
void MyI2C_SendAck(uint8_t AckBit)
{
    MyI2C_W_SDA(AckBit);
    MyI2C_W_SCL(1);
    MyI2C_W_SCL(0);
}

/**
 * @brief I2C总线接收信息
 * @retval 接收到的信息
 */
uint8_t MyI2C_ReceiveAck(void)
{
    uint8_t AckBit;
    MyI2C_W_SDA(1);
    MyI2C_W_SCL(1);
    AckBit = MyI2C_R_SDA();
    MyI2C_W_SCL(0);
    return AckBit;
}