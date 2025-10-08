/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2025-10-15
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2025/10/15  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_pca9548a_register_test.h"
#include "driver_pca9548a_basic.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include "getopt.h"
#include <stdlib.h>
#include <math.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
volatile uint16_t g_len;   /**< uart buffer length */

/**
 * @brief     pca9548a full function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t pca9548a(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"addr", required_argument, NULL, 1},
        {"channel", required_argument, NULL, 2},
        {"data", required_argument, NULL, 3},
        {"dev-addr", required_argument, NULL, 4},
        {"reg", required_argument, NULL, 5},
        {"length", required_argument, NULL, 6},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    pca9548a_address_t addr = PCA9548A_ADDRESS_A000;
    pca9548a_channel_t channel = PCA9548A_CHANNEL_0;
    uint8_t data = 0x00;
    uint8_t dev_addr = 0x00;
    uint16_t reg = 0x0000;
    uint16_t len = 1;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* addr */
            case 1 :
            {
                /* set the addr pin */
                if (strcmp("0", optarg) == 0)
                {
                    addr = PCA9548A_ADDRESS_A000;
                }
                else if (strcmp("1", optarg) == 0)
                {
                    addr = PCA9548A_ADDRESS_A001;
                }
                else if (strcmp("2", optarg) == 0)
                {
                    addr = PCA9548A_ADDRESS_A010;
                }
                else if (strcmp("3", optarg) == 0)
                {
                    addr = PCA9548A_ADDRESS_A011;
                }
                else if (strcmp("4", optarg) == 0)
                {
                    addr = PCA9548A_ADDRESS_A100;
                }
                else if (strcmp("5", optarg) == 0)
                {
                    addr = PCA9548A_ADDRESS_A101;
                }
                else if (strcmp("6", optarg) == 0)
                {
                    addr = PCA9548A_ADDRESS_A110;
                }
                else if (strcmp("7", optarg) == 0)
                {
                    addr = PCA9548A_ADDRESS_A111;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* channel */
            case 2 :
            {
                /* set the pin */
                if (strcmp("0", optarg) == 0)
                {
                    channel = PCA9548A_CHANNEL_0;
                }
                else if (strcmp("1", optarg) == 0)
                {
                    channel = PCA9548A_CHANNEL_1;
                }
                else if (strcmp("2", optarg) == 0)
                {
                    channel = PCA9548A_CHANNEL_2;
                }
                else if (strcmp("3", optarg) == 0)
                {
                    channel = PCA9548A_CHANNEL_3;
                }
                else if (strcmp("4", optarg) == 0)
                {
                    channel = PCA9548A_CHANNEL_4;
                }
                else if (strcmp("5", optarg) == 0)
                {
                    channel = PCA9548A_CHANNEL_5;
                }
                else if (strcmp("6", optarg) == 0)
                {
                    channel = PCA9548A_CHANNEL_6;
                }
                else if (strcmp("7", optarg) == 0)
                {
                    channel = PCA9548A_CHANNEL_7;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* data */
            case 3 :
            {
                char *p;
                uint16_t l;
                uint16_t i;
                uint64_t hex_data;

                /* set the data */
                l = (uint16_t)strlen(optarg);

                /* check the header */
                if (l >= 2)
                {
                    if (strncmp(optarg, "0x", 2) == 0)
                    {
                        p = optarg + 2;
                        l -= 2;
                    }
                    else if (strncmp(optarg, "0X", 2) == 0)
                    {
                        p = optarg + 2;
                        l -= 2;
                    }
                    else
                    {
                        p = optarg;
                    }
                }
                else
                {
                    p = optarg;
                }
                
                /* init 0 */
                hex_data = 0;

                /* loop */
                for (i = 0; i < l; i++)
                {
                    if ((p[i] <= '9') && (p[i] >= '0'))
                    {
                        hex_data += (p[i] - '0') * (uint32_t)pow(16, l - i - 1);
                    }
                    else if ((p[i] <= 'F') && (p[i] >= 'A'))
                    {
                        hex_data += ((p[i] - 'A') + 10) * (uint32_t)pow(16, l - i - 1);
                    }
                    else if ((p[i] <= 'f') && (p[i] >= 'a'))
                    {
                        hex_data += ((p[i] - 'a') + 10) * (uint32_t)pow(16, l - i - 1);
                    }
                    else
                    {
                        return 5;
                    }
                }
                
                /* set the data */
                data = hex_data & 0xFF;
                
                break;
            }
            
            /* dev-addr */
            case 4 :
            {
                char *p;
                uint16_t l;
                uint16_t i;
                uint64_t hex_data;

                /* set the data */
                l = (uint16_t)strlen(optarg);

                /* check the header */
                if (l >= 2)
                {
                    if (strncmp(optarg, "0x", 2) == 0)
                    {
                        p = optarg + 2;
                        l -= 2;
                    }
                    else if (strncmp(optarg, "0X", 2) == 0)
                    {
                        p = optarg + 2;
                        l -= 2;
                    }
                    else
                    {
                        p = optarg;
                    }
                }
                else
                {
                    p = optarg;
                }
                
                /* init 0 */
                hex_data = 0;

                /* loop */
                for (i = 0; i < l; i++)
                {
                    if ((p[i] <= '9') && (p[i] >= '0'))
                    {
                        hex_data += (p[i] - '0') * (uint32_t)pow(16, l - i - 1);
                    }
                    else if ((p[i] <= 'F') && (p[i] >= 'A'))
                    {
                        hex_data += ((p[i] - 'A') + 10) * (uint32_t)pow(16, l - i - 1);
                    }
                    else if ((p[i] <= 'f') && (p[i] >= 'a'))
                    {
                        hex_data += ((p[i] - 'a') + 10) * (uint32_t)pow(16, l - i - 1);
                    }
                    else
                    {
                        return 5;
                    }
                }
                
                /* set the data */
                dev_addr = hex_data & 0xFF;
                
                break;
            } 
            
            /* reg */
            case 5 :
            {
                char *p;
                uint16_t l;
                uint16_t i;
                uint64_t hex_data;

                /* set the data */
                l = (uint16_t)strlen(optarg);

                /* check the header */
                if (l >= 2)
                {
                    if (strncmp(optarg, "0x", 2) == 0)
                    {
                        p = optarg + 2;
                        l -= 2;
                    }
                    else if (strncmp(optarg, "0X", 2) == 0)
                    {
                        p = optarg + 2;
                        l -= 2;
                    }
                    else
                    {
                        p = optarg;
                    }
                }
                else
                {
                    p = optarg;
                }
                
                /* init 0 */
                hex_data = 0;

                /* loop */
                for (i = 0; i < l; i++)
                {
                    if ((p[i] <= '9') && (p[i] >= '0'))
                    {
                        hex_data += (p[i] - '0') * (uint32_t)pow(16, l - i - 1);
                    }
                    else if ((p[i] <= 'F') && (p[i] >= 'A'))
                    {
                        hex_data += ((p[i] - 'A') + 10) * (uint32_t)pow(16, l - i - 1);
                    }
                    else if ((p[i] <= 'f') && (p[i] >= 'a'))
                    {
                        hex_data += ((p[i] - 'a') + 10) * (uint32_t)pow(16, l - i - 1);
                    }
                    else
                    {
                        return 5;
                    }
                }
                
                /* set the data */
                reg = hex_data & 0xFFFF;
                
                break;
            } 
            
            /* length */
            case 6 :
            {
                len = (uint16_t)atol(optarg);
                if (len > 8)
                {
                    pca9548a_interface_debug_print("pca9548a: len > 8.\n");
                }
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_reg", type) == 0)
    {
        uint8_t res;
        
        /* run test */
        res = pca9548a_register_test(addr);
        if (res != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_read-command", type) == 0)
    {
        uint8_t res;
        uint8_t i;
        uint8_t buf[8];
        
        /* basic init */
        res = pca9548a_basic_init(addr);
        if (res != 0)
        {
            return 1;
        }
        
        /* set channel */
        res = pca9548a_basic_set_channel(channel, PCA9548A_BOOL_TRUE);
        if (res != 0)
        {
            (void)pca9548a_basic_deinit();
            
            return 1;
        }
        
        /* iic read command */
        res = pca9548a_basic_iic_read_command(dev_addr, buf, len);
        if (res != 0)
        {
            (void)pca9548a_basic_deinit();
            
            return 1;
        }
        
        /* output */
        pca9548a_interface_debug_print("pca9548a: device address 0x%02X.\n", dev_addr);
        pca9548a_interface_debug_print("pca9548a: data is ");
        for (i = 0; i < len; i++)
        {
            pca9548a_interface_debug_print("0x%02X ", buf[i]);
        }
        pca9548a_interface_debug_print("\n");
        
        /* basic deinit */
        (void)pca9548a_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint8_t i;
        uint8_t buf[8];
        
        /* basic init */
        res = pca9548a_basic_init(addr);
        if (res != 0)
        {
            return 1;
        }
        
        /* set channel */
        res = pca9548a_basic_set_channel(channel, PCA9548A_BOOL_TRUE);
        if (res != 0)
        {
            (void)pca9548a_basic_deinit();
            
            return 1;
        }
        
        /* iic read */
        res = pca9548a_basic_iic_read(dev_addr, reg & 0xFF, buf, len);
        if (res != 0)
        {
            (void)pca9548a_basic_deinit();
            
            return 1;
        }
        
        /* output */
        pca9548a_interface_debug_print("pca9548a: device address 0x%02X.\n", dev_addr);
        pca9548a_interface_debug_print("pca9548a: register address 0x%02X.\n", reg);
        pca9548a_interface_debug_print("pca9548a: data is ");
        for (i = 0; i < len; i++)
        {
            pca9548a_interface_debug_print("0x%02X ", buf[i]);
        }
        pca9548a_interface_debug_print("\n");
        
        /* basic deinit */
        (void)pca9548a_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_read16", type) == 0)
    {
        uint8_t res;
        uint8_t i;
        uint8_t buf[8];
        
        /* basic init */
        res = pca9548a_basic_init(addr);
        if (res != 0)
        {
            return 1;
        }
        
        /* set channel */
        res = pca9548a_basic_set_channel(channel, PCA9548A_BOOL_TRUE);
        if (res != 0)
        {
            (void)pca9548a_basic_deinit();
            
            return 1;
        }
        
        /* iic read16 */
        res = pca9548a_basic_iic_read_address16(dev_addr, reg, buf, len);
        if (res != 0)
        {
            (void)pca9548a_basic_deinit();
            
            return 1;
        }
        
        /* output */
        pca9548a_interface_debug_print("pca9548a: device address 0x%02X.\n", dev_addr);
        pca9548a_interface_debug_print("pca9548a: register address 0x%04X.\n", reg);
        pca9548a_interface_debug_print("pca9548a: data is ");
        for (i = 0; i < len; i++)
        {
            pca9548a_interface_debug_print("0x%02X ", buf[i]);
        }
        pca9548a_interface_debug_print("\n");
        
        /* basic deinit */
        (void)pca9548a_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_write-command", type) == 0)
    {
        uint8_t res;
        
        /* basic init */
        res = pca9548a_basic_init(addr);
        if (res != 0)
        {
            return 1;
        }
        
        /* set channel */
        res = pca9548a_basic_set_channel(channel, PCA9548A_BOOL_TRUE);
        if (res != 0)
        {
            (void)pca9548a_basic_deinit();
            
            return 1;
        }
        
        /* iic write command */
        res = pca9548a_basic_iic_write_command(dev_addr, &data, 1);
        if (res != 0)
        {
            (void)pca9548a_basic_deinit();
            
            return 1;
        }
        
        /* output */
        pca9548a_interface_debug_print("pca9548a: device address 0x%02X.\n", dev_addr);
        pca9548a_interface_debug_print("pca9548a: data is 0x%02X\n", data);
        
        /* basic deinit */
        (void)pca9548a_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_write", type) == 0)
    {
        uint8_t res;
        
        /* basic init */
        res = pca9548a_basic_init(addr);
        if (res != 0)
        {
            return 1;
        }
        
        /* set channel */
        res = pca9548a_basic_set_channel(channel, PCA9548A_BOOL_TRUE);
        if (res != 0)
        {
            (void)pca9548a_basic_deinit();
            
            return 1;
        }
        
        /* iic write */
        res = pca9548a_basic_iic_write(dev_addr, reg & 0xFF, &data, 1);
        if (res != 0)
        {
            (void)pca9548a_basic_deinit();
            
            return 1;
        }
        
        /* output */
        pca9548a_interface_debug_print("pca9548a: device address 0x%02X.\n", dev_addr);
        pca9548a_interface_debug_print("pca9548a: register address 0x%02X.\n", reg);
        pca9548a_interface_debug_print("pca9548a: data is 0x%02X\n", data);
        
        /* basic deinit */
        (void)pca9548a_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_write16", type) == 0)
    {
        uint8_t res;
        
        /* basic init */
        res = pca9548a_basic_init(addr);
        if (res != 0)
        {
            return 1;
        }
        
        /* set channel */
        res = pca9548a_basic_set_channel(channel, PCA9548A_BOOL_TRUE);
        if (res != 0)
        {
            (void)pca9548a_basic_deinit();
            
            return 1;
        }
        
        /* iic write */
        res = pca9548a_basic_iic_write_address16(dev_addr, reg, &data, 1);
        if (res != 0)
        {
            (void)pca9548a_basic_deinit();
            
            return 1;
        }
        
        /* output */
        pca9548a_interface_debug_print("pca9548a: device address 0x%02X.\n", dev_addr);
        pca9548a_interface_debug_print("pca9548a: register address 0x%04X.\n", reg);
        pca9548a_interface_debug_print("pca9548a: data is 0x%02X\n", data);
        
        /* basic deinit */
        (void)pca9548a_basic_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        pca9548a_interface_debug_print("Usage:\n");
        pca9548a_interface_debug_print("  pca9548a (-i | --information)\n");
        pca9548a_interface_debug_print("  pca9548a (-h | --help)\n");
        pca9548a_interface_debug_print("  pca9548a (-p | --port)\n");
        pca9548a_interface_debug_print("  pca9548a (-t reg | --test=reg) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]\n");
        pca9548a_interface_debug_print("  pca9548a (-e read-command | --example=read-command) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--channel=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]\n");
        pca9548a_interface_debug_print("           [--dev-addr=<hex>] [--length=<len>]\n");
        pca9548a_interface_debug_print("  pca9548a (-e read | --example=read) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--channel=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]\n");
        pca9548a_interface_debug_print("           [--dev-addr=<hex>] [--reg=<hex>] [--length=<len>]\n");
        pca9548a_interface_debug_print("  pca9548a (-e read16 | --example=read16) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--channel=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]\n");
        pca9548a_interface_debug_print("           [--dev-addr=<hex>] [--reg=<hex>] [--length=<len>]\n");
        pca9548a_interface_debug_print("  pca9548a (-e write-command | --example=write-command) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--channel=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]\n");
        pca9548a_interface_debug_print("           [--dev-addr=<hex>] [--data=<hex>]\n");
        pca9548a_interface_debug_print("  pca9548a (-e write | --example=write) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--channel=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]\n");
        pca9548a_interface_debug_print("           [--dev-addr=<hex>] [--reg=<hex>] [--data=<hex>]\n");
        pca9548a_interface_debug_print("  pca9548a (-e write16 | --example=write16) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--channel=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]\n");
        pca9548a_interface_debug_print("           [--dev-addr=<hex>] [--reg=<hex>] [--data=<hex>]\n");
        pca9548a_interface_debug_print("\n");
        pca9548a_interface_debug_print("Options:\n");
        pca9548a_interface_debug_print("      --addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>\n");
        pca9548a_interface_debug_print("                              Set the addr pin.([default: 0])\n");
        pca9548a_interface_debug_print("      --channel=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>\n");
        pca9548a_interface_debug_print("                              Set the chip channel.([default: 0])\n");
        pca9548a_interface_debug_print("      --data=<hex>            Set the data in hex format.([default: 0x00])\n");
        pca9548a_interface_debug_print("      --dev-addr=<hex>        Set the device address in hex format.([default: 0x00])\n");
        pca9548a_interface_debug_print("  -e <read-command | read | read16 | write-command | write | write16>,\n");
        pca9548a_interface_debug_print("      --example=<read-command | read | read16 | write-command | write | write16>\n");
        pca9548a_interface_debug_print("                              Run the driver example.\n");
        pca9548a_interface_debug_print("  -h, --help                  Show the help.\n");
        pca9548a_interface_debug_print("  -i, --information           Show the chip information.\n");
        pca9548a_interface_debug_print("      --reg=<hex>             Set the register address in hex format.([default: 0x00])\n");
        pca9548a_interface_debug_print("      --length=<len>          Set the length of data to be read.([default: 1])\n");
        pca9548a_interface_debug_print("  -p, --port                  Display the pin connections of the current board.\n");
        pca9548a_interface_debug_print("  -t <reg>, --test=<reg>      Run the driver test.\n");

        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        pca9548a_info_t info;
        
        /* print pca9548a info */
        pca9548a_info(&info);
        pca9548a_interface_debug_print("pca9548a: chip is %s.\n", info.chip_name);
        pca9548a_interface_debug_print("pca9548a: manufacturer is %s.\n", info.manufacturer_name);
        pca9548a_interface_debug_print("pca9548a: interface is %s.\n", info.interface);
        pca9548a_interface_debug_print("pca9548a: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        pca9548a_interface_debug_print("pca9548a: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        pca9548a_interface_debug_print("pca9548a: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        pca9548a_interface_debug_print("pca9548a: max current is %0.2fmA.\n", info.max_current_ma);
        pca9548a_interface_debug_print("pca9548a: max temperature is %0.1fC.\n", info.temperature_max);
        pca9548a_interface_debug_print("pca9548a: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        pca9548a_interface_debug_print("pca9548a: SCL connected to GPIOB PIN8.\n");
        pca9548a_interface_debug_print("pca9548a: SDA connected to GPIOB PIN9.\n");
        pca9548a_interface_debug_print("pca9548a: RST connected to GPIOA PIN8.\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart init */
    uart_init(115200);
    
    /* shell init && register pca9548a function */
    shell_init();
    shell_register("pca9548a", pca9548a);
    uart_print("pca9548a: welcome to libdriver pca9548a.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("pca9548a: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("pca9548a: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("pca9548a: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("pca9548a: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("pca9548a: param is invalid.\n");
            }
            else
            {
                uart_print("pca9548a: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
