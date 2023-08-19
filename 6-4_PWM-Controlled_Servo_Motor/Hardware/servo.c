#include "stm32f10x.h"                  // Device header
#include "pwm.h"
/**
 * @brief Servo Initialization Function  [舵机初始化函数]
 * @param None
 * @retval None
 */
void SERVO_Init(void)
{
    PWM_Init(); // PWM Initialization    
}

/* 
    |-------|-----------|
    | Angle | CCR_Value |
    |-------|-----------|
    |   0   |    500    |
    |-------|-----------|
    |  180  |    2500   |
    |-------|-----------|
  Equation  ==> [ Angle / 180 * 2000 ] + 500 
 */

/**
 * @brief  Set Servo Angle  [设置舵机角度]
 * @param  angle: Angle value [角度值]
 * @retval None
 */
void SERVO_SetAngle(float angle)
{
    float set_angle = (angle / 180 * 2000 ) + 500;
    PWM_SetCompare_2(set_angle);
}
