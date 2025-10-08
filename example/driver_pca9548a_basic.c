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
 * @file      driver_pca9548a_basic.c
 * @brief     driver pca9548a basic source file
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

#include "driver_pca9548a_basic.h"

static pca9548a_handle_t gs_handle;        /**< pca9548a handle */

/**
 * @brief     basic example init
 * @param[in] addr iic device address
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t pca9548a_basic_init(pca9548a_address_t addr)
{
    uint8_t res;
    
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
    
    /* set addr pin */
    res = pca9548a_set_addr_pin(&gs_handle, addr);
    if (res != 0)
    {
        pca9548a_interface_debug_print("pca9548a: set addr pin failed.\n");
       
        return 1;
    }
    
    /* pca9548a init */
    res = pca9548a_init(&gs_handle);
    if (res != 0)
    {
        pca9548a_interface_debug_print("pca9548a: init failed.\n");
       
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t pca9548a_basic_deinit(void)
{
    if (pca9548a_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example set channel
 * @param[in] channel input channel
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set channel failed
 * @note      none
 */
uint8_t pca9548a_basic_set_channel(pca9548a_channel_t channel, pca9548a_bool_t enable)
{
    if (pca9548a_set_channel(&gs_handle, channel, enable) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example get channel
 * @param[in]  channel input channel
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get channel failed
 * @note       none
 */
uint8_t pca9548a_basic_get_channel(pca9548a_channel_t channel, pca9548a_bool_t *enable)
{
    if (pca9548a_get_channel(&gs_handle, channel, enable) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example reset bus
 * @return status code
 *         - 0 success
 *         - 1 reset bus failed
 * @note   none
 */
uint8_t pca9548a_basic_reset_bus(void)
{
    if (pca9548a_reset_bus(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example iic read command
 * @param[in]  addr iic address
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len buffer length
 * @return     status code
 *             - 0 success
 *             - 1 iic read failed
 * @note       none
 */
uint8_t pca9548a_basic_iic_read_command(uint8_t addr, uint8_t *buf, uint16_t len)
{
    if (pca9548a_iic_read_command(&gs_handle, addr, buf, len) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example iic write command
 * @param[in] addr iic address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len buffer length
 * @return    status code
 *            - 0 success
 *            - 1 iic write failed
 * @note      none
 */
uint8_t pca9548a_basic_iic_write_command(uint8_t addr, uint8_t *buf, uint16_t len)
{
    if (pca9548a_iic_write_command(&gs_handle, addr, buf, len) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example iic read
 * @param[in]  addr iic address
 * @param[in]  reg register address
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len buffer length
 * @return     status code
 *             - 0 success
 *             - 1 iic read failed
 * @note       none
 */
uint8_t pca9548a_basic_iic_read(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (pca9548a_iic_read(&gs_handle, addr, reg, buf, len) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example iic write
 * @param[in] addr iic address
 * @param[in] reg register address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len buffer length
 * @return    status code
 *            - 0 success
 *            - 1 iic write failed
 * @note      none
 */
uint8_t pca9548a_basic_iic_write(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (pca9548a_iic_write(&gs_handle, addr, reg, buf, len) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example iic read address16
 * @param[in]  addr iic address
 * @param[in]  reg register address
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len buffer length
 * @return     status code
 *             - 0 success
 *             - 1 iic read failed
 * @note       none
 */
uint8_t pca9548a_basic_iic_read_address16(uint8_t addr, uint16_t reg, uint8_t *buf, uint16_t len)
{
    if (pca9548a_iic_read_address16(&gs_handle, addr, reg, buf, len) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example iic write address16
 * @param[in] addr iic address
 * @param[in] reg register address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len buffer length
 * @return    status code
 *            - 0 success
 *            - 1 iic write failed
 * @note      none
 */
uint8_t pca9548a_basic_iic_write_address16(uint8_t addr, uint16_t reg, uint8_t *buf, uint16_t len)
{
    if (pca9548a_iic_write_address16(&gs_handle, addr, reg, buf, len) != 0)
    {
        return 1;
    }
    
    return 0;
}
