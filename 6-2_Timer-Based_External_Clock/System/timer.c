#include "stm32f10x.h"                  // Device header

extern uint16_t display_nums;
void IR_TriggerInit(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU; 
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void TIMER_Init(void)
{
    /* 
     * 1. Configure RCC:  Enable the internal clock. ( TIM2 )
         - enabling this will also turn on the timer's:
           a. Base clock.
           b. Entire peripheral clock.*/   
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
  
    // /* 
    //  * 2. Select the clock source for the time base unit. 
    //      - For timer interrupts, choose the internal clock source. 
    //      ? Note: By default, after power-on, the internal clock is already selected.
    //         This statement is optional.*/
    // TIM_InternalClockConfig(TIM2);
    /*
     * 2. Select the External Clock for the time base unit
        - Configure Timer Clock Source using External Clock Mode 2 (ECM2) 
            - External Clock Mode 2:
                - Clock source: ETRF as timer base unit's clock.
            - External Clock Mode 1:
                - Clock source: TRGI, occupies trigger input.
                - Timer base unit's clock.*/
    TIM_ETRClockMode2Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted, 0x0F);
    /* 
     * 3. Configure the time base unit. 
        - Struct configuration:
            a. PSC (Prescaler)
            b. ARR (Auto-reload Register)
            c. CNT (Counter)*/
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 10 - 1;  
    TIM_TimeBaseInitStructure.TIM_Prescaler = 0;/* EQUATION:
                                                            * CK_CNT_OV = CK_CNT / (ARR+1)
                                                            *           = CK_PSC / (PSC+1) / (ARR+1)
                                                            * Note: 
                                                            *  - CK_CNT_OV: This is the overflow period, 
                                                            *            which is the time interval between
                                                            *            consecutive timer overflows. 
                                                            *  - CK_CNT: This represents the timer's internal clock
                                                            *            frequency, which is the rate at which the timer 
                                                            *            counter increments.
                                                            *  - CK_PSC: This is the clock frequency after being divided 
                                                            *            by the prescaler value (PSC). 
                                                            *  - ARR: Auto-reload register value. Value set in TIM_Period.
                                                            *  - PSC: Prescaler value. 
                                                            */
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    /* 
        ? Clear the Flag ?
         >  cause <TIM_TimeBaseInit()> function will Generate an update event to reload 
            the Prescaler and the Repetition counter values immediately */
    TIM_ClearFlag(TIM2,TIM_IT_Update);
    
    /*
     * 4. Configure output interrupt control. 
        - Allow update interrupt to be output to NVIC.
    */
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); /* @arg TIM_IT_Update: TIM update Interrupt Source. */

    /* 
     * 5. Configure NVIC. 
        - Enable the timer interrupt channel in NVIC.
        - Assign priority.
    */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;/* Enable TIM2 in NVIC  */
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;/* Assign priority */
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);
    /* 
     * 6. Runtime control: Enable the timer. 
        - Enable the timer --> Counter starts working --> Counter update --> Trigger interrupt.
    */
    TIM_Cmd(TIM2,ENABLE);

} 

uint16_t TIMER_GetCounter(void)
{
    return TIM_GetCounter(TIM2);
}
/* 
     * 7. Write the timer interrupt function.
*/

void TIM2_IRQHandler(void)
{
    /*
     * a. Check the Interrupt Status
     */
    if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
    {
        display_nums ++;
     /*
     * b. Clear the Interrupt Status
     */
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    }

}