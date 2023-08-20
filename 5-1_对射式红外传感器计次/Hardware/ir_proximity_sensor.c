#include "stm32f10x.h"                  // Device header


/*
Configure the IR proximity sensor as an external interrupt source.(English Version)
    Step 1: Configure RCC (Reset and Clock Control). Initialize the sensor by enabling the clock for the peripheral.
    Step 2: Configure GPIO (General Purpose Input/Output). Choose the input mode for the selected port.
    Step 3: Configure AFIO (Alternate Function I/O). Select the corresponding GPIO pin and connect it to the EXTI (External Interrupt/Event) line.
    Step 4: Configure EXTI (External Interrupt/Event).
        - Choose the edge-triggering mode, for example: rising edge, falling edge, or both edges.
        - Choose the triggering response, for example: interrupt response or event response. (Usually, interrupt response is selected.)
    Step 5: Configure NVIC (Nested Vectored Interrupt Controller). Assign a suitable priority to the interrupt. The interrupt enters the CPU through NVIC.

Configure the IR proximity sensor as an external interrupt source.(Chinese Version)
    第一步：配置RCC（复位和时钟控制）。通过使能外设时钟来初始化传感器。
    第二步：配置GPIO（通用输入/输出）。选择所选端口的输入模式。
    第三步：配置AFIO（备用功能I/O）。选择相应的GPIO引脚并将其连接到EXTI（外部中断/事件）线。
    第四步：配置EXTI（外部中断/事件）。
        - 选择边沿触发模式，例如：上升沿、下降沿或两个边沿。
        - 选择触发响应，例如：中断响应或事件响应。（通常选择中断响应。）
    第五步：配置NVIC（嵌套向量中断控制器）。为中断分配合适的优先级。中断通过NVIC进入CPU。
*/
uint16_t IR_Count;				// define a variable to count the number of times the sensor is triggered

void IR_ProximitySensor_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,  ENABLE);
	
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line    = EXTI_Line14;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel    =  EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd =  ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
}

uint16_t IR_ProximitySensor_GetCount(void)
{
    return IR_Count;
}
void EXTI15_10_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line14) == SET)
    {
		IR_Count ++;                    // count the number of times the sensor is triggered
        if(IR_Count > 9999) IR_Count = 0; // reset the counter when it reaches 9999
        EXTI_ClearITPendingBit(EXTI_Line14);
    }
}
