#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Chicken.h"
uint8_t i = 0;

int main()
{
    OLED_Init();
    
    // OLED_ShowString(0, 0, "Hello World", OLED_FONTSIZE_6X8);

    // OLED_ShowString(0, 3, "Hello World!", OLED_FONTSIZE_8X16);
    
    // OLED_ShowImage(0, 0, 32, 32, Img);
    OLED_Clear();
    // OLED_ShowChar(' ', OLED_FONTSIZE_8X16);
    // OLED_ShowNum(114, OLED_FONTSIZE_8X16);
    // OLED_ShowHexNum(0XFF, OLED_FONTSIZE_8X16);
    OLED_Update();

    // i = 0;
    while (1)
    {
		OLED_ShowImage(0, 0, 128, 64, frames[i]);
		OLED_Update();
		Delay_ms(16);
		i = (i + 1) % 25;
    }
    return 0;
}