#include "stm32f10x.h" // Device header
#include "delay.h"
#include "oled.h"
#include "motor.h"
#include "key.h"

uint8_t keyCode;
int8_t 	MOTOR_Speed;
int main(void)
{
	
	OLED_Init();
	MOTOR_Init();	
	KEY_Init();
	OLED_ShowString(1,1,"DC MOTOR TEST");
	OLED_ShowString(2,1,"Speed:");
	MOTOR_SetSpeed(0);
	while (1)
	{
		keyCode = KEY_Read();
		if(keyCode == 1)
		{
			MOTOR_Speed += 20;
			if(MOTOR_Speed > 100)
			{
				MOTOR_Speed = 0;
			}
		}
		MOTOR_SetSpeed(MOTOR_Speed);
		OLED_ShowSignedNum(2,8,MOTOR_Speed,3);
	}
}
