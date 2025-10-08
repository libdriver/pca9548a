### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

GPIO Pin: RST PA8.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. PCA9548A

#### 3.1 Command Instruction

1. Show pca9548a chip and driver information.

   ```shell
   pca9548a (-i | --information)
   ```

2. Show pca9548a help.

   ```shell
   pca9548a (-h | --help)
   ```

3. Show pca9548a pin connections of the current board.

   ```shell
   pca9548a (-p | --port)
   ```

4. Run pca9548a register test.

   ```shell
   pca9548a (-t reg | --test=reg) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]
   ```

5. Run pca9548a read command function, hex is the device address in hex format, len is the read length.

   ```shell
   pca9548a (-e read-command | --example=read-command) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--channel=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--dev-addr=<hex>] [--length=<len>]
   ```

6. Run pca9548a read function, dev-addr hex is the device address in hex format, reg hex is the register address in hex format, len is the read length.

   ```shell
   pca9548a (-e read | --example=read) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--channel=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--dev-addr=<hex>] [--reg=<hex>] [--length=<len>]
   ```

7. Run pca9548a read16 function, dev-addr hex is the device address in hex format, reg hex is the register address in hex format, len is the read length.

   ```shell
   pca9548a (-e read16 | --example=read16) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--channel=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--dev-addr=<hex>] [--reg=<hex>] [--length=<len>]
   ```
   
8. Run pca9548a write command function, dev-addr hex is the device address in hex format, data hex is the set data in hex format.

   ```shell
   pca9548a (-e write-command | --example=write-command) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--channel=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--dev-addr=<hex>] [--data=<hex>]
   ```
   
9. Run pca9548a write function, dev-addr hex is the device address in hex format, reg hex is the register address in hex format, data hex is the set data in hex format.

   ```shell
   pca9548a (-e write | --example=write) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--channel=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--dev-addr=<hex>] [--reg=<hex>] [--data=<hex>]
   ```

10. Run pca9548a write16 function, dev-addr hex is the device address in hex format, reg hex is the register address in hex format, data hex is the set data in hex format.

    ```shell
      pca9548a (-e write16 | --example=write16) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--channel=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--dev-addr=<hex>] [--reg=<hex>] [--data=<hex>]
    ```

#### 3.2 Command Example

```shell
pca9548a -i

pca9548a: chip is NXP PCA9548A.
pca9548a: manufacturer is NXP.
pca9548a: interface is IIC.
pca9548a: driver version is 1.0.
pca9548a: min supply voltage is 2.3V.
pca9548a: max supply voltage is 5.5V.
pca9548a: max current is 100.00mA.
pca9548a: max temperature is 85.0C.
pca9548a: min temperature is -40.0C.
```

```shell
pca9548a -p

pca9548a: SCL connected to GPIOB PIN8.
pca9548a: SDA connected to GPIOB PIN9.
pca9548a: RST connected to GPIOA PIN8.
```

```shell
pca9548a -t reg --addr=0

pca9548a: chip is NXP PCA9548A.
pca9548a: manufacturer is NXP.
pca9548a: interface is IIC.
pca9548a: driver version is 1.0.
pca9548a: min supply voltage is 2.3V.
pca9548a: max supply voltage is 5.5V.
pca9548a: max current is 100.00mA.
pca9548a: max temperature is 85.0C.
pca9548a: min temperature is -40.0C.
pca9548a: start register test.
pca9548a: pca9548a_set_channel/pca9548a_get_channel test.
pca9548a: enable channel 0.
pca9548a: check channel ok.
pca9548a: disable channel 0.
pca9548a: check channel ok.
pca9548a: enable channel 1.
pca9548a: check channel ok.
pca9548a: disable channel 1.
pca9548a: check channel ok.
pca9548a: enable channel 2.
pca9548a: check channel ok.
pca9548a: disable channel 2.
pca9548a: check channel ok.
pca9548a: enable channel 3.
pca9548a: check channel ok.
pca9548a: disable channel 3.
pca9548a: check channel ok.
pca9548a: enable channel 4.
pca9548a: check channel ok.
pca9548a: disable channel 4.
pca9548a: check channel ok.
pca9548a: enable channel 5.
pca9548a: check channel ok.
pca9548a: disable channel 5.
pca9548a: check channel ok.
pca9548a: enable channel 6.
pca9548a: check channel ok.
pca9548a: disable channel 6.
pca9548a: check channel ok.
pca9548a: enable channel 7.
pca9548a: check channel ok.
pca9548a: disable channel 7.
pca9548a: check channel ok.
pca9548a: pca9548a_reset_bus test.
pca9548a: check reset bus ok.
pca9548a: finish register test.
```

```shell
pca9548a -e read-command --addr=0 --channel=0 --dev-addr=0xA0 --length=1

pca9548a: device address 0xA0.
pca9548a: register address 0x00.
pca9548a: data is 0x01 
```

```shell
pca9548a -e read --addr=0 --channel=0 --dev-addr=0xA0 --reg=0x00 --length=1

pca9548a: device address 0xA0.
pca9548a: register address 0x00.
pca9548a: data is 0xC6 
```

```shell
pca9548a -e read16 --addr=0 --channel=0 --dev-addr=0xA0 --reg=0x0000 --length=1

pca9548a: device address 0xA0.
pca9548a: register address 0x0000.
pca9548a: data is 0xC6 
```

```shell
pca9548a -e write-command --addr=0 --channel=0 --dev-addr=0xA0 --data=0x01

pca9548a: device address 0xA0.
pca9548a: data is 0x01
```

```shell
pca9548a -e write --addr=0 --channel=0 --dev-addr=0xA0 --reg=0x00 --data=0x01

pca9548a: device address 0xA0.
pca9548a: register address 0x00.
pca9548a: data is 0x01
```

```shell
pca9548a -e write16 --addr=0 --channel=0 --dev-addr=0xA0 --reg=0x0000 --data=0x01

pca9548a: device address 0xA0.
pca9548a: register address 0x0000.
pca9548a: data is 0x01
```

```shell
pca9548a -h

Usage:
  pca9548a (-i | --information)
  pca9548a (-h | --help)
  pca9548a (-p | --port)
  pca9548a (-t reg | --test=reg) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]
  pca9548a (-e read-command | --example=read-command) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--channel=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]
           [--dev-addr=<hex>] [--length=<len>]
  pca9548a (-e read | --example=read) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--channel=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]
           [--dev-addr=<hex>] [--reg=<hex>] [--length=<len>]
  pca9548a (-e read16 | --example=read16) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--channel=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]
           [--dev-addr=<hex>] [--reg=<hex>] [--length=<len>]
  pca9548a (-e write-command | --example=write-command) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--channel=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]
           [--dev-addr=<hex>] [--data=<hex>]
  pca9548a (-e write | --example=write) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--channel=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]
           [--dev-addr=<hex>] [--reg=<hex>] [--data=<hex>]
  pca9548a (-e write16 | --example=write16) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--channel=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]
           [--dev-addr=<hex>] [--reg=<hex>] [--data=<hex>]

Options:
      --addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>
                              Set the addr pin.([default: 0])
      --channel=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>
                              Set the chip channel.([default: 0])
      --data=<hex>            Set the data in hex format.([default: 0x00])
      --dev-addr=<hex>        Set the device address in hex format.([default: 0x00])
  -e <read-command | read | read16 | write-command | write | write16>,
      --example=<read-command | read | read16 | write-command | write | write16>
                              Run the driver example.
  -h, --help                  Show the help.
  -i, --information           Show the chip information.
      --reg=<hex>             Set the register address in hex format.([default: 0x00])
      --length=<len>          Set the length of data to be read.([default: 1])
  -p, --port                  Display the pin connections of the current board.
  -t <reg>, --test=<reg>      Run the driver test.
```
