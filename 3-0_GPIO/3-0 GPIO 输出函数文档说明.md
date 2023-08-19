

# <span id="head1">3-0 GPIO 输出函数文档说明</span>
本文档提供了关于使用STM32的GPIO模块进行输出操作的函数说明。这些函数可以用于控制单片机上的GPIO引脚，实现输出高电平或低电平。

## 目录
- [GPIOMode_TypeDef （GPIO模式与模式名称对照表）](#head2)
- [ 函数列表](#head3)
	- [`GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)`](#head4)
	- [`GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)`](#head5)
	- [`GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal)`](#head6)
- [ 结构体和函数](#head7)
	- [ `GPIO_InitTypeDef`](#head8)
	- [`RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)`](#head9)
	- [`GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)`](#head10)
- [ 使用示例](#head11)

## <span id="head2">GPIOMode_TypeDef （GPIO模式与模式名称对照表）</span>


| 模式值                | 模式名称     | Mode Name                            |
| --------------------- | ------------ | ------------------------------------ |
| GPIO_Mode_AIN         | 模拟输入     | Analog Input                         |
| GPIO_Mode_IN_FLOATING | 浮空输入     | Floating Input                       |
| GPIO_Mode_IPD         | 下拉输入     | Pull-Down Input                      |
| GPIO_Mode_IPU         | 上拉输入     | Pull-Up Input                        |
| GPIO_Mode_Out_OD      | 开漏输出     | Open-Drain Output                    |
| GPIO_Mode_Out_PP      | 推挽输出     | Push-Pull Output                     |
| GPIO_Mode_AF_OD       | 复用开漏输出 | Alternate Function Open-Drain Output |
| GPIO_Mode_AF_PP       | 复用推挽输出 | Alternate Function Push-Pull Output  |



## <span id="head3"> 函数列表</span>

#### <span id="head4">`GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)`</span>

- **简要说明：** 将指定的GPIO引脚置为低电平状态。
- **参数：**
  - `GPIOx`：要操作的GPIO端口，如 `GPIOA`、`GPIOB` 等。
  - `GPIO_Pin`：要置为低电平的引脚，可以是单个引脚或按位或的多个引脚。
- **返回值：** 无。

#### <span id="head5">`GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)`</span>

- **简要说明：** 将指定的GPIO引脚置为高电平状态。
- **参数：**
  - `GPIOx`：要操作的GPIO端口，如 `GPIOA`、`GPIOB` 等。
  - `GPIO_Pin`：要置为高电平的引脚，可以是单个引脚或按位或的多个引脚。
- **返回值：** 无。

#### <span id="head6">`GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal)`</span>

- **简要说明：** 将指定的GPIO引脚设置为特定的电平。
- **参数：**
  - `GPIOx`：要操作的GPIO端口，如 `GPIOA`、`GPIOB` 等。
  - `GPIO_Pin`：要操作的引脚，可以是单个引脚。
  - `BitVal`：要设置的电平，可以是 `Bit_RESET`（低电平）或 `Bit_SET`（高电平）。
- **返回值：** 无。

## <span id="head7"> 结构体和函数</span>

#### <span id="head8"> `GPIO_InitTypeDef`</span>

- **简要说明：** 用于配置GPIO引脚的结构体。
- **成员：**
  - `GPIO_Mode`：GPIO引脚的工作模式，可以是 `GPIO_Mode_IN`（输入）或 `GPIO_Mode_Out_PP`（输出推挽）等。
  - `GPIO_Pin`：要配置的GPIO引脚，可以是单个引脚或按位或的多个引脚。
  - `GPIO_Speed`：GPIO引脚的输出速度，可以是 `GPIO_Speed_10MHz`、`GPIO_Speed_50MHz` 等。

#### <span id="head9">`RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)`</span>

- **简要说明：** 使能或禁用APB2总线上的外设时钟。
- **参数：**
  - `RCC_APB2Periph`：要控制的外设时钟，如 `RCC_APB2Periph_GPIOA`、`RCC_APB2Periph_GPIOB` 等。
  - `NewState`：指示外设时钟状态，可以是 `ENABLE`（使能）或 `DISABLE`（禁用）。
- **返回值：** 无。

#### <span id="head10">`GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)`</span>

- **简要说明：** 初始化指定GPIO端口的引脚。
- **参数：**
  - `GPIOx`：要初始化的GPIO端口，如 `GPIOA`、`GPIOB` 等。
  - `GPIO_InitStruct`：包含引脚配置信息的结构体指针。
- **返回值：** 无。


## <span id="head11"> 使用示例</span>

以下是一个示例代码，演示了如何使用上述函数控制GPIO引脚的输出状态：

```c
#include "stm32f10x.h" // 设备头文件
#include "delay.h"

int main(void)
{
    // 使能GPIOA时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // 初始化GPIO引脚
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    while (1)
    {
        // 置为低电平，LED亮
        GPIO_ResetBits(GPIOA, GPIO_Pin_0);
        Delay_ms(500);

        // 置为高电平，LED灭
        GPIO_SetBits(GPIOA, GPIO_Pin_0);
        Delay_ms(500);

        // 设置特定电平，LED亮
        GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
        Delay_ms(500);

        // 设置特定电平，LED灭
        GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
        Delay_ms(500);
    }
}