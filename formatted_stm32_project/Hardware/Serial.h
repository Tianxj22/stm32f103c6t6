#ifndef __SERIAL__
#define __SERIAL__

#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"

void Serial_Init(uint32_t Serial_RCC_APB2Periph, GPIO_TypeDef* Serial_GPIO_GROUP, uint16_t Tx_Port, uint16_t Rx_Port, uint8_t Serial_IRQn, uint32_t BaudRate);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t* Array, uint16_t Length);
void Serial_SendString(char* String);
void Serial_SendNum(uint32_t Num);
void u1_printf(char* format, ...);
uint8_t Serial_GetRxFlag(void);
uint8_t Serial_GetRxData(void);

#endif