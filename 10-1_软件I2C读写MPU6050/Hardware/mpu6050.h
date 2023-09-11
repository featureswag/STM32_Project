#ifndef __MPU6050_H
#define __MPU6050_H

void MPU6050_WriteReg(uint8_t RegAddress, uint8_t data);
uint8_t MPU6050_ReadReag(uint8_t RegAddress);
void MPU6050_Init(void);
void MPU6050_GetValue(int16_t *accX,int16_t *accY,int16_t *accZ, 
                      int16_t *gyroX,int16_t *gyroY,int16_t *gyroZ);
#endif
