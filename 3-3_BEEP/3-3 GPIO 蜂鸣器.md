

# <span id="head1">3-3 GPIO 蜂鸣器</span>

本文档将演示如何使用STM32F10x系列微控制器配置GPIO引脚，以控制蜂鸣器发出声音。本文档将提供一个简单的代码示例，演示如何初始化GPIO引脚并生成不同延迟的蜂鸣声音效果。

## 目录

- [ 前提条件](#head2)
- [ 步骤](#head3)
  - [1. 主函数](#head4)
  - [2. GPIO 初始化](#head5)
  - [3. BEEP 蜂鸣模式](#head6)
- [ 总结](#head7)

## <span id="head2"> 前提条件</span>

- STM32F10x系列微控制器
- 开发环境：例如 Keil5、STM32CubeIDE
- 代码中所需的头文件：“stm32f10x.h”和“delay.h”（假定已包含在项目中）

## <span id="head3"> 步骤</span>
### <span id="head4">1. 主函数</span>
```C
int main(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // 使能GPIOB时钟
    // ...（其他代码）
}
```
主函数初始化用于控制GPIO引脚的GPIOB端口的时钟。

### <span id="head5">2. GPIO 初始化</span>

```C
GPIO_InitTypeDef GPIO_InitStructure; // 用于LED的GPIO结构体声明

GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出模式
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;       // 引脚12
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 速度50MHz

GPIO_Init(GPIOB, &GPIO_InitStructure); // 初始化GPIOB

```
此部分初始化端口 GPIOB 上的引脚 12 ，以推挽输出模式初始化，速度为50MHz。

### <span id="head6">3. BEEP 蜂鸣模式</span>
```C
while (1)
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_12); // 打开蜂鸣器
    Delay_ms(100);                      // 延迟100毫秒
    GPIO_SetBits(GPIOB, GPIO_Pin_12);   // 关闭蜂鸣器
    Delay_ms(100);                      // 延迟100毫秒
    // ...（使用不同的延迟重复上述模式）
}
```
此循环使用GPIO引脚12生成蜂鸣声模式。它会打开引脚，等待指定的延迟时间，然后关闭引脚并再次等待。该模式通过使用不同的延迟时间生成不同的声音效果。

## <span id="head7"> 总结</span>
所提供的代码片段配置了STM32F10x微控制器上的GPIO引脚，以生成蜂鸣声模式。通过在特定的延迟时间内切换引脚的状态，可以实现所需的声音效果。确保设置好项目环境，包含所需的头文件，并根据需要调整延迟时间以获得期望的声音效果。

请注意，本文档假设您具有基本的STM32微控制器编程和所提供的头文件的理解。请根据您的应用程序调整代码和延迟时间。如需详细信息，请参考STM32F10x参考手册和特定开发环境文档，以获取有关GPIO配置和函数的详细信息。