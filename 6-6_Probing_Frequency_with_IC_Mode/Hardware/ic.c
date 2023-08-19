#include "stm32f10x.h"                  // Device header

void IC_Init(void)
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
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
     /* *
    *3. Configure the timer's base unit. Set CNT counter to increment
        under the drive of the internal clock. */
    TIM_InternalClockConfig(TIM3);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1; // ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1; // PSC  --> 72MHz / 72 = 1MHz
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

    /* *
    *4. Configure the input capture unit:
        - * a. Filter
        - * b. Polarity
        - * c. !Direct or cross-channel
        - * d. Prescaler */
    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter = 0xF;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);

    /* *
    * 5. Select the trigger source for the slave mode. */
    TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);
   
     /* *
    * 6. Choose the action to be taken after the trigger. */
    TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);

     /* *
    * 7. Start the timer. */ 
    TIM_Cmd(TIM3,ENABLE);
}

uint32_t IC_GetFrequency(void)
{
    // return latest frequency
    return 1000000 / (TIM_GetCapture1(TIM3) + 1); 
}
