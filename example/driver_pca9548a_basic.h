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
 * @file      driver_pca9548a_basic.h
 * @brief     driver pca9548a basic header file
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

#ifndef DRIVER_PCA9548A_BASIC_H
#define DRIVER_PCA9548A_BASIC_H

#include "driver_pca9548a_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup pca9548a_example_driver pca9548a example driver function
 * @brief    pca9548a example driver modules
 * @ingroup  pca9548a_driver
 * @{
 */

/**
 * @brief     basic example init
 * @param[in] addr iic device address
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t pca9548a_basic_init(pca9548a_address_t addr);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t pca9548a_basic_deinit(void);

/**
 * @brief     basic example set channel
 * @param[in] channel input channel
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set channel failed
 * @note      none
 */
uint8_t pca9548a_basic_set_channel(pca9548a_channel_t channel, pca9548a_bool_t enable);

/**
 * @brief      basic example get channel
 * @param[in]  channel input channel
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get channel failed
 * @note       none
 */
uint8_t pca9548a_basic_get_channel(pca9548a_channel_t channel, pca9548a_bool_t *enable);

/**
 * @brief  basic example reset bus
 * @return status code
 *         - 0 success
 *         - 1 reset bus failed
 * @note   none
 */
uint8_t pca9548a_basic_reset_bus(void);

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
uint8_t pca9548a_basic_iic_read_command(uint8_t addr, uint8_t *buf, uint16_t len);

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
uint8_t pca9548a_basic_iic_write_command(uint8_t addr, uint8_t *buf, uint16_t len);

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
uint8_t pca9548a_basic_iic_read(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);

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
uint8_t pca9548a_basic_iic_write(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);

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
uint8_t pca9548a_basic_iic_read_address16(uint8_t addr, uint16_t reg, uint8_t *buf, uint16_t len);

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
uint8_t pca9548a_basic_iic_write_address16(uint8_t addr, uint16_t reg, uint8_t *buf, uint16_t len);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
