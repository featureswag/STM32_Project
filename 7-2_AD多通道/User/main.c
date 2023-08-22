#include "stm32f10x.h" // Device header
#include "delay.h"
#include "oled.h"
#include "ad.h"

uint16_t AD_Value_0, AD_Value_1, AD_Value_2, AD_Value_3;
uint8_t i;
float AD_Voltage;
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
		// get 10 times AD value and calculate average value
		for (i = 0; i < 10; i++)
		{
			AD_Value_0 += AD_GetValue(ADC_Channel_0);
			AD_Value_1 += AD_GetValue(ADC_Channel_1);
			AD_Value_2 += AD_GetValue(ADC_Channel_2);
			AD_Value_3 += AD_GetValue(ADC_Channel_3);
			delay_ms(10);
		}
		AD_Value_0 /= 10;
		AD_Value_1 /= 10;
		AD_Value_2 /= 10;
		AD_Value_3 /= 10;
		OLED_ShowNum(1,6,AD_Value_0,4);/* OLED show AD value, min:0, max:4095 */
		OLED_ShowNum(2,6,AD_Value_1,4);
		OLED_ShowNum(3,6,AD_Value_2,4);
		OLED_ShowNum(4,6,AD_Value_3,4);
		delay_ms(100);
		AD_Value_0 = 0; // clear AD value
		AD_Value_1 = 0;
		AD_Value_2 = 0;
		AD_Value_3 = 0;
	}
}
