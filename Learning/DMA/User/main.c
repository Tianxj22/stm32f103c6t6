#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "MyDMA.h"

uint8_t DataA[] = {0X01, 0X02, 0X03, 0X04};
uint8_t DataB[] = {0, 0, 0, 0};

int main()
{
    OLED_Init();
    OLED_Clear();
    

    MyDMA_Init((uint32_t)DataA, (uint32_t)DataB, 4);

    
	OLED_Update();
    while (1)
    {
        DataA[0] ++;
        DataA[1] ++;
        DataA[2] ++;
        DataA[3] ++;

        OLED_SetCursor(0, 0);
        OLED_printf(OLED_FONTSIZE_8X16, "DataA: %x", (uint32_t)(DataA));
        OLED_SetCursor(0, 2);
        OLED_printf(OLED_FONTSIZE_8X16, "%x, %x, %x, %x", DataA[0], DataA[1], DataA[2], DataA[3]);
        OLED_SetCursor(0, 4);
        OLED_printf(OLED_FONTSIZE_8X16, "DataB: %x", (uint32_t)(DataB));
        OLED_SetCursor(0, 6);
        OLED_printf(OLED_FONTSIZE_8X16, "%x, %x, %x, %x", DataB[0], DataB[1], DataB[2], DataB[3]);
        OLED_Update();

        Delay_ms(1000);

        MyDMA_Transfer();

        OLED_SetCursor(0, 0);
        OLED_printf(OLED_FONTSIZE_8X16, "DataA: %x", (uint32_t)(DataA));
        OLED_SetCursor(0, 2);
        OLED_printf(OLED_FONTSIZE_8X16, "%x, %x, %x, %x", DataA[0], DataA[1], DataA[2], DataA[3]);
        OLED_SetCursor(0, 4);
        OLED_printf(OLED_FONTSIZE_8X16, "DataB: %x", (uint32_t)(DataB));
        OLED_SetCursor(0, 6);
        OLED_printf(OLED_FONTSIZE_8X16, "%x, %x, %x, %x", DataB[0], DataB[1], DataB[2], DataB[3]);
        OLED_Update();

        Delay_ms(1000);
    }
    return 0;
}