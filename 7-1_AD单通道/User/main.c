#include "stm32f10x.h" // Device header
#include "delay.h"
#include "oled.h"
#include "ad.h"

uint16_t AD_Value;
uint8_t i;
float AD_Voltage;
int main(void)
{
	OLED_Init();
	AD_Init();	
	OLED_ShowString(1,1,"AD TEST");
	OLED_ShowString(2,1,"AD Value:");
	OLED_ShowString(3,1,"Voltage:0.00V");
	AD_Value = 0;
	while (1)
	{
		// get 10 times AD value and calculate average value
		for (i = 0; i < 10; i++)
		{
			AD_Value += AD_GetValue();
			delay_ms(10);
		}
		AD_Value /= 10;
		AD_Voltage = (float) AD_Value * 3.3 / 4095; // calculate voltage
		OLED_ShowNum(2,11,AD_Value,4);/* OLED show AD value, min:0, max:4095 */
		OLED_ShowNum(3,9,AD_Voltage,1);/* OLED show voltage, min:0, max:3.3V */
		OLED_ShowNum(3,11,(uint16_t)(AD_Voltage*100) %100,2); /* OLED show voltage, min:0, max:3.3V */
		delay_ms(100);
		AD_Value = 0; // clear AD value
	}
}
