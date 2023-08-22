#include "stm32f10x.h" // Device header
#include "delay.h"
#include "oled.h"
#include "ad.h"


int main(void)
{
	OLED_Init();
	AD_Init();	
	// OLED_ShowString(1,1,"AD TEST");
	OLED_ShowString(1,1,"AD 0:");
	OLED_ShowString(2,1,"AD 1:");
	OLED_ShowString(3,1,"AD 2:");
	OLED_ShowString(4,1,"AD 3:");
	
	while (1)
	{
		// AD_GetValue();
		OLED_ShowNum(1,6,AD_Value[0],4);/* OLED show AD value, min:0, max:4095 */
		OLED_ShowNum(2,6,AD_Value[1],4);
		OLED_ShowNum(3,6,AD_Value[2],4);
		OLED_ShowNum(4,6,AD_Value[3],4);
		delay_ms(100);

	}
}
