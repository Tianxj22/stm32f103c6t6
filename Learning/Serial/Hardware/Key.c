#include "Key.h"

/**
 * @brief 初始化按键(这里使用GPIOB的1号和11号端口)
 */
void Key_Init(void)
{
    GPIO_InitTypeDef GPIOB_InitStructure;
    GPIOB_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIOB_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11;
    GPIOB_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;


    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_Init(GPIOB, &GPIOB_InitStructure);
}

/**
 * @brief 读取按键值
 * @retval 按键的键值, 如果按下1则返回1, 按下11则返回2, 否则返回0
 */
uint8_t GetKey(void)
{
    uint8_t KeyNum = 0;
    
    if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
    {
        Delay_ms(20);
        while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0);
        Delay_ms(20);
        KeyNum = 1;
    }
    if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0)
    {
        Delay_ms(20);
        while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0);
        Delay_ms(20);
        KeyNum = 2;
    }
    return KeyNum;
}