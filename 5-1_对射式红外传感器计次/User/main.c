#include "stm32f10x.h" // Device header
#include "delay.h"
#include "OLED.h"
#include "ir_proximity_sensor.h"

int main(void)
{
	OLED_Init();
	IR_ProximitySensor_Init();
	OLED_ShowString(1,1,"IR:COUNTING-TEST"); 
	OLED_ShowString(2,1,"COUNT:");

	while (1)
	{
		OLED_ShowNum(2,8,IR_ProximitySensor_GetCount(),5);
		delay_ms(10); // delay for oled refresh
	}
}
