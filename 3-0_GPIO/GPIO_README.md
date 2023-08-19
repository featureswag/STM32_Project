- [ 工程示例：](#head1)
- [ 一、简介](#head2)
- [二、GPIO 基本结构](#head3)
- [三、GPIO 位结构](#head4)
	- [（一）I/O 口引脚部分](#head5)
	- [（二）驱动器部分 ](#head6)
		- [ 1.输入驱动器部分](#head7)
		- [ 2.输出驱动器部分](#head8)
- [三、GPIO 模式](#head9)
	- [ （一）浮空输入、上拉输入和下拉输入](#head10)
	- [ （二）模拟输入](#head11)
	- [（三）开漏输出和推挽输出 ](#head12)
	- [（四）输入输出模式切换 ](#head13)
	- [（五）复用开漏/推挽输出 ](#head14)
	- [（六）小结 ](#head15)

## <span id="head1"> 工程示例：</span>

- [3-0 GPIO 输出函数文档说明](https://github.com/featureswag/STM32/blob/eab4944109d75e50e5757f8d1d5ec52f0da130bc/3-0_GPIO_Function.md)
- [3-1 GPIO 控制 LED 闪烁](https://github.com/featureswag/STM32/blob/eab4944109d75e50e5757f8d1d5ec52f0da130bc/3-1_GPIO_LED_BLINK.md)
- [3-2 GPIO 控制 LED 循环](https://github.com/featureswag/STM32/blob/d6d11cbf375c42f35b9cb020399ad5abf0cb3cff/3-2_GPIO_LED_LOOP.md)
- [3-3 GPIO 控制蜂鸣器](https://github.com/featureswag/STM32/blob/b83a9cde03fb8942bdb0cd33091107a983759a92/3-3_GPIO_BEEP.md)

## <span id="head2"> 一、简介</span>

- GPIO （General Purpose Input Output）通用输入输出口 可配置为8种输入输出模式

- 引脚电平：0V～3.3V，部分引脚可容忍5V

- 输出模式下可控制端口输出高低电平，用以驱动LED、控制蜂鸣器、模拟通信协议输出时序等

- 输入模式下可读取端口的高低电平或电压，用于读取按键输入、外接模块电平信号输入、ADC电压采集、模拟通信协议接收数据等


## <span id="head3">二、GPIO 基本结构</span>
<br />
<br />
&emsp;&emsp;&emsp;  <img src="https://github.com/featureswag/STM32/assets/62315592/d0ae362c-efd3-4c68-9bf0-a4a7823af33f" width = "500px" height = "auto" >
<br />
<br />

- 每个 GPIO 模块，主要包含了寄存器和驱动器。
  
- 寄存器为特殊的存储器，Core 可以通过 APB2 总线对寄存器进行读写，从而实现完成输出电平和读取电平的功能。

    - 输出寄存器写 “1” --> 高电平
 
    - 输出寄存器写 “0” --> 低电平
 
    - 输入寄存器写 “1” --> 高电平
 
    - 输入寄存器写 “0” --> 低电平
 
- 驱动器则是增加 I/O 口的驱动能力的。

- STM32 为 32 bit 的单片机，因此所有的内部寄存器都为 32 位。但是端口只有 16 位，寄存器只有低 16 位对应的有端口。

## <span id="head4">三、GPIO 位结构</span>
<br />
<br />
&emsp;&emsp;&emsp; <img src="https://github.com/featureswag/STM32/assets/62315592/a7138f1e-1c7d-4f95-a27e-8b779a1b7cc0" width = "700px" height = "auto" >
<br />
<br />

GPIO 的位结构图如上图所示，分为三个部分：寄存器、驱动器（分为输入、输出）、I/O 引脚。 我们依次从右到左讲每个部分说明一下。

### <span id="head5">（一）I/O 口引脚部分</span>

当 I/O 口输入进电压时，回先经过两个保护二极管，目的是对输入电压进行限幅的，以防止电路烧坏。上方二极管接 VDD ：3.3V，下方二极管接 VSS ：0V。 

- 如果输入电压比 VDD（3.3V）还要高的时候，那么上方的二极管就会导通。

- 如果输入电压比 VSS（0V）还要低的时候（相对于 VSS 的电压），那么下方的二极管就会导通。

通过这种增加二极管限幅的方式，对内部电路进行保护，只有输入电压在 0V ~ 3.3V 之间的时候，两个二极管才不会导通，对电路没有影响。


### <span id="head6">（二）驱动器部分 </span>

#### <span id="head7"> 1.输入驱动器部分</span>

**输入保护电路**

在输入驱动器部分我们可以看到，通过二极管保护部分之后会来到上拉电阻 VDD 和下拉电阻 VSS 的部分。开关可通过程序进行配置。

- 上拉 VDD --> 导通 和 下拉 VSS --> 断开 ， **上拉输出模式**
    > 上拉模式相当于是默认高电平的输入模式。

- 上拉 VDD --> 断开 和 下拉 VSS --> 导通 ， **下拉输出模式**
    > 上拉模式相当于是默认高电平的输入模式。

- 上拉 VDD --> 导通 和 下拉 VSS --> 断开 ， **浮空输出模式**
    > 在浮空输入模式下，引脚的呼入电平极易受外界干扰而改变。

**TTL 施密特触发器**


接着我们可以看到经过上下拉电阻部分，会经过 **TTL 施密特触发器**，作用就是对输入电压进行整形。

- 如果输入电压大于某一阈值，输出就瞬间升为高电平。

- 如果输入电压小于某一阈值，输出就瞬间降为低电平。

因为施密特触发器（可以理解为迟滞比较器），使用了两个比较阈值进行判断，中间保留了一定的变化范围，可以有效避免因信号波动造成的输出抖动现象。


**端口输入数据寄存器 GPIOx_IDR**


经过施密特触发器的波形，可以直接存入**输入数据寄存器**中，再用程序进行读出输入寄存器对应某一位数据的操作，就可以知道 I/O 口输入电平了。


**片上外设**


图片左上有两路线路连接到片上外设的一些端口，在 TTL 施密特触发器前后分别引出的，

- 模拟输入（模拟量）：连接到 ADC 上，ADC 需要接收模拟量，所以线路接入至施密特触发器前。

- 复用功能输入（数字量）：连接到其他需要读取端口的外设上，如：串口的输入引脚等。复用功能输入接受的是数字量，所以线路接入至施密特触发器后。


#### <span id="head8"> 2.输出驱动器部分</span>

输出的数字部分，可以由**输出数据寄存器**或者**片上外设控制（复用功能输出）**。

**端口输出数据寄存器 GPIOx_ODR**

如果选择通过输出数据寄存器进行控制，相当于是普通的 I/O 口输出，写输出数据寄存器的某一位就可实现操作对应某个端口。输出数据寄存器同时控制 16 个端口，并且只能对寄存器整体读写，所以想控制其中某个端口，可以先读数寄存器数据，然后采用按位与、按位或的方式进行更改，把更改后的数据写回去。第二种方式见 位设置/清除寄存器 部分。

**端口位设置寄存器 GPIOx_BSRR 和 端口位清除寄存器  GPIOx_BRR**

在输出数据寄存器的左边还有个叫位设置/清除寄存器，这个可以用来单独操作输出数据寄存器的某一位，而不影响其他位。

- GPIOx_BSRR 寄存器：高十六位是位清除，低十六位位设置。
    > 通常我们用位设置时，采用 GPIOx_BSRR 寄存器（因为是低 16 位）。
    
- GPIOx_BRR 寄存器：低十六位位清除。
    > 通常我们用位清除时，采用 GPIOx_BRR 寄存器（因为是低 16 位）。

- 我们对某一位进行 置1 的操作的话，需要在位寄存器对应为写入 1。
    > 寄存器会自动讲输出数据寄存器对应位置置为 1，其他位保持原有数据。

- 我们对某一位进行 置0 的操作的话，需要在清除寄存器对应为写入 1。
    > 寄存器会自动讲输出数据寄存器对应位置清 0。

**扩展：位带操作**

除了上述的两种操作方式，STM32 还提供了第三种操作方式，就是读写 STM32 中的“位带”区域，这个位带的作用就跟51单片机的位寻址作用差不多。在STM32中，专门分配的有一段地址区域，这段地址映射了RAM和外设寄存器所有的位。读写这段地址中的数据，就相当于读写所映射位置的某一位。这就是位带的操作方式。


**输出控制**
输出控制的输入采用数据选择器来选择的通路（输出数据寄存器或者片上外设）。输出部分采用上面是 P—MOS，下面是 N—MOS 的组合结构。根据信号来控制开关的导通和关闭，开关负责将 IO 口接到 VDD 或者 VSS。

可以选择三种输出方式：推挽输出、开漏输出或者关闭。

**推挽输出模式**

在推挽输出模式下，P—MOS 和 N—MOS 均有效。

- 数据寄存器为1时，上管导通，下管断开，输出直接接到VDD，就是输出高电平。

- 数据寄存器为0时，上管断开，下管导通，输出直接接到VSS，就是输出低电平。

这种模式下，高低电平均有较强的驱动能力。所以推挽输出模式也可以叫**强推输出模式**。在推挽输出模式下，STM32 对 I0 口具有绝对的控制权，高低电平都由 STM32 说的算。

**开漏输出模式**
在开漏输出模式下，这个 P—MOS 是无效的，只有 N—MOS 在工作。

- 数据寄存器为 1 时，下管断开，这时输出相当于断开，也就是高阻模式。

- 数据寄存器为 0 时，下管导通，输出直接接到 VSS，也就是输出低电平。


在开漏输出模式下，只有低电平有驱动能力，高电平是没有驱动能力的。
   > 这个开漏模式可以作为通信协议的驱动方式。比如 I2C 通信的引脚，就是使用的开漏模式。在多机通信的情况下，这个模式可以避免各个设备的相互干扰。

   > 另外开漏模式还可以用于输出 5V 的电平信号，比如在 I0 口外接一个上拉电阻到 5V 的电源。
   > - 当输出低电平时，由内部的 N—MOS 直接接 VSS。
   > - 当输出高电平时，由外部的上拉电阻拉高至 5V，这样就可以输出5V的电平信号，用于兼容一些5V电平的设备。

**关闭模式**

这个是当引脚配置为输入模式的时候，这两个MOS管都无效，也就是输出关闭，端口的电平由外部信号来控制。


## <span id="head9">三、GPIO 模式</span>

通过配置GPIO的端口配置寄存器，端口可以配置成以下8种模式：

<br />
<br />
<table style="width:100%; text-align:center;">
  <tr>
    <th style="text-align:center">模式名称</th>
    <th style="text-align:center">性质</th>
    <th style="text-align:center">特征</th>
  </tr>
  <tr>
    <td style="text-align:center">浮空输入</td>
    <td style="text-align:center">数字输入</td>
    <td style="text-align:center">可读取引脚电平，若引脚悬空，则电平不确定</td>
  </tr>
  <tr>
    <td style="text-align:center">上拉输入</td>
    <td style="text-align:center">数字输入</td>
    <td style="text-align:center">可读取引脚电平，内部连接上拉电阻，悬空时默认高电平</td>
  </tr>
  <tr>
    <td style="text-align:center">下拉输入</td>
    <td style="text-align:center">数字输入</td>
    <td style="text-align:center">可读取引脚电平，内部连接下拉电阻，悬空时默认低电平</td>
  </tr>
  <tr>
    <td style="text-align:center">模拟输入</td>
    <td style="text-align:center">模拟输入</td>
    <td style="text-align:center">GPIO无效，引脚直接接入内部ADC</td>
  </tr>
  <tr>
    <td style="text-align:center">开漏输出</td>
    <td style="text-align:center">数字输出</td>
    <td style="text-align:center">可输出引脚电平，高电平为高阻态，低电平接VSS</td>
  </tr>
  <tr>
    <td style="text-align:center">推挽输出</td>
    <td style="text-align:center">数字输出</td>
    <td style="text-align:center">可输出引脚电平，高电平接VDD，低电平接VSS</td>
  </tr>
  <tr>
    <td style="text-align:center">复用开漏输出</td>
    <td style="text-align:center">数字输出</td>
    <td style="text-align:center">由片上外设控制，高电平为高阻态，低电平接VSS</td>
  </tr>
  <tr>
    <td style="text-align:center">复用推挽输出</td>
    <td style="text-align:center">数字输出</td>
    <td style="text-align:center">由片上外设控制，高电平接VDD，低电平接VSS</td>
  </tr>
</table>

### <span id="head10"> （一）浮空输入、上拉输入和下拉输入</span>

这三个模式的电路结构基本是一样的，区别就是上拉电阻和下拉电阻的连接。它们都属于数字的输入口，那特征就是，都可以读取端口的高低电平。

当引脚悬空时，上拉输入默认是高电平，下拉输入默认是低电平。而浮空输入的电平是不确定的，所以在使用浮空输入时端口一定要接上一个连续的驱动源，不能出现悬空的状态。

### <span id="head11"> （二）模拟输入</span>

- 此模式可以说是 ADC 模数转换器的专属配置模式。使用ADC时，将引脚配置为模拟输入模式，以进行信号采样。
  
- 模拟输入结构中，输出处于断开状态，施密特触发器也处于关闭状态，导致 GPIO 整个状态处于无效，仅剩模拟输入这一线路。
  
### <span id="head12">（三）开漏输出和推挽输出 </span>

推挽输出和开漏输出属于数字输出模式，可用于输出高低电平。

- 在推挽输出模式下，引脚具有驱动能力，可输出高低电平。
  > 当 P-MOS 和 N-MOS 同时有效。
  
- 在开漏输出模式下，高电平状态呈现高阻态，无驱动能力。
  > 当 P-MOS 无效，N-MOS 有效时，开漏输出会导致引脚连接到地。

### <span id="head13">（四）输入输出模式切换 </span>

- 在输出模式下，输入模式仍然有效。
  > 配置为输出模式时，内部可以顺带进行输入，不会产生影响。
  
- 输入模式下，输出无效。
  > 一个端口只能有一个输出，但可以有多个输入。

### <span id="head14">（五）复用开漏/推挽输出 </span>

复用输出模式类似于开漏输出和推挽输出。但此时输出数据寄存器处于断开状态，引脚的控制权转移到了片上外设。片上外设可以读取引脚的电平，同时普通输入也有效。

### <span id="head15">（六）小结 </span>

综上所述，我们可以总结一下。GPIO模式是通过配置端口配置寄存器实现的，共有8种模式：

<p style="margin-bottom: 10px;"><strong> &emsp;&emsp;1. 浮空输入、上拉输入和下拉输入</strong>：这三种模式都是数字输入，可读取引脚电平，悬空状态会有不同默认电平。</p>
<p style="margin-bottom: 10px;"><strong>&emsp;&emsp;2. 模拟输入</strong>：专用于ADC模数转换器，引脚直接连接内部ADC，输出断开。</p>
<p style="margin-bottom: 10px;"><strong>&emsp;&emsp;3. 推挽输出</strong>：数字输出，具备驱动能力，可以输出高低电平。</p>
<p style="margin-bottom: 10px;"><strong>&emsp;&emsp;4. 开漏输出</strong>：数字输出，高电平状态呈现高阻态，无驱动能力。</p>
<p style="margin-bottom: 10px;"><strong>&emsp;&emsp;5. 复用开漏/推挽输出</strong>：类似推挽/开漏输出，由片上外设控制，保留普通输入功能。</p>
<p style="margin-bottom: 10px;">&emsp;&emsp;GPIO 仅在模拟输入时，会关闭数字的输入功能，其他的 7 种模式中，所有的输入都是有效的。</p>

在不同模式之间切换时，一些功能仍然保持有效，如输出模式下的输入功能，或者输入模式下的输出失效。这些不同模式的配置可以适应不同的应用需求，实现GPIO的多功能操作。