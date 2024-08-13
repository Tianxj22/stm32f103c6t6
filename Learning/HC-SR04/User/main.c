#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"
#include "OLED.h"
#include "Timer.h"
#include "HC-SR04.h"

int main()
{
    OLED_Init();
    HCSR04_Init();
    OLED_Clear();

    // i = 0;
    while (1)
    {
        OLED_SetCursor(8, 3);
        OLED_printf(OLED_FONTSIZE_8X16, "Distance = %.2f", HCSR04_GetDistance());
        OLED_Update();
    }
    return 0;
}