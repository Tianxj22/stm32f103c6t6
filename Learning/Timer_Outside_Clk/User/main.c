#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"
#include "OLED.h"
#include "Timer.h"
// #include "Chicken.h"
uint16_t Num = 0;

int main()
{
    OLED_Init();
    Timer_Init();
    OLED_Clear();

    // i = 0;
    while (1)
    {
        OLED_SetCursor(8, 3);
        OLED_printf(OLED_FONTSIZE_8X16, "Num = %d", Num);
        OLED_SetCursor(8, 5);
        OLED_printf(OLED_FONTSIZE_8X16, "Cnt = %d", TIM_GetCounter(TIM2));
        OLED_Update();
    }
    return 0;
}

/**
 * @brief TIM2中断函数
 */
void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        Num++;
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}