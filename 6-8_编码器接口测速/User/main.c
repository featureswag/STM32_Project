#include "stm32f10x.h" // Device header
#include "delay.h"
#include "OLED.h"
#include "timer.h"
#include "encoder.h"

int16_t speed;

int main(void)
{
	OLED_Init();
	TIMER_Init();
	ENCODER_Init();
	OLED_ShowString(1,1,"ENCODER-TEST"); 
	OLED_ShowString(2,1,"Speed:");
	OLED_ShowString(2,14,"/s");
	while (1)
	{
		OLED_ShowSignedNum(2,8,speed,5); /* display Timer count */
	}
}
/* 
   * timer interrupt function.
*/
void TIM2_IRQHandler(void)
{
   /*
    * a. Check the Interrupt Status
    */
   if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
   {
       speed = ENCODER_GetCNT();
    /*
    * b. Clear the Interrupt Status
    */
       TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
   }

}
