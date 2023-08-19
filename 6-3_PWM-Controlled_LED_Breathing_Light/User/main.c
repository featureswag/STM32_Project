#include "stm32f10x.h" // Device header
#include "delay.h"
#include "oled.h"
#include "pwm.h"

uint8_t value;
int main(void)
{
	OLED_Init();
	PWM_Init();	
	
	while (1)
	{
		for(value = 0; value <= 100; value ++)
		{
			PWM_SetCompare_1(value);
			delay_ms(25);
 		}
		for(value = 0; value <= 100; value ++)
		{
			PWM_SetCompare_1(100-value);
			delay_ms(25);
 		}
	}
}
