#ifndef __SERIAL__
#define __SERIAL__

#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"

#define USART1_RX GPIO_Pin_9
#define MAX_RECEIVE_DATA            20

void Serial_Init(void);
void Serial_SendByte(const uint8_t Byte);
void Serial_SendArray(const uint8_t* Array, uint16_t Length);
void Serial_SendString(char* String);
void Serial_SendNum(uint32_t Num);
void u1_printf(char* format, ...);
// uint8_t Serial_GetRxFlag(void);
// uint8_t Serial_GetRxData(uint8_t* Data);
uint8_t Serial_GetRxFlag(void);
uint8_t Serial_GetRxData(void);

#endif