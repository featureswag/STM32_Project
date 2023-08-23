#include "stm32f10x.h" // Device header
#include "delay.h"
#include "oled.h"
#include "serial.h"

int main(void)
{
	OLED_Init();
	SERIAL_Init();	


	SERIAL_Printf("你好世界");
	while (1)
	{
	
	}
}
