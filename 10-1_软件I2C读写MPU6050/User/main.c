#include "stm32f10x.h" // Device header
#include "delay.h"
#include "oled.h"
#include "mpu6050.h"

int16_t ACCEX,ACCEY,ACCEZ,GYROX,GYROY,GYROZ;
int main(void)
{
	OLED_Init();
	MPU6050_Init();
	while (1)
	{
		MPU6050_GetValue(&ACCEX, &ACCEY, &ACCEZ, &GYROX, &GYROY, &GYROZ);
		OLED_ShowSignedNum(2,1,ACCEX,5);
		OLED_ShowSignedNum(2,1,ACCEY,5);
		OLED_ShowSignedNum(2,1,ACCEZ,5);
		OLED_ShowSignedNum(2,8,GYROX,5);
		OLED_ShowSignedNum(2,8,GYROY,5);
		OLED_ShowSignedNum(2,8,GYROZ,5);
	}
}
