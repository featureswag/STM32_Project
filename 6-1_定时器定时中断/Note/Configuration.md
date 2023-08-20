用英文整理 ，以C语言注释 /* 1. */的形式返回。  

1. 配置RCC。
   - 开启内部时钟，打开后定时器基准时钟和整个外设工作时钟会同时打开。
2. 选择时基单元的时钟源。
   - 对于定时器中断，选择内部时钟源。
3. 配置时基单元。
   - 结构体配置：PSC（预分频器）、ARR（自动重装器）、CNT（计数模式）
4. 配置输出中断控制。
   - 允许更新中断输出到NVIC。
5. 配置NVIC。
   - 在NVIC中打开定时中断的通道。
   - 分配优先级。
6. 运行控制-：使能定时器。
   - 使能定时器 --> 计数器开始工作 --> 计数器更新 --> 触发中断。
7. 写定时器中断函数。


```C
/* 
 * 1. Configure RCC. 
 */
// Enable the internal clock, enabling this will also turn on the timer's base clock and the entire peripheral clock.
 
/* 2. Select the clock source for the time base unit. */
// For timer interrupts, choose the internal clock source.
void TIM_InternalClockConfig(TIM_TypeDef* TIMx);

void TIM_ITRxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource);

void TIM_TIxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_TIxExternalCLKSource, uint16_t TIM_ICPolarity, uint16_t ICFilter);

void TIM_ETRClockMode1Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,uint16_t ExtTRGFilter);

void TIM_ETRClockMode2Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter);

void TIM_ETRConfig(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter);

/* 3. Configure the time base unit. */
// Struct configuration: PSC (Prescaler), ARR (Auto-reload Register), CNT (Counter)
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct); 

/* 4. Configure output interrupt control. */
// Allow update interrupt to be output to NVIC.
void TIM_ITConfig(TIM_TypeDef* TIMx, uint16_t TIM_IT, FunctionalState NewState);

/* 5. Configure NVIC. */
// Enable the timer interrupt channel in NVIC.
// Assign priority.
 
/* 6. Runtime control: Enable the timer. */
// Enable the timer --> Counter starts working --> Counter update --> Trigger interrupt.
 void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);

/* 7. Write the timer interrupt function. */

```

Precaler
```C
/* This function is to revise precaler */
/**
  * @brief  Configures the TIMx Prescaler.
  * @param  TIMx: where x can be 1 to 17 to select the TIM peripheral.
  * @param  Prescaler: specifies the Prescaler Register value
  * @param  TIM_PSCReloadMode: specifies the TIM Prescaler Reload mode
  *   This parameter can be one of the following values:
  *     @arg TIM_PSCReloadMode_Update: The Prescaler is loaded at the update event.
  *     @arg TIM_PSCReloadMode_Immediate: The Prescaler is loaded immediately.
  * @retval None
  */
void TIM_PrescalerConfig(TIM_TypeDef* TIMx, uint16_t Prescaler, uint16_t TIM_PSCReloadMode);

```
Counter
```C
/**
  * @brief  Specifies the TIMx Counter Mode to be used.
  * @param  TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  TIM_CounterMode: specifies the Counter Mode to be used
  *   This parameter can be one of the following values:
  *     @arg TIM_CounterMode_Up: TIM Up Counting Mode
  *     @arg TIM_CounterMode_Down: TIM Down Counting Mode
  *     @arg TIM_CounterMode_CenterAligned1: TIM Center Aligned Mode1
  *     @arg TIM_CounterMode_CenterAligned2: TIM Center Aligned Mode2
  *     @arg TIM_CounterMode_CenterAligned3: TIM Center Aligned Mode3
  * @retval None
  */
void TIM_CounterModeConfig(TIM_TypeDef* TIMx, uint16_t TIM_CounterMode);
```
