#include "stm32f10x.h" // Device header
#include "delay.h"
#include "OLED.h"
#include "encoder.h"

int16_t count;
int main(void)
{
	OLED_Init();
	ENCODER_Init();
	OLED_ShowString(1,1,"ENCODER TEST");
	OLED_ShowString(2,1,"COUNT:");

	while (1)
	{
		count += ENCODER_GetCount();
		OLED_ShowSignedNum(2,7,count,5);
	}
}
