#ifndef __PWM__
#define __PWM__

#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"

/**
 * @defgroup PWM相关接口定义
 */
#define PWM_RCC_APB2Periph RCC_APB2Periph_GPIOA
#define PWM_GPIO_GROUP GPIOA
#define PWM_GPIO_PIN GPIO_Pin_2

void PWM_Init(void);
void PWM_SetCompare(uint16_t Compare);

#endif