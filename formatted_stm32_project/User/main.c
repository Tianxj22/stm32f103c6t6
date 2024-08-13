#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"
#include "Delay.h"
#include "LED.h"
#include "Key.h"

uint16_t UsedLED[] = {GPIO_Pin_13};
uint16_t UsedKey[] = {GPIO_Pin_0};
uint8_t TotalUsedNum = 1;
uint8_t i = 0;

int main()
{
    LED_Init(RCC_APB2Periph_GPIOC, GPIOC, UsedLED, TotalUsedNum);
    Key_Init(RCC_APB2Periph_GPIOA, GPIOA, UsedKey, TotalUsedNum);
    //LED_On(0);

    while(1)
    {
        if(GetKey()){
            LED_Turn(0);
        }
    }
}