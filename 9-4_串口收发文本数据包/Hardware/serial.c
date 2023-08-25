#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

char SERIAL_RxPacket[100];
uint8_t SERIAL_Rx_Flag;

enum SERIAL_State
{
    SERIAL_State_WaitHead = 0,
    SERIAL_State_Receiving = 1,
    SERIAL_State_WaitTail = 2,
   
};
enum SERIAL_Packet
{
    SERIAL_Packet_Head = '@',
    SERIAL_Packet_1stTail = '\r',
    SERIAL_Packet_2ndTail = '\n',
};

void SERIAL_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef GPIO_InitStrucutre;
    GPIO_InitStrucutre.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStrucutre.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStrucutre.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStrucutre);

	GPIO_InitStrucutre.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStrucutre.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStrucutre.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStrucutre);
	
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1,&USART_InitStructure);

	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART1,ENABLE);
}

void SERIAL_SendByte(uint8_t byte_data)
{
    USART_SendData(USART1,byte_data);
    while(!USART_GetFlagStatus(USART1,USART_FLAG_TXE));
}

void SERIAL_SendArray(uint8_t *nums, uint16_t numsSize)
{
    uint8_t i;
    for(i=0; i<numsSize; ++i)
    {
        SERIAL_SendByte(nums[i]);
    }
}
void SERIAL_SendString(char *string)
{
    uint8_t i;
    for(i=0; string[i]!=0; ++i)
    {
        SERIAL_SendByte(string[i]);
    }
}
uint32_t SERIAL_Pow(uint32_t x, uint32_t y)
{
    uint32_t result = 1;
    while(y--)
    {
        result*=x;
    }
    return result;
}
void SERIAL_SendNumber(uint32_t number, uint8_t size)
{
    uint32_t div,data;
    uint8_t i;
    for(i=size; i>0; i--)
    {
        div = SERIAL_Pow(10,i-1);
        data = (number/div) % 10;
        SERIAL_SendByte(data+'0');
    }
}
int fputc(int ch,FILE *f)
{
    SERIAL_SendByte(ch);
    return ch;
}

void SERIAL_Printf(char *format,...)
{
	char string[100];
	va_list arg;
	va_start(arg,format);
	vsprintf(string,format,arg);
	va_end(arg);
	SERIAL_SendString(string);
}

uint8_t SERIAL_GetRxFlag(void)
{
    if(SERIAL_Rx_Flag == 1)
    {
        SERIAL_Rx_Flag = 0;
        return 1;
    }
    return 0;
}

void USART1_IRQHandler(void)
{
    static uint8_t Rx_State = SERIAL_State_WaitHead;
    static uint8_t Rx_ArrayIndex = 0;
    if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
    {
        uint8_t Rx_Data = USART_ReceiveData(USART1);
        if(Rx_State == SERIAL_State_WaitHead)
        {
            if(Rx_Data == SERIAL_Packet_Head && SERIAL_Rx_Flag == 0)
            {
                Rx_State = SERIAL_State_Receiving;
                Rx_ArrayIndex = 0;
            }
        }
        else if(Rx_State == SERIAL_State_Receiving)
        {
            if(Rx_Data == SERIAL_Packet_1stTail)
            {
                Rx_State = SERIAL_State_WaitTail;
            }
            else{
                SERIAL_RxPacket[Rx_ArrayIndex++] = Rx_Data;
            }
        }
        else if(Rx_State == SERIAL_State_WaitTail)
        {
            if(Rx_Data == SERIAL_Packet_2ndTail)
            {
                Rx_State = SERIAL_State_WaitHead;
                SERIAL_RxPacket[Rx_ArrayIndex] = '\0';
                SERIAL_Rx_Flag = 1;
            }
        }
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);
    }
}
