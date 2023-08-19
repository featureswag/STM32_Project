#include "stm32f10x.h" // Device header
#include "delay.h"

int main(void)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 	// Enable clock for GPIOB

	GPIO_InitTypeDef GPIO_InitStructure; 				  	// GPIO structure declaration for LED

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  		// Output push-pull mode
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 		  		// Pin 12
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 		// Speed 50MHz

	GPIO_Init(GPIOB, &GPIO_InitStructure); 					// Initialize GPIOB

	
	
	while (1)
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_12); 					// Turn on BEEP
		delay_ms(100);											// Delay 500ms
		GPIO_SetBits(GPIOB, GPIO_Pin_12);						// Turn off BEEP
		delay_ms(100);	
		GPIO_ResetBits(GPIOB, GPIO_Pin_12); 					// Turn on BEEP
		delay_ms(100);											// Delay 500ms
		GPIO_SetBits(GPIOB, GPIO_Pin_12);						// Turn off BEEP
		delay_ms(700);	
		GPIO_ResetBits(GPIOB, GPIO_Pin_12); 					// Turn on BEEP
		delay_ms(1000);											// Delay 500ms
		GPIO_SetBits(GPIOB, GPIO_Pin_12);						// Turn off BEEP
		delay_ms(1000);	
	}
}
