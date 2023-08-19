#include "stm32f10x.h" // Device header
#include "delay.h"
#include "led.h"
#include "key.h"

#define LED_1 1
#define LED_2 2
#define ENABLE 	1
#define DISABLE 0

uint8_t KeyState;

int main(void)
{
	LED_Init();
	KEY_Init();

	while (1)
	{
		KeyState = KEY_Read();
		if(KeyState == 1){
			LED_Reverse_1();
		}
		if(KeyState == 2){
			LED_Reverse_2();
		}
	}
}
