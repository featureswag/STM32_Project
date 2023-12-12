#include "stm32f10x.h" // Device header
#include "delay.h"
#include "oled.h"
#include "serial.h"
#include "led.h"
#include <string.h>

int main(void)
{
	OLED_Init();
	SERIAL_Init();
	LED_Init();
	OLED_ShowString(1,1,"TX Packet:");
	OLED_ShowString(3,1,"RX Packet:");

	while (1)
	{
		if(SERIAL_Rx_Flag == SET)
		{
			OLED_ShowString(4,1,"                "); 
			OLED_ShowString(4,1,SERIAL_RxPacket);

			if(strcmp(SERIAL_RxPacket,"LED_ON") == 0)
			{
				LED_On_1();
				SERIAL_SendString("LED_ON\r\n");
				OLED_ShowString(2,1,"                "); 
				OLED_ShowString(2,1,"LED_IS_ON");
			}
			else if(strcmp(SERIAL_RxPacket,"LED_OFF") == 0)
			{
				LED_Off_1();
				SERIAL_SendString("LED_OFF\r\n");
				OLED_ShowString(2,1,"                ");
				OLED_ShowString(2,1,"LED_IS_OFF");
			}
			else
			{
				SERIAL_SendString("ERROR\r\n");
				OLED_ShowString(2,1,"                ");
				OLED_ShowString(2,1,"ERROR");
			}
			SERIAL_Rx_Flag = RESET;
		}
	}
}
