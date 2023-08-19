#include "stm32f10x.h" // Device header
#include "delay.h"

int main(void)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 	// Enable clock for GPIOA

	GPIO_InitTypeDef GPIO_InitStructure; 				  	// GPIO structure declaration for LED

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  		// Output push-pull mode
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 		  		// Pin 0
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 		// Speed 50MHz

	GPIO_Init(GPIOA, &GPIO_InitStructure); 					// Initialize GPIOA

	
	
	while (1)
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_0); 						// Turn on LED
		delay_ms(500);											// Delay 500ms
		GPIO_SetBits(GPIOA, GPIO_Pin_0);						// Turn off LED
		delay_ms(500);	
		GPIO_WriteBit(GPIOA, GPIO_Pin_0,Bit_RESET);      		// Turn on LED
		delay_ms(500);											// Delay 500ms
		GPIO_WriteBit(GPIOA, GPIO_Pin_0,Bit_SET);      			// Turn off LED 
		delay_ms(500);											// Delay 500ms
	}
}
