#include "Serial.h"
#include "stdio.h"
#include "stdarg.h"

/**
 * @brief 初始化UART串口
 */
void Serial_Init(void)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStructure);

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