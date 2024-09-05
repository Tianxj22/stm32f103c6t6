#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "Key.h"
#include "PWM.h"

int16_t Speed = 0;
uint8_t KeyNum;
uint16_t Cmp = 1250;

uint16_t UsedLED[1] = {GPIO_Pin_13};

int main()
{
    LED_Init(UsedLED, 1);
    PWM_Init();
	
    while (1)
    {	
		Cmp = (Cmp + 100) % 2500;
		LED_Turn(0);
		PWM_SetCompare3(Cmp);
		Delay_ms(200);
    }
    return 0;
}