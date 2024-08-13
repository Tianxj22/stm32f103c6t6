#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
uint8_t i = 0;

int main()
{
	OLED_Init();

	Serial_Init();


	
	OLED_Clear();

	OLED_Update();

  // i = 0;
	while (1)
	{
		if(Serial_GetRxFlag())
		{
			i = Serial_GetRxData();
			u1_printf("I heard %d\r\n", i);
		}
	}
	return 0;
}