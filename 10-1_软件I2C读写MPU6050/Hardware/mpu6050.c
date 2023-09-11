#include "stm32f10x.h"                  // Device header
#include "sofr_i2c.h"
#include "mpu6050_reg.h"

#define MPU6050_ADDRESS 0xD0

void MPU6050_WriteReg(uint8_t RegAddress, uint8_t data)
{
    SOFR_I2C_Start();
    SOFR_I2C_Sendbyte(MPU6050_ADDRESS);
    SOFR_I2C_ReceiveAck();
    SOFR_I2C_Sendbyte(RegAddress);
    SOFR_I2C_ReceiveAck();
    SOFR_I2C_Sendbyte(data);
    SOFR_I2C_ReceiveAck();
    SOFR_I2C_Stop();
}

uint8_t MPU6050_ReadReag(uint8_t RegAddress)
{
    uint8_t data;
    SOFR_I2C_Start();
    SOFR_I2C_Sendbyte(MPU6050_ADDRESS);
    SOFR_I2C_ReceiveAck();
    SOFR_I2C_Sendbyte(RegAddress);
    SOFR_I2C_ReceiveAck();

    SOFR_I2C_Start();//restart condition
    SOFR_I2C_Sendbyte(MPU6050_ADDRESS | 0x01);// 1101 000(MPU6050 address) 1(read)
    SOFR_I2C_ReceiveAck();
    data = SOFR_I2C_Receivebyte();
    SOFR_I2C_SendAck(1);
    SOFR_I2C_Stop();

    return data;
}

void MPU6050_Init(void)
{
    SOFR_I2C_Init();
    MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);
    MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);
    MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);
    MPU6050_WriteReg(MPU6050_CONFIG, 0x06);
    MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);
    MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18); 
}

void MPU6050_GetValue(int16_t *accX,int16_t *accY,int16_t *accZ, 
                      int16_t *gyroX,int16_t *gyroY,int16_t *gyroZ)
{
    uint16_t dataH,dataL;
    dataH = MPU6050_ReadReag(MPU6050_ACCEL_XOUT_H);
    dataL = MPU6050_ReadReag(MPU6050_ACCEL_XOUT_L);
    *accX = (dataH<<8) | dataL;

    dataH = MPU6050_ReadReag(MPU6050_ACCEL_YOUT_H);
    dataL = MPU6050_ReadReag(MPU6050_ACCEL_YOUT_L);
    *accY = (dataH<<8) | dataL;

    dataH = MPU6050_ReadReag(MPU6050_ACCEL_ZOUT_H);
    dataL = MPU6050_ReadReag(MPU6050_ACCEL_ZOUT_L);
    *accZ = (dataH<<8) | dataL;

    dataH = MPU6050_ReadReag(MPU6050_GYRO_XOUT_H);
    dataL = MPU6050_ReadReag(MPU6050_GYRO_XOUT_L);
    *gyroX = (dataH<<8) | dataL;

    dataH = MPU6050_ReadReag(MPU6050_GYRO_YOUT_H);
    dataL = MPU6050_ReadReag(MPU6050_GYRO_YOUT_L);
    *gyroY = (dataH<<8) | dataL;

    dataH = MPU6050_ReadReag(MPU6050_GYRO_ZOUT_H);
    dataL = MPU6050_ReadReag(MPU6050_GYRO_ZOUT_L);
    *gyroZ = (dataH<<8) | dataL;
}
