/*
 * @Author: Tianxj22 3456053429@qq.com
 * @Date: 2024-08-13 20:45:21
 * @LastEditors: Tianxj22 3456053429@qq.com
 * @LastEditTime: 2024-08-13 21:16:29
 * @FilePath: \formatted_stm32_project\Hardware\Serial.c
 * @Description: 
 * 
 * Copyright (c) 2024 by Tianxj22, All Rights Reserved. 
 */
#include "Serial.h"
#include "stdio.h"
#include "stdarg.h"

uint8_t Serial_RxData;
uint8_t Serial_Flag;

/**
 * @brief: 初始化通信串口
 *      @enum UART1
 * @param Serial_RCC_APB2Periph 使用的串口对应时钟源, 常见如RCC_APB2Periph_GPIOA
 * @param Serial_GPIO_GROUP 使用的串口族, 如GPIOA
 * @param Tx_Port 串口通信的TX口
 * @param Rx_Port 串口通信的RX口
 * @param Serial_IRQn 串口的UART序号, 可用参数有USART1_IRQn(Tx-A9/B6, Rx-A10/B7), USART2_IRQn(Tx-A2, Rx-A3), USART3_IRQn(Tx-B10, Rx-B11)
 * @param BaudRate 波特率
 * @return 
 */
void Serial_Init(uint32_t Serial_RCC_APB2Periph, GPIO_TypeDef* Serial_GPIO_GROUP, uint16_t Tx_Port, uint16_t Rx_Port, uint8_t Serial_IRQn, uint32_t BaudRate)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(Serial_RCC_APB2Periph, ENABLE);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = Tx_Port;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(Serial_GPIO_GROUP, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = Rx_Port;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(Serial_GPIO_GROUP, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStructure);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = Serial_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART1, ENABLE);
}

/**
 * @brief USART发送一个字节的信息
 */
void Serial_SendByte(uint8_t Byte)
{
    USART_SendData(USART1, Byte);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}


/**
 * @brief USART发送一个数组
 * @param Array 发送的字符
 * @param Length 发送长度
 */
void Serial_SendArray(uint8_t* Array, uint16_t Length)
{
    uint16_t i;
    for(i = 0; i < Length; i++)
    {
        Serial_SendByte(Array[i]);
    }
}

/**
 * @brief USART发送一个字符串
 * @param String 发送的字符串
 */
void Serial_SendString(char* String)
{
    uint8_t i;
    for(i = 0; String[i] != '\0'; i++)
    {
        Serial_SendByte(String[i]);
    }
}

/**
 * @brief USART发送一个数字
 * @param Num 发送的数字
 */
void Serial_SendNum(uint32_t Num)
{
    char Ch[20];
    uint8_t i;
    if(!Num){
        Serial_SendByte('0');
        return;
    }
    while(Num)
    {
        Ch[i] = Num % 10;
        Num /= 10;
        i++;
    }
    while(i--)
    {
        Serial_SendByte(Ch[i]);
    }
}

/**
 * @brief 串口的格式化输出函数
 * @param format 格式化输出的字符串
 */
void u1_printf(char* format, ...)
{
    char String[100];
    va_list arg;
    va_start(arg, format);
    vsprintf(String, format, arg);
    va_end(arg);
    Serial_SendString(String);
}

/**
 * @brief 获取接受信息的标志位, 并进行自清除
 * @retval 若接收到了信息, 则返回1
 */
uint8_t Serial_GetRxFlag(void)
{
    if(Serial_Flag == 1)
    {
        Serial_Flag = 0;
        return 1;
    }
    return 0;
}

/**
 * @brief 获取Rx接收缓存的值
 * @retval 接收缓存的值
 */
uint8_t Serial_GetRxData(void)
{
    return Serial_RxData;
}
