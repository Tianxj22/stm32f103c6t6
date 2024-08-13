#ifndef __MY_I2C__
#define __MY_I2C__

#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"

#define I2C_RCC_APB2PERIPH RCC_APB2Periph_GPIOB
#define I2C_GPIO_GROUP GPIOB
#define I2C_SCL GPIO_Pin_9
#define I2C_SDA GPIO_Pin_8


void MyI2C_Init(void);
void MyI2C_Start(void);
void MyI2C_Stop(void);
void MyI2C_SendByte(uint8_t Byte);
uint8_t MyI2C_ReadByte(void);
void MyI2C_SendAck(uint8_t AckBit);
uint8_t MyI2C_ReceiveAck(void);

#endif