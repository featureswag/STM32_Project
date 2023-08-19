#include "stm32f10x.h" // Device header
#include "delay.h"
#include "servo.h"
#include "oled.h"
#include "math.h"
#include "key.h"


uint8_t keyCode;
float   angle;
int main(void)
{
	OLED_Init();
	KEY_Init();	
	SERVO_Init();
	OLED_ShowString(1,1,"SERVO TEST");
	while (1)
	{
		keyCode = KEY_Read();
		if(keyCode == 1)
		{
			angle+=30;
			if(angle > 180)
				angle = 0;
		}
		SERVO_SetAngle(angle);
		OLED_ShowString(2,1,"Angle:");
		OLED_ShowNum(2,8,angle,3);

	}
}
