#include "OLED.h"
#include "MyI2C.h"
#include "Delay.h"
#include "OLED_font.h"
#include "stdio.h"
#include <stdarg.h>

#define NUM2HEX_CHAR(x) (x >= 10) ? (x - 10 + 'A') : (x + '0')

uint8_t OLED_DisplayBuf[OLED_PAGE_MAX][OLED_X_MAX];
uint8_t Cur_X;
uint8_t Cur_Page;

/**
 * @brief 根据字体大小更新光标位置
 * @param FontSize 字体大小
 */
void _Update_Cursor(uint8_t FontSize)
{
    Cur_X += FontSize;
    if(Cur_X >= OLED_X_MAX)
    {
        Cur_X = 0;
        Cur_Page += (FontSize == OLED_FONTSIZE_6X8 ? 1 : 2);
    }
}

/**
 * @brief 判断当前位置是否足够输出
 * @param FontSize 字体的大小
 */
void _OLED_Check(uint8_t FontSize)
{
    if(Cur_X + FontSize >= OLED_X_MAX)
    {
        _Update_Cursor(FontSize);
    }
}

/**
 * @brief 初始化OLED模块
 */
void OLED_Init(void)
{
    MyI2C_Init();
    Delay_ms(100);

    OLED_WriteCommand(0XAE);
    OLED_WriteCommand(0X00);
    OLED_WriteCommand(0X10);
    OLED_WriteCommand(0X40);
    OLED_WriteCommand(0XB0);
    OLED_WriteCommand(0X81);
    OLED_WriteCommand(0XFF);
    OLED_WriteCommand(0XA1);
    OLED_WriteCommand(0XA6);
    OLED_WriteCommand(0XA8);
    OLED_WriteCommand(0X3F);
    OLED_WriteCommand(0XC8);
    OLED_WriteCommand(0XD3);
    OLED_WriteCommand(0X00);

    OLED_WriteCommand(0XD5);
    OLED_WriteCommand(0X80);

    OLED_WriteCommand(0XD8);
    OLED_WriteCommand(0X05);

    OLED_WriteCommand(0XD9);
    OLED_WriteCommand(0XF1);

    OLED_WriteCommand(0XDA);
    OLED_WriteCommand(0X12);

    OLED_WriteCommand(0XDB);
    OLED_WriteCommand(0X30);

    OLED_WriteCommand(0X8D);
    OLED_WriteCommand(0X14);

    OLED_WriteCommand(0XAF);

    Delay_ms(100);
}

/**
 * @brief OLED写命令
 * @param Command 命令的字节信息
 */
void OLED_WriteCommand(uint8_t Command)
{
    MyI2C_Start();
    MyI2C_SendByte(0X78);       // 寻址
    MyI2C_ReceiveAck();
    MyI2C_SendByte(0X00);       // 控制信息
    MyI2C_ReceiveAck();
    MyI2C_SendByte(Command);    //
    MyI2C_ReceiveAck();
    MyI2C_Stop();
}

/**
 * @brief OLED写数据
 * @param Data 要写的数据
 * @param Count 发送的数据个数
 */
void OLED_WriteData(uint8_t* Data, uint8_t Count)
{
    uint8_t i;
    MyI2C_Start();
    MyI2C_SendByte(0X78);       // 寻址
    MyI2C_ReceiveAck();
    MyI2C_SendByte(0X40);       // 控制信息
    MyI2C_ReceiveAck();
    for(i = 0; i < Count; i++){    
        MyI2C_SendByte(Data[i]);    //
        MyI2C_ReceiveAck();
    }
    MyI2C_Stop();
}

/**
 * @brief 向用户提供的改变光标位置的接口
 * @param  X 以左上角为原点，向右方向的坐标，范围：0~127
 * @param  Page 以左上角为原点，向下方向的坐标，范围：0~7
 */
void OLED_SetCursor(uint8_t X, uint8_t Page)
{
    Cur_X = X;
    Cur_Page = Page;
}

/**
  * @brief  OLED设置光标位置
  * @param  X 以左上角为原点，向右方向的坐标，范围：0~127
  * @param  Page 以左上角为原点，向下方向的坐标，范围：0~7
  * @retval 无
  */
void _OLED_SetCursor(uint8_t X, uint8_t Page)
{
	OLED_WriteCommand(0xB0 | Page);					//设置Y位置
	OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));	//设置X位置高4位
	OLED_WriteCommand(0x00 | (X & 0x0F));			//设置X位置低4位
}

/**
 * @brief 更新OLED的显示内容
 */
void OLED_Update(void)
{
    uint8_t i;
    for(i = 0; i < 8; i++){ 
        _OLED_SetCursor(0, i);
        OLED_WriteData(OLED_DisplayBuf[i], 128);
    }
}

/**
 * @brief 清除部分区域的函数
 * @param X 横坐标 0~127
 * @param Y 纵坐标 0~63
 * @param Width 图片宽度
 * @param Height 图片高度
 */
void OLED_ClearArea(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height)
{
    uint8_t i, j;
    for(i = X; i < X + Width; i++)
    {
        for(j = Y; j < Y + Height; j++)
        {
            OLED_DisplayBuf[j / 8][i] &= ~(0X01 << (j % 8));
        }
    }
}

/**
 * @brief OLED清屏函数
 */
void OLED_Clear(void)
{
    OLED_ClearArea(0, 0, 128, 64);
}

/**
 * @brief OLED输出6x8的小字符
 * @param Ch 要输出的字符
 */
void OLED_ShowSmallChar(char Ch)
{
    if(Ch < OLED_F6x8_START_ASCII | Ch > OLED_F6x8_END_ASCII)
    {
        return;
    }
    _OLED_Check(OLED_FONTSIZE_6X8);
    OLED_ShowImage(Cur_X, Cur_Page * 8, 6, 8, OLED_F6x8[Ch - OLED_F6x8_START_ASCII]);
    _Update_Cursor(OLED_FONTSIZE_6X8);
}

/**
 * @brief OLED输出8x16的大字符
 * @param Ch 要输出的字符
 */
void OLED_ShowHugeChar(char Ch)
{
    if(Ch < OLED_F8x16_START_ASCII | Ch > OLED_F6x8_END_ASCII)
    {
        return;
    }
    _OLED_Check(OLED_FONTSIZE_8X16);
    OLED_ShowImage(Cur_X, Cur_Page * 8, 8, 16, OLED_F8x16[Ch - OLED_F8x16_START_ASCII]);
    _Update_Cursor(OLED_FONTSIZE_8X16);
}

/**
 * @brief OLED输出字符
 * @param Ch 要输出的字符
 * @param FontSize 字体大小
 *      @arg OLED_FONTSIZE_6X8 OLED_FONTSIZE_6X8
 */
void OLED_ShowChar(char Ch, uint8_t FontSize)
{
    if(FontSize == OLED_FONTSIZE_6X8)
    {
        OLED_ShowSmallChar(Ch);
    }
    else if(FontSize == OLED_FONTSIZE_8X16)
    {
        OLED_ShowHugeChar(Ch);
    }
}

/**
 * @brief OLED输出字符串
 * @param Ch 要输出的字符
 * @param FontSize 字体大小
 *      @arg OLED_FONTSIZE_6X8 OLED_FONTSIZE_6X8
 */
void OLED_ShowString(char* String, uint8_t FontSize)
{
    uint8_t i;
    for(i = 0; String[i] != '\0'; i++)
    {
        OLED_ShowChar(String[i], FontSize);
    }
}

/**
 * @brief OLED显示图片
 * @param X 横坐标 0~127
 * @param Y 纵坐标 0~63
 * @param Width 图片宽度
 * @param Height 图片高度
 * @param Image 图片信息
 */
void OLED_ShowImage(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height, const uint8_t *Image)
{
    uint8_t i, j;
    OLED_ClearArea(X, Y, Width, Height);
    for(j = 0; j < (Height - 1) / 8 + 1; j++)
    {
        for(i = 0; i < Width; i++)
        {
            OLED_DisplayBuf[Y / 8 + j][X + i] |= Image[j * Width + i] << (Y % 8);
            OLED_DisplayBuf[Y / 8 + j + 1][X + i] |= Image[j * Width + i] >> (8 - Y % 8);
        }
    }
}

/**
 * @brief OLED屏幕在指定位置画点
 * @param X 横坐标 0~127
 * @param Y 纵坐标 0~63
 */
void OLED_DrawPoint(uint8_t X, uint8_t Y)
{
    OLED_DisplayBuf[Y / 8][X] |= (0X01 << (Y % 8));
}

/**
 * @brief 获取OLED屏幕指定位置的点是否点亮
 * @param X 横坐标 0~127
 * @param Y 纵坐标 0~63
 * @retval 若点亮则返回1, 否则返回0
 */
uint8_t OLED_GetPoint(uint8_t X, uint8_t Y)
{
    return (OLED_DisplayBuf[Y / 8][X] & (0X01 << (Y % 8)) ? 1 : 0);
}

/**
 * @brief OLED以十进制输出字符, 
 * @param Num 输出的数字
 * @param FontSize 字体大小
 *      @arg OLED_FONTSIZE_6X8 OLED_FONTSIZE_6X8
 */
void OLED_ShowNum(uint32_t Num, uint8_t FontSize)
{
    char s[20];
    uint8_t i = 0;
    if(!Num)
    {
        OLED_ShowChar('0', FontSize);
    }
    while(Num)
    {
        s[i] = Num % 10 + '0';
        Num /= 10;
        i++;
    }
    while(i)
    {
        i--;
        OLED_ShowChar(s[i], FontSize);
    }
}

/**
 * @brief OLED以十六进制输出字符, 
 * @param Num 输出的数字
 * @param FontSize 字体大小
 *      @arg OLED_FONTSIZE_6X8 OLED_FONTSIZE_6X8
 */
void OLED_ShowHexNum(uint32_t Num, uint8_t FontSize)
{
    char s[20];
    uint8_t i = 0;
    if(!Num)
    {
        OLED_ShowChar('0', FontSize);
    }
    while(Num)
    {
        s[i] = NUM2HEX_CHAR((Num % 16));
        Num /= 16;
        i++;
    }
    while(i)
    {
        i--;
        OLED_ShowChar(s[i], FontSize);
    }
}

/**
 * @brief 以标准化的格式调用OLED的输出
 * @param FontSize 字体大小
 * @param format 标准化字符串
 */
void OLED_printf(uint8_t FontSize, const char *format, ...) 
{
    char String[100];
    va_list arg;
    va_start(arg, format);
    vsprintf(String, format, arg);
    va_end(arg);
    OLED_ShowString(String, FontSize);
}
