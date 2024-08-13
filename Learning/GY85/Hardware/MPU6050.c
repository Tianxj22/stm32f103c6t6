#include "MPU6050.h"
#include "MyI2C_2.h"

#define MPU6050_ADDRESS 0XD0

/**
 * @brief MPU6050写入数据
 * @param RegAddress 寄存器地址
 * @param Data 写入的数据
 */
void GY85_WriteReg(uint8_t RegAddress, uint8_t Data)
{
    MyI2C_2_Start();
    MyI2C_2_SendByte(MPU6050_ADDRESS);
    MyI2C_2_ReceiveAck();
    MyI2C_2_SendByte(RegAddress);
    MyI2C_2_ReceiveAck();
    MyI2C_2_SendByte(Data);
    MyI2C_2_ReceiveAck();
    MyI2C_2_Stop();
}

/**
 * @brief MPU6050读取指定地址的数据
 * @param RegAddress 读取的寄存器地址
 * @retval 读取到的数据
 */
uint8_t GY85_ReadReg(uint8_t RegAddress)
{
    uint8_t Data;

    MyI2C_2_Start();
    MyI2C_2_SendByte(MPU6050_ADDRESS);
    MyI2C_2_ReceiveAck();
    MyI2C_2_SendByte(RegAddress);
    MyI2C_2_ReceiveAck();
    MyI2C_2_Stop();

    MyI2C_2_Start();
    MyI2C_2_SendByte(MPU6050_ADDRESS | 0X01);
    MyI2C_2_ReceiveAck();
    Data = MyI2C_2_ReadByte();
    MyI2C_2_SendAck(1);
    MyI2C_2_Stop();

    return Data;
}

/**
 * @brief 陀螺仪初始化
 */
void GY85_Init()
{
    MyI2C_2_Init();
    GY85_WriteReg(GY85_ACC_Power_REG, 0X00);
    GY85_WriteReg(GY85_GYO_Power_REG, 0X05);
}

/**
 * @brief 获取陀螺仪的数据
 * @param Acc 加速度, 顺序为x, y, z
 * @param Gyo 角速度, 顺序为x, y, z
 */
void GY85_GetData(int16_t* Acc, int16_t* Gyo)
{
    uint16_t DataL, DataH;
    uint8_t i;
    
    DataH = GY85_ReadReg(GY85_ACC_X_Reg_DATA_H);
    DataL = GY85_ReadReg(GY85_ACC_X_Reg_DATA_L);
    Acc[0] = (DataH << 8) | DataL;

    DataH = GY85_ReadReg(GY85_ACC_Y_Reg_DATA_H);
    DataL = GY85_ReadReg(GY85_ACC_Y_Reg_DATA_L);
    Acc[1] = (DataH << 8) | DataL;

    DataH = GY85_ReadReg(GY85_ACC_Z_Reg_DATA_H);
    DataL = GY85_ReadReg(GY85_ACC_Z_Reg_DATA_L);
    Acc[2] = (DataH << 8) | DataL;

    DataH = GY85_ReadReg(GY85_GYO_X_Reg_DATA_H);
    DataL = GY85_ReadReg(GY85_GYO_X_Reg_DATA_L);
    Gyo[0] = (DataH << 8) | DataL;

    DataH = GY85_ReadReg(GY85_GYO_Y_Reg_DATA_H);
    DataL = GY85_ReadReg(GY85_GYO_Y_Reg_DATA_L);
    Gyo[1] = (DataH << 8) | DataL;

    DataH = GY85_ReadReg(GY85_GYO_Z_Reg_DATA_H);
    DataL = GY85_ReadReg(GY85_GYO_Z_Reg_DATA_L);
    Gyo[2] = (DataH << 8) | DataL;
}