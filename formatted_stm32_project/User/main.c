#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"
#include "Delay.h"
#include "LED.h"

uint16_t UsedLED[] = {GPIO_Pin_0, GPIO_Pin_1};
uint8_t TotalUsedNum = 1;
uint8_t i = 0;

int main()
{
    LED_Init(UsedLED, TotalUsedNum);
	
    while (1)
    {
		LED_Turn(0);
        
    }
    return 0;
}