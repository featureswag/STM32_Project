#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
    /*
        * 1. PWM Initialization Configuration:
          -* a. Configure RCC Clock (Enable).
          -* b. Enable TIM peripheral clock.
          -* c. Enable GPIO peripheral clock.*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    /* 
        * 2. Configure Timer Base Unit:
          -*  a. Clock source selection.
          -*  b. PSC Prescaler.
          -*  c. CNT Counter.
          -*  d. ARR Auto-reload.*/
    TIM_InternalClockConfig(TIM2);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;   /* ARR:
                                                        Resolution = 1 / (ARR+1) = 1%
                                                        ==> ARR = 100 - 1*/
    TIM_TimeBaseInitStructure.TIM_Prescaler = 720 - 1; /* PSC 
                                                        Frequency = CK_PSC/(PSC+1)/(ARR+1) = 1KHz
                                                                  = 72MHz /(PSC+1)/100 = 1000 Hz
                                                        ==> PSC = 720 - 1 */
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure); // Send Configuration.
     /* 
        * 3. Configure Output Compare Unit:
          -*  a. CCR Capture/Comparator.
                - Adjusting the value of CCR allows you to control the duty cycle,
                  thereby achieving the purpose of adjusting brightness. 
          -*  b. Output compare mode.
          -*  d. Output enable.*/
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure); /* Initialize the TIM_OCInitStructure 
                                               with default values.*/
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState =TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;      /* CCR Value:
                                             if Duty = CRR / (ARR+1) = 50 %
                                                ARR + 1 = 100
                                            ==> CRR = 0.5 * 100 = 50 */
    TIM_OC1Init(TIM2,&TIM_OCInitStructure);
     /* 
        * 4. Configure GPIO:
          -*  a. Configure PWM associated GPIO pins as alternate function push-pull output.
          -*  b. Refer to the specific pin definition table.*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
        /* 
            * Remap PA0 to PA15  */
        // RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
        // GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);    // Remap PA0 to PA15
        // GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE); // Disable JTAG on PA15
        // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;/* GPIO_Mode_AF_PP is a mode used to 
                                                       configure a GPIO pin as an alternate function output with push-pull configuration.  */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
     
     /* 
        * 5. Run control, enable the counter. 
    */
    TIM_Cmd(TIM2,ENABLE);
}

void PWM_SetCompare_1(uint16_t Compare_Value)
{
    TIM_SetCompare1(TIM2,Compare_Value);
}
