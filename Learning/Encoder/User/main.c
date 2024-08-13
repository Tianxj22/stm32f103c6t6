#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"
#include "Delay.h"
#include "LED.h"
#include "CountCollision.h"
#include "Encoder.h"

uint16_t UsedLED[] = {GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_2, GPIO_Pin_3, GPIO_Pin_4, GPIO_Pin_5, GPIO_Pin_6, GPIO_Pin_7};
uint8_t TotalUsedNum = 8;
uint8_t i = 0;

void LEDShowNum(uint8_t Num)
{
    for(i = 0; i < 8; i++)
    {
        if(Num & (0X01 << i))
        {
            LED_On(i);
        }
        else
        {
            LED_Off(i);
        }
    }
}

int main()
{
    LED_Init(UsedLED, TotalUsedNum);
    Encoder_Init();
	for(i = 0; i < TotalUsedNum; i++)
    {
        LED_Off(i);
    }
    while (1)
    {
		LEDShowNum(Encoder_Get());
    }
    return 0;
}