#include "stm32f10x.h" // Device header
#include "delay.h"
#include "oled.h"
#include "dma_transfer.h"

uint8_t Data_A[] = {0x01,0x02,0x03,0x04};
uint8_t Data_B[] = {0,0,0,0};
uint8_t i;
int main(void)
{
	OLED_Init();
	DMA_TRANSFER_Init((uint32_t)Data_A,(uint32_t)Data_B,4);

	OLED_ShowString(1,1,"DATA A");
	OLED_ShowString(3,1,"DATA B");
	OLED_ShowHexNum(1,8,(uint32_t)Data_A,8);
	OLED_ShowHexNum(3,8,(uint32_t)Data_B,8);
	
	
	while (1)
	{
		for(i=0;i<4;i++)
		{
			Data_A[i]++;
		}

		for(i=0;i<4;i++)
		{
			OLED_ShowHexNum(2,1+i*3,Data_A[i],2);
		}
		delay_ms(1000);

		// start DMA transfer
		DMA_TRANSFER_Enable();
		for(i=0;i<4;i++)
		{
			OLED_ShowHexNum(4,1+i*3,Data_B[i],2);
		}
		delay_ms(1000);
	}
}
