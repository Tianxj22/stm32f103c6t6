#include "L298N.h"
#include "PWM.h"

/**
 * @brief 初始化L298N模块
 */
void L298N_Init()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = L298N_GPIO_IN1 | L298N_GPIO_IN2 | L298N_GPIO_IN3 | L298N_GPIO_IN4;
    
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    RCC_APB2PeriphClockCmd(L298N_RCC_APB2Periph, ENABLE);

    GPIO_Init(L298N_GPIO_GROUP, &GPIO_InitStruct);
    PWM_Init();
}


/**
 * @brief 控制左轮
 * @param PwmCompare 设置Pwm波的值
 * @param Status 左轮运行的状态
 *  @arg Forward 向前
 *  @arg Backward 向后
 *  @arg Stop 停止
 */
void L298N_SetLeftMotor(uint16_t PwmCompare, MotorStatus Status)
{
    PWM_SetCompare(PwmCompare);
    if(Status == Forward){
        L298N_LEFT_FORWARD;
    }
    else if(Status == Backward)
    {
        L298N_LEFT_BACKWARD;
    }
    else
    {
        L298N_LEFT_STOP;
    }
}

/**
 * @brief 控制左轮
 * @param PwmCompare 设置Pwm波的值
 * @param Status 右轮运行的状态
 *  @arg Forward 向前
 *  @arg Backward 向后
 *  @arg Stop 停止
 */
void L298N_SetRightMotor(uint16_t PwmCompare, MotorStatus Status)
{
    PWM_SetCompare(PwmCompare);
    if(Status == Forward){
        L298N_RIGHT_FORWARD;
    }
    else if(Status == Backward)
    {
        L298N_RIGHT_BACKWARD;
    }
    else
    {
        L298N_RIGHT_STOP;
    }
}