#include "stm32f10x.h" // Device header
#include "delay.h"
#include "oled.h"
#include "pwm.h"
#include "ic.h"


int main(void)
{
	OLED_Init();
	PWM_Init();	
	IC_Init();

	OLED_ShowString(1, 1, "IC_PB Test");
	OLED_ShowString(2, 1, "F: 00000 Hz");
	PWM_SetPrescaler(720 - 1);  // F = 72MHz / 720 / 100 = 1KHz
	PWM_SetCompare_1(50);	   // 50% duty cycle, duty = CCR / ARR(100) = 50 / 100 = 50%
	while (1)
	{
		OLED_ShowNum(2,4,IC_GetFrequency(),5);
	}
}
