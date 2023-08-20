#include "stm32f10x.h" // Device header
#include "delay.h"

int main(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 	// Enable clock for GPIOA

	GPIO_InitTypeDef GPIO_InitStructure; 				  	// GPIO structure declaration for LED

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  		// Output push-pull mode
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All; 			// Select all pins
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 		// Speed 50MHz

	GPIO_Init(GPIOA, &GPIO_InitStructure); 					// Initialize GPIOA

	while (1)
	{
	/********************* LED LOOP ****************************/
		GPIO_Write(GPIOA,~0x0001); // 0000 0000 0000 0001
		delay_ms(500);
		GPIO_Write(GPIOA,~0x0002); // 0000 0000 0000 0010
		delay_ms(500);
		GPIO_Write(GPIOA,~0x0004); // 0000 0000 0000 0100
		delay_ms(500);
		GPIO_Write(GPIOA,~0x0008); // 0000 0000 0000 1000
		delay_ms(500);
		GPIO_Write(GPIOA,~0x0010); // 0000 0000 0001 0000
		delay_ms(500);
		GPIO_Write(GPIOA,~0x0020); // 0000 0000 0010 0000
		delay_ms(500);
		GPIO_Write(GPIOA,~0x0040); // 0000 0000 0100 0000
		delay_ms(500);
		GPIO_Write(GPIOA,~0x0080); // 0000 0000 1000 0000
		delay_ms(500);
	
	/********************* LED SIRENS AND LIGHTS ***********************/
		//	u16 i;
		// // 0005 --> 红灯1、3同时闪烁
		// GPIO_Write(GPIOA,~0x0005); // 0000 0000 0000 0101
		// Delay_ms(300);
		// for(i=0; i<=4;i++){
		// 	GPIO_Write(GPIOA,~0x0005); // 0000 0000 0000 0101
		// 	Delay_ms(200);
		// 	GPIO_Write(GPIOA,~0x0000); // 0000 0000 0000 0000
		// 	Delay_ms(50);
		// }
		
		// // 0005 --> 蓝灯2、4同时闪烁
		// GPIO_Write(GPIOA,~0x000A); // 0000 0000 0000 1010
		// Delay_ms(300);
		// for(i=0; i<=4;i++){
		// 	GPIO_Write(GPIOA,~0x000A); // 0000 0000 0000 0101
		// 	Delay_ms(200);
		// 	GPIO_Write(GPIOA,~0x0000); // 0000 0000 0000 0000
		// 	Delay_ms(50);
		// }
		
		// //000F --> 红灯蓝灯同时闪烁
		// for(i=0; i<=5;i++){
		// 	GPIO_Write(GPIOA,~0x000F); // 0000 0000 0000 1111
		// 	Delay_ms(100);
		// 	GPIO_Write(GPIOA,~0x0000); // 0000 0000 0000 1111
		// 	Delay_ms(200);
		// }
	/********************* LED SIRENS AND LIGHTS (DONE) ***********************/
	}
}
