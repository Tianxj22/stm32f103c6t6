#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "LD2420.h"

uint8_t i = 0;

int main()
{
  OLED_Init();
  OLED_Clear();
  OLED_SetCursor(0, 0);
  OLED_printf(OLED_FONTSIZE_8X16, "LD2420 Data:");
  OLED_Update();
  LD2420_Init();
  // LD2420_GetVersionNum();
  // i = 0;
  while (1)
  {
    // i = LD2420_GetDataFlag();
    // OLED_SetCursor(4, 6);
    // OLED_printf(OLED_FONTSIZE_8X16, "%d", i);
    // OLED_Update();
    // if(i)
    // {
    //   OLED_SetCursor(4, 2);
    //   OLED_printf(OLED_FONTSIZE_8X16, "%03d", LD2420_GetData());
    //   OLED_Update();
    // }
    OLED_SetCursor(0, 2);
    OLED_printf(OLED_FONTSIZE_8X16, "%03d  %d", LD2420_GetData(), LD2420_GetOT2Data());
    OLED_Update();
  }
  return 0;
}