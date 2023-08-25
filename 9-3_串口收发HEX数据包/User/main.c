#include "stm32f10x.h" // Device header
#include "delay.h"
#include "oled.h"
#include "serial.h"
#include "key.h"

uint8_t KeyCode = 0;

int main(void)
{
	OLED_Init();
	KEY_Init();
	SERIAL_Init();
	
	OLED_ShowString(1,1,"TX Packet:");
	OLED_ShowString(3,1,"RX Packet:");
	SERIAL_TxPacket[0] = 0x01;
	SERIAL_TxPacket[1] = 0x02;
	SERIAL_TxPacket[2] = 0x03;
	SERIAL_TxPacket[3] = 0x04;
	SERIAL_SendPacket();
	while (1)
	{
		uint8_t i;
		KeyCode = KEY_Read();
		if(KeyCode == SET)
		{
			SERIAL_TxPacket[0] ++;
			SERIAL_TxPacket[1] ++;
			SERIAL_TxPacket[2] ++;
			SERIAL_TxPacket[3] ++;
			SERIAL_SendPacket();
			for(i=0; i<4; i++)
			{
				OLED_ShowHexNum(2,1+i*3,SERIAL_TxPacket[i],2);
			}
		}
		if(SERIAL_GetRxFlag())
		{
			for(i=0; i<4; i++)
			{
				OLED_ShowHexNum(4,1+i*3,SERIAL_RxPacket[i],2);
			}
		}
	}
}
