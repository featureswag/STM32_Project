
# <span id="head1">3-2 GPIO 控制 LED 循环</span>

本文档将详细解释如何在STM32单片机上配置GPIO引脚，以实现LED警灯循环闪烁效果，并展示了一些扩展功能。我们将分步介绍主函数、GPIO初始化以及生成LED闪烁模式的过程。

## <span id="head2"> 目录</span>

- [ 目录](#head2)
- [ 前提条件](#head3)
- [ 步骤](#head4)
  - [1. 主函数](#head5)
  - [ 2. 初始化GPIO引脚](#head6)
  - [3. 生成LED循环闪烁模式](#head7)
  - [4. 扩展：LED警灯闪烁](#head8)
- [ 总结](#head9)


## <span id="head3"> 前提条件</span>

- STM32系列单片机
- 开发环境：例如STM32CubeIDE
- 代码中所需的头文件：“stm32f10x.h”和“delay.h”（假定已包含在项目中）

## <span id="head4"> 步骤</span>

### <span id="head5">1. 主函数</span>

```c
int main(void)
{
    // ...（以下为后续步骤）
}
```

主函数是代码的入口点。在该函数中，我们将执行以下操作来实现LED警灯循环闪烁效果以及扩展功能。

### <span id="head6"> 2. 初始化GPIO引脚</span>

```C
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

GPIO_InitTypeDef GPIO_InitStructure;

GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOA, &GPIO_InitStructure);
```

在这一步中，我们会启用GPIOA的时钟，并使用 `GPIO_InitTypeDef` 结构体对GPIO引脚进行初始化。我们将引脚设置为推挽输出模式，选择所有引脚（使用GPIO_Pin_All），速度为50MHz。

### <span id="head7">3. 生成LED循环闪烁模式</span>

```
while (1)
{
    GPIO_Write(GPIOA,~0x0001); // 0000 0000 0000 0001
    Delay_ms(500);
    // ...（以下为其他LED循环闪烁模式，您可以根据需要扩展或自定义）
}
```

### <span id="head8">4. 扩展：LED警灯闪烁</span>

如果您想要添加其他LED警灯闪烁的模式，您可以参考扩展部分的示例代码，并根据需要进行自定义修改。

```c
u16 i;
// 0005 --> 红灯1、3同时闪烁
GPIO_Write(GPIOA,~0x0005); // 0000 0000 0000 0101
Delay_ms(300);
for(i=0; i<=4;i++){
    GPIO_Write(GPIOA,~0x0005); // 0000 0000 0000 0101
    Delay_ms(200);
    GPIO_Write(GPIOA,~0x0000); // 0000 0000 0000 0000
    Delay_ms(50);
}

// 0005 --> 蓝灯2、4同时闪烁
GPIO_Write(GPIOA,~0x000A); // 0000 0000 0000 1010
Delay_ms(300);
for(i=0; i<=4;i++){
    GPIO_Write(GPIOA,~0x000A); // 0000 0000 0000 0101
    Delay_ms(200);
    GPIO_Write(GPIOA,~0x0000); // 0000 0000 0000 0000
    Delay_ms(50);
}

// 000F --> 红灯蓝灯同时闪烁
for(i=0; i<=5;i++){
    GPIO_Write(GPIOA,~0x000F); // 0000 0000 0000 1111
    Delay_ms(100);
    GPIO_Write(GPIOA,~0x0000); // 0000 0000 0000 1111
    Delay_ms(200);
}
```



## <span id="head9"> 总结</span>

本文档详细解释了如何在STM32单片机上配置GPIO引脚，以实现LED警灯的循环闪烁效果。我们分步介绍了主函数、GPIO初始化以及生成LED闪烁模式的过程。同时，我们也提供了一个示例代码，您可以根据需要添加其他LED循环闪烁模式或扩展功能。

确保您熟悉STM32单片机编程基础，并根据您的项目环境和需求进行相应的调整。如需更多详细信息，请参考您所使用的STM32单片机型号的参考手册以及开发环境的文档，以获取有关GPIO配置和函数的详细信息。