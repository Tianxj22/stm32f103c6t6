#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "PWM.h"
uint16_t i = 0;


int main()
{
    OLED_Init();
    PWM_Init();

    OLED_Clear();
    OLED_Update();

    while (1)
    {
        
    }
    return 0;
}