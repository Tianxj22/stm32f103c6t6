#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "PWM.h"
#include "Motor.h"

int16_t Speed = 0;
uint8_t KeyNum;

int main()
{
    OLED_Init();
    Key_Init();
    Motor_Init();
    OLED_Clear();

    Motor_SetSpeed(0);

    while (1)
    {
        KeyNum = GetKey();
        if(KeyNum == 1)
        {
            Speed += 20;
            if(Speed > 100)
            {
                Speed = -100;
            }
        }
        Motor_SetSpeed(Speed);
        OLED_SetCursor(8, 3);
        OLED_printf(OLED_FONTSIZE_8X16, "Speed = %d", Speed);
        OLED_Update();
    }
    return 0;
}