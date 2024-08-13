#ifndef __OLED__
#define __OLED__

#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"

/**
 * @enum OLED字体大小的类型
 */
#define OLED_FONTSIZE_6X8   6
#define OLED_FONTSIZE_8X16  8

#define OLED_SCL GPIO_Pin_9
#define OLED_SDA GPIO_Pin_8

#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define OLED_X_MAX 	128
#define OLED_Y_MAX 	64	 
#define OLED_PAGE_MAX 8

void OLED_Init(void);
void OLED_WriteCommand(uint8_t Command);
void OLED_WriteData(uint8_t* Data, uint8_t Count);
void OLED_SetCursor(uint8_t X, uint8_t Page);
void OLED_Update(void);
void OLED_ClearArea(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);
void OLED_Clear(void);
void OLED_ShowChar(char Ch, uint8_t FontSize);
void OLED_ShowString(char* String, uint8_t Fontsize);
void OLED_ShowImage(uint8_t X, uint8_t Page, uint8_t Width, uint8_t Height, const uint8_t *Image);
void OLED_ShowNum(uint16_t Num, uint8_t FontSize);
void OLED_ShowHexNum(uint16_t Num, uint8_t FontSize);
void OLED_DrawPoint(uint8_t X, uint8_t Y);
uint8_t OLED_GetPoint(uint8_t X, uint8_t Y);
void OLED_printf(uint8_t FontSize, const char *format, ...) ;

#endif