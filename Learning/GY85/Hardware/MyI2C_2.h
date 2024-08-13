#ifndef __MY_I2C_2__
#define __MY_I2C_2__

#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"

#define I2C_RCC_APB2PERIPH RCC_APB2Periph_GPIOB
#define I2C_GPIO_GROUP GPIOB
#define I2C_SCL GPIO_Pin_10
#define I2C_SDA GPIO_Pin_11


void MyI2C_2_Init(void);
void MyI2C_2_Start(void);
void MyI2C_2_Stop(void);
void MyI2C_2_SendByte(uint8_t Byte);
uint8_t MyI2C_2_ReadByte(void);
void MyI2C_2_SendAck(uint8_t AckBit);
uint8_t MyI2C_2_ReceiveAck(void);

#endif