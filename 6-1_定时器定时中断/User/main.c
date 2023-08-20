#include "stm32f10x.h" // Device header
#include "delay.h"
#include "OLED.h"
#include "timer.h"

uint16_t display_nums;
int main(void)
{
	OLED_Init();
	TIMER_Init();
	OLED_ShowString(1,1,"TIMER-INTERRUPT"); 
	OLED_ShowString(2,1,"Count:"); 
	OLED_ShowString(3,1,"TIM2 :");


	while (1)
	{
		OLED_ShowNum(2,8,display_nums,5); /* display Timer count */
		OLED_ShowNum(3,8,TIM_GetCounter(TIM2),5);/* display TIM Counter Status */
	}
}
