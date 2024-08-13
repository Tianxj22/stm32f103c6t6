#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "L298N.h"

uint8_t i = 0;

int main()
{
    OLED_Init();
    OLED_Clear();
    OLED_printf(OLED_FONTSIZE_8X16, "test L298N");
    OLED_Update();
    L298N_Init();
    L298N_SetLeftMotor(100, Forward);
    // i = 0;
    while (1)
    {
		
    }
    return 0;
}