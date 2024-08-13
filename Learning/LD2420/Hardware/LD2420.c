#include "LD2420.h"
#include "OLED.h"

const uint8_t StartArray[] = {0XFD, 0XFC, 0XFB, 0XFA, 
            0X08, 0X00,
            0X12, 0X00,
            0X00, 0X00, 0X64, 0X00, 0X00, 0X00,
            0X04, 0X03, 0X02, 0X01
            };

const uint8_t ReadVersionNum[] = {
    0XFD, 0XFC, 0XFB, 0XFA,
    0X02, 0X00, 0X00, 0X00, 
    0X04, 0X03, 0X02, 0X01
};

/**
 * @brief LD2420的初始化
 */
void LD2420_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    Serial_Init();
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
 * @brief 读取LD2420版本号
 */
void LD2420_GetVersionNum(void)
{
    uint8_t i;
    Serial_SendArray(ReadVersionNum, 14);
    OLED_SetCursor(0, 0);
    for(i = 0; i < 22; i++)
    {
        while(!Serial_GetRxFlag());
        OLED_printf(OLED_FONTSIZE_8X16, "%c", Serial_GetRxData());
        // OLED_Update();
    }
    OLED_printf(OLED_FONTSIZE_8X16, "finished");
    OLED_Update();
}

/**
 * @brief 读取是否有人
 * @retval 若为1则表示有人, 否则表示没人
 */
uint8_t LD2420_GetOT2Data(void)
{
    return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11);
}

/**
 * @brief 判断LD2420是否有数据
 * @retval 若有信息则返回1, 否则返回0
 */
uint8_t LD2420_GetDataFlag(void)
{
    return Serial_GetRxFlag();
}

/**
 * @brief 获取缓存区中的数据
 * @param Data 接收串口数据的数组
 */
uint32_t LD2420_GetData(void)
{
    uint32_t Rt;
    uint8_t Temp;
    do{
        while(!Serial_GetRxFlag());
        Temp = Serial_GetRxData();
    }while(Temp < '0' || Temp > '9');
    Rt = Temp - '0';
    while(1){
        while(!Serial_GetRxFlag());
        Temp = Serial_GetRxData();
        if(Temp < '0' || Temp > '9'){
            break;
        }
        Rt = Rt * 10 + Temp - '0';
    }
    return Rt;
}

