[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver PCA9548A

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/pca9548a/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

PCA9548A是一种通过I2C总线控制的八进制双向转换开关。SCL/SDA上行对扇出到八个下行对或信道。可以选择任何单个SCx/SDx信道或信道组合，由可编程控制寄存器的内容确定。激活的LOW复位输入允许PCA9548A从其中一条下游I2C总线卡在LOW状态的情况中恢复。拉动RESET引脚LOW（低）将重置I2C总线状态机，并导致取消选择所有通道，就像内部通电重置功能一样。开关的通过门的构造使得VDD引脚可以用于限制PCA9548A将通过的最大高压。这允许在每对上使用不同的总线电压，因此1.8 V或2.5 V或3.3 V部件可以与5 V部件通信，而无需任何附加保护。外部上拉电阻器将总线上拉到每个通道所需的电压水平。所有I/O引脚都具有6V的耐受性。

LibDriver PCA9548A是LibDriver推出的PCA9548A全功能驱动，该驱动提供I2C通道切换, I2C写入，I2C读取等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver PCA9548A的源文件。

/interface目录包含了LibDriver PCA9548A与平台无关的IIC总线模板。

/test目录包含了LibDriver PCA9548A驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver PCA9548A编程范例。

/doc目录包含了LibDriver PCA9548A离线文档。

/datasheet目录包含了PCA9548A数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的IIC总线模板，完成指定平台的IIC总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

#### example basic

```C
#include "driver_pca9548a_basic.h"

uint8_t res;
uint8_t i;
uint8_t buf[8];
uint8_t data = 0x00;
uint8_t dev_addr = 0x00;
uint16_t reg = 0x0000;
uint16_t len = 1;

/* basic init */
res = pca9548a_basic_init(PCA9548A_ADDRESS_A000);
if (res != 0)
{
    return 1;
}

...
    
/* set channel */
res = pca9548a_basic_set_channel(PCA9548A_CHANNEL_0, PCA9548A_BOOL_TRUE);
if (res != 0)
{
    (void)pca9548a_basic_deinit();

    return 1;
}

...
    
/* iic read command */
res = pca9548a_basic_iic_read_command(dev_addr, buf, len);
if (res != 0)
{
    (void)pca9548a_basic_deinit();

    return 1;
}
pca9548a_interface_debug_print("pca9548a: device address 0x%02X.\n", dev_addr);
pca9548a_interface_debug_print("pca9548a: data is ");
for (i = 0; i < len; i++)
{
    pca9548a_interface_debug_print("0x%02X ", buf[i]);
}
pca9548a_interface_debug_print("\n");

...

/* iic read */
res = pca9548a_basic_iic_read(dev_addr, reg & 0xFF, buf, len);
if (res != 0)
{
    (void)pca9548a_basic_deinit();

    return 1;
}
pca9548a_interface_debug_print("pca9548a: device address 0x%02X.\n", dev_addr);
pca9548a_interface_debug_print("pca9548a: register address 0x%02X.\n", reg);
pca9548a_interface_debug_print("pca9548a: data is ");
for (i = 0; i < len; i++)
{
    pca9548a_interface_debug_print("0x%02X ", buf[i]);
}
pca9548a_interface_debug_print("\n");    

...

/* iic read16 */
res = pca9548a_basic_iic_read_address16(dev_addr, reg, buf, len);
if (res != 0)
{
    (void)pca9548a_basic_deinit();

    return 1;
}
pca9548a_interface_debug_print("pca9548a: device address 0x%02X.\n", dev_addr);
pca9548a_interface_debug_print("pca9548a: register address 0x%04X.\n", reg);
pca9548a_interface_debug_print("pca9548a: data is ");
for (i = 0; i < len; i++)
{
    pca9548a_interface_debug_print("0x%02X ", buf[i]);
}
pca9548a_interface_debug_print("\n");  

...

/* iic write command */
res = pca9548a_basic_iic_write_command(dev_addr, &data, 1);
if (res != 0)
{
    (void)pca9548a_basic_deinit();

    return 1;
}
pca9548a_interface_debug_print("pca9548a: device address 0x%02X.\n", dev_addr);
pca9548a_interface_debug_print("pca9548a: data is 0x%02X\n", data); 

...

/* iic write */
res = pca9548a_basic_iic_write(dev_addr, reg & 0xFF, &data, 1);
if (res != 0)
{
    (void)pca9548a_basic_deinit();

    return 1;
}
pca9548a_interface_debug_print("pca9548a: device address 0x%02X.\n", dev_addr);
pca9548a_interface_debug_print("pca9548a: register address 0x%02X.\n", reg);
pca9548a_interface_debug_print("pca9548a: data is 0x%02X\n", data);    

...

/* iic write */
res = pca9548a_basic_iic_write_address16(dev_addr, reg, &data, 1);
if (res != 0)
{
    (void)pca9548a_basic_deinit();

    return 1;
}
pca9548a_interface_debug_print("pca9548a: device address 0x%02X.\n", dev_addr);
pca9548a_interface_debug_print("pca9548a: register address 0x%04X.\n", reg);
pca9548a_interface_debug_print("pca9548a: data is 0x%02X\n", data);  

...
    
/* basic deinit */
(void)pca9548a_basic_deinit();

return 0;
```

### 文档

在线文档: [https://www.libdriver.com/docs/pca9548a/index.html](https://www.libdriver.com/docs/pca9548a/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。