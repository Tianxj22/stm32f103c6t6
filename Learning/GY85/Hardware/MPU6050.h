#ifndef __MPU6050__
#define __MPU6050__

#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"


/**
 * @defgroup MP6050寄存器的地址
 */
#define GY85_ACC_Power_REG 0x2D
#define GY85_ACC_X_Reg_DATA_L 0x32
#define GY85_ACC_X_Reg_DATA_H 0x33
#define GY85_ACC_Y_Reg_DATA_L 0x34
#define GY85_ACC_Y_Reg_DATA_H 0x35
#define GY85_ACC_Z_Reg_DATA_L 0x36
#define GY85_ACC_Z_Reg_DATA_H 0x37
#define GY85_GYO_Power_REG 0X3E
#define GY85_GYO_X_Reg_DATA_H 0x1D
#define GY85_GYO_X_Reg_DATA_L 0x1E
#define GY85_GYO_Y_Reg_DATA_H 0x1F
#define GY85_GYO_Y_Reg_DATA_L 0x20
#define GY85_GYO_Z_Reg_DATA_H 0x21
#define GY85_GYO_Z_Reg_DATA_L 0x22

void GY85_WriteReg(uint8_t RegAddress, uint8_t Data);
uint8_t GY85_ReadReg(uint8_t RegAddress);
void GY85_Init();
void GY85_GetData(int16_t* Acc, int16_t* Gyo);

#endif