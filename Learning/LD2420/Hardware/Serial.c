#include "Serial.h"
#include "stdio.h"
#include "stdarg.h"
#include "OLED.h"

/**
 * @defgroup 与读取状态相关的常量
 */
#define RX_STATUS_WAITING           0
#define RX_STATUS_READING_HEADER    1
#define RX_STATUS_READING_DATA      2
#define RX_STATUS_READING_TAIL      3

// uint8_t Serial_RxData[MAX_RECEIVE_DATA];
// uint8_t Serial_Flag;
// uint8_t Serial_RxLen;
uint8_t Serial_RxData;
uint8_t Serial_Flag;

/**
 * @brief 初始化UART串口
 */
void Serial_Init(void)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStructure);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART1, ENABLE);
}

/**
 * @brief USART发送一个字节的信息
 */
void Serial_SendByte(const uint8_t Byte)
{
    USART_SendData(USART1, Byte);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}


/**
 * @brief USART发送一个数组
 * @param Array 发送的字符
 * @param Length 发送长度
 */
void Serial_SendArray(const uint8_t* const Array, uint16_t Length)
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

/**
 * @brief 串口中断的函数
 */
void USART1_IRQHandler(void)
{
    if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
    {
        Serial_RxData = USART_ReceiveData(USART1);
        Serial_Flag = 1;
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}

// /**
//  * @brief 获取接受信息的标志位, 并进行自清除
//  * @retval 若接收到了信息, 则返回1
//  */
// uint8_t Serial_GetRxFlag(void)
// {
//     if(Serial_Flag == 1)
//     {
//         Serial_Flag = 0;
//         return 1;
//     }
//     return 0;
// }

// /**
//  * @brief 获取Rx接收缓存的值
//  * @param Data 接收缓存的值
//  * @retval 返回数组的长度
//  */
// uint8_t Serial_GetRxData(uint8_t* Data)
// {
//     uint8_t i;
//     for(i = 0; i < Serial_RxLen; i++)
//     {
//         Data[i] = Serial_RxData[i];
//     }
//     return Serial_RxLen;
// }

// /**
//  * @brief 串口中断的函数
//  */
// void USART1_IRQHandler(void)
// {
//     static uint8_t RxStatus;
//     static uint8_t RxIdx;
//     uint8_t Temp;
//     if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
//     {
//         Temp = USART_ReceiveData(USART1);
//         if(Temp == 'O')
//         {
//             Serial_RxLen = RxIdx;
//             RxIdx = 0;
//             Serial_Flag = 1;
//         }
//         Serial_RxData[RxIdx] = USART_ReceiveData(USART1);
//         RxIdx++;
//         if(RxIdx >= MAX_RECEIVE_DATA)
//         {
//             Serial_Flag = 1;
//             RxIdx = 0;
//         }
//         // Serial_Flag = 1;
//         // USART_ClearITPendingBit(USART1, USART_IT_RXNE);
//     }
// }