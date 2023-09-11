#ifndef __SOFR_I2C_H
#define __SOFR_I2C_H

void SOFR_I2C_Init(void);
void SOFR_I2C_Start(void);
void SOFR_I2C_Stop(void);
void SOFR_I2C_Sendbyte(uint8_t byte);
uint8_t SOFR_I2C_Receivebyte(void);
void SOFR_I2C_SendAck(uint8_t ack);
uint8_t SOFR_I2C_ReceiveAck(void);

#endif
