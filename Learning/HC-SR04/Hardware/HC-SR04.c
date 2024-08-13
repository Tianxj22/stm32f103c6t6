#include "HC-SR04.h"
#include "Delay.h"


/**
 * @brief 初始化超声模块
 */
void HCSR04_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    Timer_Init();
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = HCSR04_TRIG_PIN;
    GPIO_Init(HCSR04_GPIO_GROUP, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = HCSR04_ECHO_PIN;
    GPIO_Init(HCSR04_GPIO_GROUP, &GPIO_InitStructure);

}


float HCSR04_GetDistance(void)
{
    uint32_t t = 0;  
	uint8_t i = 0;  
	float Sum = 0;
    for(i = 0; i < 5; i++)
    {
        GPIO_SetBits(HCSR04_GPIO_GROUP, HCSR04_TRIG_PIN);
        Delay_us(20);
        GPIO_ResetBits(HCSR04_GPIO_GROUP, HCSR04_TRIG_PIN);
        while(GPIO_ReadInputDataBit(HCSR04_GPIO_GROUP, HCSR04_ECHO_PIN) == RESET);
        Timer_ResetTime();
        while(GPIO_ReadInputDataBit(HCSR04_GPIO_GROUP, HCSR04_ECHO_PIN) == SET);
        t = Timer_GetTime_us();
        Sum += (float)(t) / 58.0;            // 以cm为单位
    }
	return Sum / 5.0; 
}