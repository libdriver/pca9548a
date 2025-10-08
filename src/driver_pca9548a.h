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
 * @file      driver_pca9548a.h
 * @brief     driver pca9548a header file
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

#ifndef DRIVER_PCA9548A_H
#define DRIVER_PCA9548A_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup pca9548a_driver pca9548a driver function
 * @brief    pca9548a driver modules
 * @{
 */

/**
 * @addtogroup pca9548a_base_driver
 * @{
 */

/**
 * @brief pca9548a address enumeration definition
 */
typedef enum
{
    PCA9548A_ADDRESS_A000 = 0xE0,        /**< A2A1A0 000 */
    PCA9548A_ADDRESS_A001 = 0xE2,        /**< A2A1A0 001 */
    PCA9548A_ADDRESS_A010 = 0xE4,        /**< A2A1A0 010 */
    PCA9548A_ADDRESS_A011 = 0xE6,        /**< A2A1A0 011 */
    PCA9548A_ADDRESS_A100 = 0xE8,        /**< A2A1A0 100 */
    PCA9548A_ADDRESS_A101 = 0xEA,        /**< A2A1A0 101 */
    PCA9548A_ADDRESS_A110 = 0xEC,        /**< A2A1A0 110 */
    PCA9548A_ADDRESS_A111 = 0xEE,        /**< A2A1A0 111 */
} pca9548a_address_t;

/**
 * @brief pca9548a bool enumeration definition
 */
typedef enum
{
    PCA9548A_BOOL_FALSE = 0x00,        /**< disable */
    PCA9548A_BOOL_TRUE  = 0x01,        /**< enable */
} pca9548a_bool_t;

/**
 * @brief pca9548a channel enumeration definition
 */
typedef enum
{
    PCA9548A_CHANNEL_0 = 0,        /**< channel 0 */
    PCA9548A_CHANNEL_1 = 1,        /**< channel 1 */
    PCA9548A_CHANNEL_2 = 2,        /**< channel 2 */
    PCA9548A_CHANNEL_3 = 3,        /**< channel 3 */
    PCA9548A_CHANNEL_4 = 4,        /**< channel 4 */
    PCA9548A_CHANNEL_5 = 5,        /**< channel 5 */
    PCA9548A_CHANNEL_6 = 6,        /**< channel 6 */
    PCA9548A_CHANNEL_7 = 7,        /**< channel 7 */
} pca9548a_channel_t;

/**
 * @brief pca9548a handle structure definition
 */
typedef struct pca9548a_handle_s
{
    uint8_t (*reset_gpio_init)(void);                                                              /**< point to a reset_gpio_init function address */
    uint8_t (*reset_gpio_deinit)(void);                                                            /**< point to a reset_gpio_deinit function address */
    uint8_t (*reset_gpio_write)(uint8_t level);                                                    /**< point to a reset_gpio_write function address */
    uint8_t (*iic_init)(void);                                                                     /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                                   /**< point to an iic_deinit function address */
    uint8_t (*iic_read_cmd)(uint8_t addr, uint8_t *buf, uint16_t len);                             /**< point to an iic_read_cmd function address */
    uint8_t (*iic_write_cmd)(uint8_t addr, uint8_t *buf, uint16_t len);                            /**< point to an iic_write_cmd function address */
    uint8_t (*iic_read)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);                    /**< point to an iic_read function address */
    uint8_t (*iic_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);                   /**< point to an iic_write function address */
    uint8_t (*iic_read_address16)(uint8_t addr, uint16_t reg, uint8_t *buf, uint16_t len);         /**< point to an iic_read_address16 function address */
    uint8_t (*iic_write_address16)(uint8_t addr, uint16_t reg, uint8_t *buf, uint16_t len);        /**< point to an iic_write_address16 function address */
    void (*delay_ms)(uint32_t ms);                                                                 /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                               /**< point to a debug_print function address */
    uint8_t iic_addr;                                                                              /**< iic device address */
    uint8_t channel;                                                                               /**< channel */
    uint8_t inited;                                                                                /**< inited flag */
} pca9548a_handle_t;

/**
 * @brief pca9548a information structure definition
 */
typedef struct pca9548a_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} pca9548a_info_t;

/**
 * @}
 */

/**
 * @defgroup pca9548a_link_driver pca9548a link driver function
 * @brief    pca9548a link driver modules
 * @ingroup  pca9548a_driver
 * @{
 */

/**
 * @brief     initialize pca9548a_handle_t structure
 * @param[in] HANDLE pointer to a pca9548a handle structure
 * @param[in] STRUCTURE pca9548a_handle_t
 * @note      none
 */
#define DRIVER_PCA9548A_LINK_INIT(HANDLE, STRUCTURE)                  memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link reset_gpio_init function
 * @param[in] HANDLE pointer to a pca9548a handle structure
 * @param[in] FUC pointer to a reset_gpio_init function address
 * @note      none
 */
#define DRIVER_PCA9548A_LINK_RESET_GPIO_INIT(HANDLE, FUC)            (HANDLE)->reset_gpio_init = FUC

/**
 * @brief     link reset_gpio_deinit function
 * @param[in] HANDLE pointer to a pca9548a handle structure
 * @param[in] FUC pointer to a reset_gpio_deinit function address
 * @note      none
 */
#define DRIVER_PCA9548A_LINK_RESET_GPIO_DEINIT(HANDLE, FUC)          (HANDLE)->reset_gpio_deinit = FUC

/**
 * @brief     link reset_gpio_write function
 * @param[in] HANDLE pointer to a pca9548a handle structure
 * @param[in] FUC pointer to a reset_gpio_write function address
 * @note      none
 */
#define DRIVER_PCA9548A_LINK_RESET_GPIO_WRITE(HANDLE, FUC)           (HANDLE)->reset_gpio_write = FUC

/**
 * @brief     link iic_init function
 * @param[in] HANDLE pointer to a pca9548a handle structure
 * @param[in] FUC pointer to an iic_init function address
 * @note      none
 */
#define DRIVER_PCA9548A_LINK_IIC_INIT(HANDLE, FUC)                   (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE pointer to a pca9548a handle structure
 * @param[in] FUC pointer to an iic_deinit function address
 * @note      none
 */
#define DRIVER_PCA9548A_LINK_IIC_DEINIT(HANDLE, FUC)                 (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read_cmd function
 * @param[in] HANDLE pointer to a pca9548a handle structure
 * @param[in] FUC pointer to an iic_read_cmd function address
 * @note      none
 */
#define DRIVER_PCA9548A_LINK_IIC_READ_COMMAND(HANDLE, FUC)           (HANDLE)->iic_read_cmd = FUC

/**
 * @brief     link iic_write_cmd function
 * @param[in] HANDLE pointer to a pca9548a handle structure
 * @param[in] FUC pointer to an iic_write_cmd function address
 * @note      none
 */
#define DRIVER_PCA9548A_LINK_IIC_WRITE_COMMAND(HANDLE, FUC)          (HANDLE)->iic_write_cmd = FUC

/**
 * @brief     link iic_read function
 * @param[in] HANDLE pointer to a pca9548a handle structure
 * @param[in] FUC pointer to an iic_read function address
 * @note      none
 */
#define DRIVER_PCA9548A_LINK_IIC_READ(HANDLE, FUC)                   (HANDLE)->iic_read = FUC

/**
 * @brief     link iic_write function
 * @param[in] HANDLE pointer to a pca9548a handle structure
 * @param[in] FUC pointer to an iic_write function address
 * @note      none
 */
#define DRIVER_PCA9548A_LINK_IIC_WRITE(HANDLE, FUC)                  (HANDLE)->iic_write = FUC

/**
 * @brief     link iic_read_address16 function
 * @param[in] HANDLE pointer to a pca9548a handle structure
 * @param[in] FUC pointer to an iic_read_address16 function address
 * @note      none
 */
#define DRIVER_PCA9548A_LINK_IIC_READ_ADDRESS16(HANDLE, FUC)         (HANDLE)->iic_read_address16 = FUC

/**
 * @brief     link iic_write_address16 function
 * @param[in] HANDLE pointer to a pca9548a handle structure
 * @param[in] FUC pointer to an iic_write_address16 function address
 * @note      none
 */
#define DRIVER_PCA9548A_LINK_IIC_WRITE_ADDRESS16(HANDLE, FUC)        (HANDLE)->iic_write_address16 = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE pointer to a pca9548a handle structure
 * @param[in] FUC pointer to a delay_ms function address
 * @note      none
 */
#define DRIVER_PCA9548A_LINK_DELAY_MS(HANDLE, FUC)                   (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE pointer to a pca9548a handle structure
 * @param[in] FUC pointer to a debug_print function address
 * @note      none
 */
#define DRIVER_PCA9548A_LINK_DEBUG_PRINT(HANDLE, FUC)                (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup pca9548a_base_driver pca9548a base driver function
 * @brief    pca9548a base driver modules
 * @ingroup  pca9548a_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a pca9548a info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t pca9548a_info(pca9548a_info_t *info);

/**
 * @brief     set the address pin
 * @param[in] *handle pointer to a pca9548a handle structure
 * @param[in] addr_pin chip address pins
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t pca9548a_set_addr_pin(pca9548a_handle_t *handle, pca9548a_address_t addr_pin);

/**
 * @brief      get the address pin
 * @param[in]  *handle pointer to a pca9548a handle structure
 * @param[out] *addr_pin pointer to a chip address pins buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t pca9548a_get_addr_pin(pca9548a_handle_t *handle, pca9548a_address_t *addr_pin);

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to a pca9548a handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic or gpio initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 reset failed
 *            - 5 iic write failed
 * @note      none
 */
uint8_t pca9548a_init(pca9548a_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle pointer to a pca9548a handle structure
 * @return    status code
 *            - 0 success
 *            - 1 deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 iic write failed
 * @note      none
 */
uint8_t pca9548a_deinit(pca9548a_handle_t *handle);

/**
 * @brief     set channel
 * @param[in] *handle pointer to a pca9548a handle structure
 * @param[in] channel input channel
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set channel failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9548a_set_channel(pca9548a_handle_t *handle, pca9548a_channel_t channel, pca9548a_bool_t enable);

/**
 * @brief      get channel
 * @param[in]  *handle pointer to a pca9548a handle structure
 * @param[in]  channel input channel
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9548a_get_channel(pca9548a_handle_t *handle, pca9548a_channel_t channel, pca9548a_bool_t *enable);

/**
 * @brief     reset bus
 * @param[in] *handle pointer to a pca9548a handle structure
 * @return    status code
 *            - 0 success
 *            - 1 reset bus failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9548a_reset_bus(pca9548a_handle_t *handle);

/**
 * @brief      iic read command
 * @param[in]  *handle pointer to a pca9548a handle structure
 * @param[in]  addr iic address
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len buffer length
 * @return     status code
 *             - 0 success
 *             - 1 iic read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9548a_iic_read_command(pca9548a_handle_t *handle, uint8_t addr, uint8_t *buf, uint16_t len);

/**
 * @brief     iic write command
 * @param[in] *handle pointer to a pca9548a handle structure
 * @param[in] addr iic address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len buffer length
 * @return    status code
 *            - 0 success
 *            - 1 iic write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9548a_iic_write_command(pca9548a_handle_t *handle, uint8_t addr, uint8_t *buf, uint16_t len);

/**
 * @brief      iic read
 * @param[in]  *handle pointer to a pca9548a handle structure
 * @param[in]  addr iic address
 * @param[in]  reg register address
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len buffer length
 * @return     status code
 *             - 0 success
 *             - 1 iic read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9548a_iic_read(pca9548a_handle_t *handle, uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @brief     iic write
 * @param[in] *handle pointer to a pca9548a handle structure
 * @param[in] addr iic address
 * @param[in] reg register address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len buffer length
 * @return    status code
 *            - 0 success
 *            - 1 iic write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9548a_iic_write(pca9548a_handle_t *handle, uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @brief      iic read address16
 * @param[in]  *handle pointer to a pca9548a handle structure
 * @param[in]  addr iic address
 * @param[in]  reg register address
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len buffer length
 * @return     status code
 *             - 0 success
 *             - 1 iic read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9548a_iic_read_address16(pca9548a_handle_t *handle, uint8_t addr, uint16_t reg, uint8_t *buf, uint16_t len);

/**
 * @brief     iic write address16
 * @param[in] *handle pointer to a pca9548a handle structure
 * @param[in] addr iic address
 * @param[in] reg register address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len buffer length
 * @return    status code
 *            - 0 success
 *            - 1 iic write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9548a_iic_write_address16(pca9548a_handle_t *handle, uint8_t addr, uint16_t reg, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
