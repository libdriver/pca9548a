[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver PCA9548A

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/pca9548a/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

The PCA9548A is an octal bidirectional translating switch controlled via the I2C-bus. The SCL/SDA upstream pair fans out to eight downstream pairs, or channels. Any individual SCx/SDx channel or combination of channels can be selected, determined by the contents of the programmable control register. An active LOW reset input allows the PCA9548A to recover from a situation where one of the downstream I2C-buses is stuck in a LOW state. Pulling the RESET pin LOW resets the I2C-bus state machine and causes all the channels to be deselected as does the internal Power-on reset function. The pass gates of the switches are constructed such that the VDD pin can be used to limit the maximum high voltage which will be passed by the PCA9548A. This allows the use of different bus voltages on each pair, so that 1.8 V or 2.5 V or 3.3 V parts can communicate with 5 V parts without any additional protection. External pull-up resistors pull the bus up to the desired voltage level for each channel. All I/O pins are 6 V tolerant.

LibDriver PCA9548A is a full-featured driver for PCA9548A, launched by LibDriver.It provides I2C channel switching, I2C writing, I2C reading and additional features. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver PCA9548A source files.

/interface includes LibDriver PCA9548A IIC platform independent template.

/test includes LibDriver PCA9548A driver test code and this code can test the chip necessary function simply.

/example includes LibDriver PCA9548A sample code.

/doc includes LibDriver PCA9548A offline document.

/datasheet includes PCA9548A datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC platform independent template and finish your platform IIC driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

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

### Document

Online documents: [https://www.libdriver.com/docs/pca9548a/index.html](https://www.libdriver.com/docs/pca9548a/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.