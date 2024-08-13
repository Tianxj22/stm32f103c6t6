#ifndef __L298N__
#define __L298N__

#include "stm32f10x.h"                  // Device header
#define USE_STDPERIPH_DRIVER
#include "stm32f10x_conf.h"

/**
 * @defgroup L298N相关引脚与常量
 */
#define L298N_RCC_APB2Periph RCC_APB2Periph_GPIOA
#define L298N_GPIO_GROUP GPIOA
#define L298N_GPIO_IN1 GPIO_Pin_4
#define L298N_GPIO_IN2 GPIO_Pin_5
#define L298N_GPIO_IN3 GPIO_Pin_6
#define L298N_GPIO_IN4 GPIO_Pin_7
#define L298N_GPIO_ENA GPIO_Pin_2
#define L298N_GPIO_ENB GPIO_Pin_2

/**
 * 枚举电机的状态
 */
typedef enum{
    Forward,
    Backward,
    Stop
}MotorStatus;

/**
 * @defgroup 直接控制左右电机运动的宏定义方式
 */
#define L298N_LEFT_FORWARD  GPIO_SetBits(L298N_GPIO_GROUP, L298N_GPIO_IN1); GPIO_ResetBits(L298N_GPIO_GROUP, L298N_GPIO_IN2)
#define L298N_LEFT_BACKWARD GPIO_SetBits(L298N_GPIO_GROUP, L298N_GPIO_IN2); GPIO_ResetBits(L298N_GPIO_GROUP, L298N_GPIO_IN1)
#define L298N_LEFT_STOP     GPIO_ResetBits(L298N_GPIO_GROUP, L298N_GPIO_IN1); GPIO_ResetBits(L298N_GPIO_GROUP, L298N_GPIO_IN2)
#define L298N_RIGHT_FORWARD  GPIO_SetBits(L298N_GPIO_GROUP, L298N_GPIO_IN3); GPIO_ResetBits(L298N_GPIO_GROUP, L298N_GPIO_IN4)
#define L298N_RIGHT_BACKWARD GPIO_SetBits(L298N_GPIO_GROUP, L298N_GPIO_IN4); GPIO_ResetBits(L298N_GPIO_GROUP, L298N_GPIO_IN3)
#define L298N_RIGHT_STOP     GPIO_ResetBits(L298N_GPIO_GROUP, L298N_GPIO_IN3); GPIO_ResetBits(L298N_GPIO_GROUP, L298N_GPIO_IN4)

void L298N_Init();
void L298N_SetLeftMotor(uint16_t PwmCompare, MotorStatus Status);
void L298N_SetRightMotor(uint16_t PwmCompare, MotorStatus Status);

#endif