#include "stm32f10x.h" // Device header
#include "delay.h"
#include "oled.h"
#include "serial.h"

uint8_t Rx_data;
int main(void)
{
	OLED_Init();
	SERIAL_Init();	
	OLED_ShowString(1,1,"RxData:");
	while (1)
	{
		if(SERIAL_GetRxFlag() == 1) 
		{
			Rx_data = SERIAL_GetRxData();
			SERIAL_SendByte(Rx_data);
			OLED_ShowHexNum(1,9,Rx_data,2);
		}
	}
}
