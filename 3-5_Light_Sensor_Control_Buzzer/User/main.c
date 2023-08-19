#include "stm32f10x.h" // Device header
#include "delay.h"
#include "buzzer.h"
#include "light_sensor.h"
#include "led.h"

int main(void)
{
	LED_Init();
	BUZZER_Init();
	LIGHT_SENSOR_Init();

	while (1)
	{
		if(LIGHT_SENSOR_Read() == 1){
			LED_On_1();
			BUZZER_On();
			delay_ms(100);
			BUZZER_Off();
		}
		else{
			LED_Off_1();
		}
	}
}
