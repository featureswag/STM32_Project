#include "stm32f10x.h"                  // Device header
#include "delay.h"

void SOFR_I2C_W_SCL(uint8_t bitvalue)
{
  GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)bitvalue);
  delay_us(10);
}

void SOFR_I2C_W_SDA(uint8_t bitvalue)
{
  GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)bitvalue);
  delay_us(10);
}

uint8_t SOFR_I2C_R_SCL(void)
{
  uint8_t bitvalue;
  bitvalue = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10);
  delay_us(10);
  return bitvalue;
}

uint8_t SOFR_I2C_R_SDA(void)
{
  uint8_t bitvalue;
  bitvalue = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
  delay_us(10);
  return bitvalue;
}

void SOFR_I2C_Init(void)
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);       // Enable GPIOB clock
    GPIO_InitTypeDef GPIO_InitStructure;                        // Define GPIO_InitStructure
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_OD;           // Mode: OUT-DRAIN
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10 | GPIO_Pin_11;    // Pin: 10 & 11
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;           // Speed: 50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);                      // Initialize GPIOB

    GPIO_SetBits(GPIOB,GPIO_Pin_10 | GPIO_Pin_11); 
}

void SOFR_I2C_Start(void)
{
  SOFR_I2C_W_SDA(1);
  SOFR_I2C_W_SCL(1);
  SOFR_I2C_W_SDA(0);
  SOFR_I2C_W_SCL(0);
}

void SOFR_I2C_Stop(void)
{
  SOFR_I2C_W_SDA(0);
  SOFR_I2C_W_SCL(1);
  SOFR_I2C_W_SDA(1);
}

void SOFR_I2C_Sendbyte(uint8_t byte)
{
  uint8_t i;
  for(i=0;i<8;++i)
  {
    SOFR_I2C_W_SDA(byte & 0x80);
    SOFR_I2C_W_SCL(1);
    SOFR_I2C_W_SCL(0);
  }
}
uint8_t SOFR_I2C_Receivebyte(void)
{
  uint8_t byte=0x00,i;
  SOFR_I2C_W_SDA(1);
  for(i=0;i<8;++i)
  {
    SOFR_I2C_W_SCL(1);
    if(SOFR_I2C_R_SCL() == 1)
    {
      byte |= (0x80>>i);
    }
    SOFR_I2C_W_SCL(0);
  }
  return byte;
}

void SOFR_I2C_SendAck(uint8_t ack)
{
  SOFR_I2C_W_SDA(ack);
  SOFR_I2C_W_SCL(1);
  SOFR_I2C_W_SCL(0);
}

uint8_t SOFR_I2C_ReceiveAck(void)
{
  uint8_t ack;
  SOFR_I2C_W_SDA(1);
  SOFR_I2C_W_SCL(1);
  ack = SOFR_I2C_R_SDA();
  SOFR_I2C_W_SCL(0);
  return ack;
}
