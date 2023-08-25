#ifndef __SERIAL_H
#define __SERIAL_H

#include "stdio.h"
#include "stm32f10x.h"

void SERIAL_Init(void);
void SERIAL_SendByte(uint8_t byte_data);
void SERIAL_SendArray(uint8_t *nums, uint16_t numsSize);
void SERIAL_SendString(char *string);
void SERIAL_SendNumber(uint32_t number, uint8_t size);
int fputc(int ch,FILE *f);
void SERIAL_Printf(char *format,...);
void SERIAL_SendPacket(void);

extern uint8_t SERIAL_RxPacket[];
extern uint8_t SERIAL_TxPacket[];
uint8_t SERIAL_GetRxFlag(void);


#endif
