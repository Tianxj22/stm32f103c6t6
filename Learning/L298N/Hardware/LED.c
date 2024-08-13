#include "LED.h"

uint16_t* _Used_LED_GPIO;
uint8_t _TotalUsedKeyNum;

/**
 * @brief 初始化GPIOA端口为使用的LED口
 * @param UsedGPIO 需要使用的GPIO列表
 * @param TotalUsedNum 总共需要使用的GPIO口数量
 */
void LED_Init(uint16_t* UsedGPIO, uint8_t TotalUsedNum)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    while(TotalUsedNum--)
    {
        GPIO_InitStruct.GPIO_Pin |= UsedGPIO[TotalUsedNum];
    }
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    RCC_APB2PeriphClockCmd(LED_RCC_APB2Periph, ENABLE);

    GPIO_Init(LED_GPIO_GROUP, &GPIO_InitStruct);
    _Used_LED_GPIO = UsedGPIO;
    _TotalUsedKeyNum = TotalUsedNum;
}

/**
 * @brief 打开指定顺序的LED, 如果正确打开返回1, 否则返回0
 * @param LED_Order LED灯的顺序
 * @retval 是否成功打开LED, 如果是的话返回1, 否则返回0
 */
uint8_t LED_On(uint8_t LED_Order)
{
    if(LED_Order >= _TotalUsedKeyNum)
    {
        return 0;
    }
    GPIO_ResetBits(LED_GPIO_GROUP, _Used_LED_GPIO[LED_Order]);
    return 1;
}

/**
 * @brief 关闭指定顺序的LED, 如果正确关闭返回1, 否则返回0
 * @param LED_Order LED灯的顺序
 * @retval 是否成功关闭LED, 如果是的话返回1, 否则返回0
 */
uint8_t LED_Off(uint8_t LED_Order)
{
    if(LED_Order >= _TotalUsedKeyNum)
    {
        return 0;
    }
    GPIO_SetBits(LED_GPIO_GROUP, _Used_LED_GPIO[LED_Order]);
    return 1;
}

/**
 * @brief 翻转指定顺序的LED状态, 如果正确翻转返回1, 否则返回0
 * @param LED_Order LED灯的顺序
 * @retval 是否成功翻转LED, 如果是的话返回1, 否则返回0
 */
uint8_t LED_Turn(uint8_t LED_Order)
{
    if(LED_Order >= _TotalUsedKeyNum)
    {
        return 0;
    }
    if(GPIO_ReadOutputDataBit(LED_GPIO_GROUP, _Used_LED_GPIO[LED_Order]))
    {
        LED_On(LED_Order);
    }
    else
    {
        LED_Off(LED_Order);
    }
    return 1;
}