#include "MyI2C_2.h"

/**
 * @brief SCL线写入数据
 * @param BitVal 要写上的数据
 */
void MyI2C_2_W_SCL(uint8_t BitVal)
{
    GPIO_WriteBit(I2C_GPIO_GROUP, I2C_SCL, (BitAction)BitVal);
}

/**
 * @brief SDA线写入数据
 * @param BitVal 要写上的数据
 */
void MyI2C_2_W_SDA(uint8_t BitVal)
{
    GPIO_WriteBit(I2C_GPIO_GROUP, I2C_SDA, (BitAction)BitVal);
}

/**
 * @brief SDA线读取数据
 * @retval SDA线上面的数据
 */
uint8_t MyI2C_2_R_SDA(void)
{
    uint8_t BitVal;
    BitVal = GPIO_ReadInputDataBit(I2C_GPIO_GROUP, I2C_SDA);
    return BitVal;
}

/**
 * @brief 自定义的I2C总线初始化
 */
void MyI2C_2_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(I2C_RCC_APB2PERIPH, ENABLE);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Pin = I2C_SCL | I2C_SDA;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(I2C_GPIO_GROUP, &GPIO_InitStructure);

    MyI2C_2_W_SCL(1);
    MyI2C_2_W_SDA(1);
}

/**
 * @brief I2C总线开始输出
 */
void MyI2C_2_Start(void)
{
    MyI2C_2_W_SCL(1);
    MyI2C_2_W_SDA(1);
    MyI2C_2_W_SCL(0);
    MyI2C_2_W_SDA(0);
}

/**
 * @brief 总线关闭
 */
void MyI2C_2_Stop(void)
{
    MyI2C_2_W_SCL(1);
    MyI2C_2_W_SDA(0);
    MyI2C_2_W_SDA(1);
}

/**
 * @brief I2C总线发送一个字节
 * @param Byte 要发送的字节信息
 */
void MyI2C_2_SendByte(uint8_t Byte)
{
    uint8_t i;
    for(i = 0; i < 8; i++)
    {
        MyI2C_2_W_SDA(Byte & (0X80 >> i));
        MyI2C_2_W_SCL(1);
        MyI2C_2_W_SCL(0);
    }
}

/**
 * @brief I2C总线读取一个字节
 * @retval 读取到的字节信息
 */
uint8_t MyI2C_2_ReadByte(void)
{
    uint8_t i;
    uint8_t Byte = 0X00;
    MyI2C_2_W_SDA(1);
    for(i = 0; i < 8; i++)
    {
        MyI2C_2_W_SCL(1);
        if(MyI2C_2_R_SDA()){Byte |= (0X80 >> i);}
        MyI2C_2_W_SCL(0);
    }
    return Byte;
}

/**
 * @brief I2C发送响应
 * @param AckBit 发送的相应数
 */
void MyI2C_2_SendAck(uint8_t AckBit)
{
    MyI2C_2_W_SDA(AckBit);
    MyI2C_2_W_SCL(1);
    MyI2C_2_W_SCL(0);
}

/**
 * @brief I2C总线接收信息
 * @retval 接收到的信息
 */
uint8_t MyI2C_2_ReceiveAck(void)
{
    uint8_t AckBit;
    MyI2C_2_W_SDA(1);
    MyI2C_2_W_SCL(1);
    AckBit = MyI2C_2_R_SDA();
    MyI2C_2_W_SCL(0);
    return AckBit;
}