#include "stm32f10x.h"                  // Device header

void ENCODER_Init(void)
{
  
   /* *
    * 1. Enable RCC clocks for GPIO and TIM. */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    /* *
    * 2. Initialize GPIO. Configure GPIO pins as input mode:
        - * a. Pull-up input
        - * b. or Floating input */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
     /* *
    *3. Configure the timer's base unit. Set CNT counter to increment
     */
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // not working
    TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1; // ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1; // No prescaling
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

    /* *
    *4. Configure the input capture unit:
        - * a. Filter
        - * b. Polarity */
    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICStructInit(&TIM_ICInitStructure); // initialize the struct with default values
    // Channel 1
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter = 0xF;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);// Configure the input capture unit of channel 1
    // Channel 2
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICFilter = 0xF;
    TIM_ICInit(TIM3, &TIM_ICInitStructure); // Configure the input capture unit of channel 2

    /* *
    * 5. Conigure Encoer Interface Mode. 
        -* a. TIM_EncoderMode_TI12.
        -* b. encoder mode.
        -* c. polarity of IC1 and IC2. */
    TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);

     /* *
    * 6. Start the timer. */ 
    TIM_Cmd(TIM3,ENABLE);
}

int16_t ENCODER_GetCNT(void)
{
    int16_t display_nums;
    display_nums = TIM_GetCounter(TIM3);
    TIM_SetCounter(TIM3, 0);
    return display_nums;
}
