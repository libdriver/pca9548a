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
 * @file      driver_pca9548a_register_test.c
 * @brief     driver pca9548a register test source file
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

static pca9548a_handle_t gs_handle;        /**< pca9548a handle */

/**
 * @brief     register test
 * @param[in] addr iic device address
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t pca9548a_register_test(pca9548a_address_t addr)
{
    uint8_t res;
    uint8_t i;
    pca9548a_bool_t enable;
    pca9548a_info_t info;
    
    /* link functions */
    DRIVER_PCA9548A_LINK_INIT(&gs_handle, pca9548a_handle_t);
    DRIVER_PCA9548A_LINK_RESET_GPIO_INIT(&gs_handle, pca9548a_interface_reset_gpio_init);
    DRIVER_PCA9548A_LINK_RESET_GPIO_DEINIT(&gs_handle, pca9548a_interface_reset_gpio_deinit);
    DRIVER_PCA9548A_LINK_RESET_GPIO_WRITE(&gs_handle, pca9548a_interface_reset_gpio_write);
    DRIVER_PCA9548A_LINK_IIC_INIT(&gs_handle, pca9548a_interface_iic_init);
    DRIVER_PCA9548A_LINK_IIC_DEINIT(&gs_handle, pca9548a_interface_iic_deinit);
    DRIVER_PCA9548A_LINK_IIC_READ_COMMAND(&gs_handle, pca9548a_interface_iic_read_cmd);
    DRIVER_PCA9548A_LINK_IIC_WRITE_COMMAND(&gs_handle, pca9548a_interface_iic_write_cmd);
    DRIVER_PCA9548A_LINK_IIC_READ(&gs_handle, pca9548a_interface_iic_read);
    DRIVER_PCA9548A_LINK_IIC_WRITE(&gs_handle, pca9548a_interface_iic_write);
    DRIVER_PCA9548A_LINK_IIC_READ_ADDRESS16(&gs_handle, pca9548a_interface_iic_read_address16);
    DRIVER_PCA9548A_LINK_IIC_WRITE_ADDRESS16(&gs_handle, pca9548a_interface_iic_write_address16);
    DRIVER_PCA9548A_LINK_DELAY_MS(&gs_handle, pca9548a_interface_delay_ms);
    DRIVER_PCA9548A_LINK_DEBUG_PRINT(&gs_handle, pca9548a_interface_debug_print);
    
    /* pca9548a info */
    res = pca9548a_info(&info);
    if (res != 0)
    {
        pca9548a_interface_debug_print("pca9548a: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        pca9548a_interface_debug_print("pca9548a: chip is %s.\n", info.chip_name);
        pca9548a_interface_debug_print("pca9548a: manufacturer is %s.\n", info.manufacturer_name);
        pca9548a_interface_debug_print("pca9548a: interface is %s.\n", info.interface);
        pca9548a_interface_debug_print("pca9548a: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        pca9548a_interface_debug_print("pca9548a: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        pca9548a_interface_debug_print("pca9548a: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        pca9548a_interface_debug_print("pca9548a: max current is %0.2fmA.\n", info.max_current_ma);
        pca9548a_interface_debug_print("pca9548a: max temperature is %0.1fC.\n", info.temperature_max);
        pca9548a_interface_debug_print("pca9548a: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* set addr pin */
    res = pca9548a_set_addr_pin(&gs_handle, addr);
    if (res != 0)
    {
        pca9548a_interface_debug_print("pca9548a: set addr pin failed.\n");
       
        return 1;
    }
    
    /* start register test */
    pca9548a_interface_debug_print("pca9548a: start register test.\n");
    
    /* pca9548a init */
    res = pca9548a_init(&gs_handle);
    if (res != 0)
    {
        pca9548a_interface_debug_print("pca9548a: init failed.\n");
       
        return 1;
    }
    
    /* pca9548a_set_channel/pca9548a_get_channel test */
    pca9548a_interface_debug_print("pca9548a: pca9548a_set_channel/pca9548a_get_channel test.\n");
    
    for (i = 0; i < 8; i++)
    {
        pca9548a_channel_t channel;
        
        if (i == 0)
        {
            channel = PCA9548A_CHANNEL_0;
        }
        else if (i == 1)
        {
            channel = PCA9548A_CHANNEL_1;
        }
        else if (i == 2)
        {
            channel = PCA9548A_CHANNEL_2;
        }
        else if (i == 3)
        {
            channel = PCA9548A_CHANNEL_3;
        }
        else if (i == 4)
        {
            channel = PCA9548A_CHANNEL_4;
        }
        else if (i == 5)
        {
            channel = PCA9548A_CHANNEL_5;
        }
        else if (i == 6)
        {
            channel = PCA9548A_CHANNEL_6;
        }
        else
        {
            channel = PCA9548A_CHANNEL_7;
        }
        
        /* enable channel x */
        res = pca9548a_set_channel(&gs_handle, channel, PCA9548A_BOOL_TRUE);
        if (res != 0)
        {
            pca9548a_interface_debug_print("pca9548a: set channel failed.\n");
            (void)pca9548a_deinit(&gs_handle);
            
            return 1;
        }
        pca9548a_interface_debug_print("pca9548a: enable channel %d.\n", i);
        res = pca9548a_get_channel(&gs_handle, channel, &enable);
        if (res != 0)
        {
            pca9548a_interface_debug_print("pca9548a: get channel failed.\n");
            (void)pca9548a_deinit(&gs_handle);
            
            return 1;
        }
        pca9548a_interface_debug_print("pca9548a: check channel %s.\n", (enable == PCA9548A_BOOL_TRUE) ? "ok" : "error");
        
        /* disable channel x */
        res = pca9548a_set_channel(&gs_handle, channel, PCA9548A_BOOL_FALSE);
        if (res != 0)
        {
            pca9548a_interface_debug_print("pca9548a: set channel failed.\n");
            (void)pca9548a_deinit(&gs_handle);
            
            return 1;
        }
        pca9548a_interface_debug_print("pca9548a: disable channel %d.\n", i);
        res = pca9548a_get_channel(&gs_handle, channel, &enable);
        if (res != 0)
        {
            pca9548a_interface_debug_print("pca9548a: get channel failed.\n");
            (void)pca9548a_deinit(&gs_handle);
            
            return 1;
        }
        pca9548a_interface_debug_print("pca9548a: check channel %s.\n", (enable == PCA9548A_BOOL_FALSE) ? "ok" : "error");
    }
    
    /* pca9548a_reset_bus test */
    pca9548a_interface_debug_print("pca9548a: pca9548a_reset_bus test.\n");
    
    /* reset bus */
    res = pca9548a_reset_bus(&gs_handle);
    if (res != 0)
    {
        pca9548a_interface_debug_print("pca9548a: reset bus failed.\n");
        (void)pca9548a_deinit(&gs_handle);
        
        return 1;
    }
    pca9548a_interface_debug_print("pca9548a: check reset bus %s.\n", (res == 0) ? "ok" : "error");
    
    /* finish register test */
    pca9548a_interface_debug_print("pca9548a: finish register test.\n");  
    (void)pca9548a_deinit(&gs_handle);
    
    return 0;
}
