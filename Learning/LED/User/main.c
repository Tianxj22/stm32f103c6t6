#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"
#include "Delay.h"
#include "LED.h"

// uint16_t UsedLED[] = {GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_2, GPIO_Pin_3, GPIO_Pin_4, GPIO_Pin_5, GPIO_Pin_6, GPIO_Pin_7};
uint16_t UsedLED[] = {GPIO_Pin_0, GPIO_Pin_1};
uint8_t TotalUsedNum = 1;
uint8_t i = 0;

int main()
{
    LED_Init(UsedLED, TotalUsedNum);
	//for(i = 0; i < TotalUsedNum; i++)
    //{
    //    LED_On(i);
    //}
    //i = 0;
	LED_On(0);
	LED_Off(1);
    while (1)
    {
		//LED_Off(i);
        //i = (i + 1) % TotalUsedNum;
        //LED_On(i);
        //Delay_ms(100);
    }
    return 0;
}