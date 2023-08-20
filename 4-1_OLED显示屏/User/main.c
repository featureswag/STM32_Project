#include "stm32f10x.h" // Device header
#include "delay.h"
#include "oled.h"

int main(void)
{
	OLED_Init();
	
	// OLED_ShowChar(1,1,'A');
	OLED_ShowString(1,1,"Hello World!"); 
	OLED_ShowNum(2,1,1234,4); 
	OLED_ShowSignedNum(2,6,-1234,4); 
	OLED_ShowHexNum(3,1,0xAA55,4);
	OLED_ShowBinNum(4,1,0xAA55,16);
	while (1)
	{
	
	}
}
