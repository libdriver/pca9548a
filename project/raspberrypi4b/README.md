### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

GPIO Pin: RST GPIO17.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(pca9548a REQUIRED)
```

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
./pca9548a -i

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
./pca9548a -p

pca9548a: SCL connected to GPIO3(BCM).
pca9548a: SDA connected to GPIO2(BCM).
pca9548a: RST connected to GPIO17(BCM).
```

```shell
./pca9548a -t reg --addr=0

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
./pca9548a -e read-command --addr=0 --channel=0 --dev-addr=0x00 --length=1

pca9548a: device address 0xA0.
pca9548a: register address 0x00.
pca9548a: data is 0x01 
```

```shell
./pca9548a -e read --addr=0 --channel=0 --dev-addr=0x00 --reg=0x00 --length=1

pca9548a: device address 0xA0.
pca9548a: register address 0x00.
pca9548a: data is 0xC6
```

```shell
./pca9548a -e read16 --addr=0 --channel=0 --dev-addr=0x00 --reg=0x0000 --length=1

pca9548a: device address 0xA0.
pca9548a: register address 0x0000.
pca9548a: data is 0xC6 
```

```shell
./pca9548a -e write-command --addr=0 --channel=0 --dev-addr=0x00 --data=0x01

pca9548a: device address 0xA0.
pca9548a: data is 0x01
```

```shell
./pca9548a -e write --addr=0 --channel=0 --dev-addr=0x00 --reg=0x00 --data=0x01

pca9548a: device address 0xA0.
pca9548a: register address 0x00.
pca9548a: data is 0x01
```

```shell
./pca9548a -e write16 --addr=0 --channel=0 --dev-addr=0x00 --reg=0x0000 --data=0x01

pca9548a: device address 0xA0.
pca9548a: register address 0x0000.
pca9548a: data is 0x01
```

```shell
./pca9548a -h

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
