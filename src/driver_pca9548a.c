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
 * @file      driver_pca9548a.c
 * @brief     driver pca9548a source file
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

#include "driver_pca9548a.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "NXP PCA9548A"       /**< chip name */
#define MANUFACTURER_NAME         "NXP"                /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.3f                 /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.5f                 /**< chip max supply voltage */
#define MAX_CURRENT               100.0f               /**< chip max current */
#define TEMPERATURE_MIN           -40.0f               /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                /**< chip max operating temperature */
#define DRIVER_VERSION            1000                 /**< driver version */

/**
 * @brief     set the address pin
 * @param[in] *handle pointer to a pca9548a handle structure
 * @param[in] addr_pin chip address pins
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t pca9548a_set_addr_pin(pca9548a_handle_t *handle, pca9548a_address_t addr_pin)
{
    if (handle == NULL)                            /* check handle */
    {
        return 2;                                  /* return error */
    }

    handle->iic_addr = (uint8_t)(addr_pin);        /* set iic address */
    
    return 0;                                      /* success return 0 */
}

/**
 * @brief      get the address pin
 * @param[in]  *handle pointer to a pca9548a handle structure
 * @param[out] *addr_pin pointer to a chip address pins buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t pca9548a_get_addr_pin(pca9548a_handle_t *handle, pca9548a_address_t *addr_pin)
{
    if (handle == NULL)                                        /* check handle */
    {
        return 2;                                              /* return error */
    }

    *addr_pin = (pca9548a_address_t)(handle->iic_addr);        /*get iic address */
    
    return 0;                                                  /* success return 0 */
}

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
uint8_t pca9548a_init(pca9548a_handle_t *handle)
{
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->debug_print == NULL)                                            /* check debug_print */
    {
        return 3;                                                               /* return error */
    }
    if (handle->reset_gpio_init == NULL)                                        /* check reset_gpio_init */
    {
        handle->debug_print("pca9548a: reset_gpio_init is null.\n");            /* reset_gpio_init is null */
       
        return 3;                                                               /* return error */
    }
    if (handle->reset_gpio_deinit == NULL)                                      /* check reset_gpio_deinit */
    {
        handle->debug_print("pca9548a: reset_gpio_deinit is null.\n");          /* reset_gpio_deinit is null */
       
        return 3;                                                               /* return error */
    }
    if (handle->reset_gpio_write == NULL)                                       /* check reset_gpio_write */
    {
        handle->debug_print("pca9548a: reset_gpio_write is null.\n");           /* reset_gpio_write is null */
       
        return 3;                                                               /* return error */
    }
    if (handle->iic_init == NULL)                                               /* check iic_init */
    {
        handle->debug_print("pca9548a: iic_init is null.\n");                   /* iic_init is null */
       
        return 3;                                                               /* return error */
    }
    if (handle->iic_deinit == NULL)                                             /* check iic_deinit */
    {
        handle->debug_print("pca9548a: iic_deinit is null.\n");                 /* iic_deinit is null */
       
        return 3;                                                               /* return error */
    }
    if (handle->iic_read_cmd == NULL)                                           /* check iic_read_cmd */
    {
        handle->debug_print("pca9548a: iic_read_cmd is null.\n");               /* iic_read_cmd is null */
       
        return 3;                                                               /* return error */
    }
    if (handle->iic_write_cmd == NULL)                                          /* check iic_write_cmd */
    {
        handle->debug_print("pca9548a: iic_write_cmd is null.\n");              /* iic_write_cmd is null */
       
        return 3;                                                               /* return error */
    }
    if (handle->iic_read == NULL)                                               /* check iic_read */
    {
        handle->debug_print("pca9548a: iic_read is null.\n");                   /* iic_read is null */
       
        return 3;                                                               /* return error */
    }
    if (handle->iic_write == NULL)                                              /* check iic_write */
    {
        handle->debug_print("pca9548a: iic_write is null.\n");                  /* iic_write is null */
       
        return 3;                                                               /* return error */
    }
    if (handle->iic_read_address16 == NULL)                                     /* check iic_read_address16 */
    {
        handle->debug_print("pca9548a: iic_read_address16 is null.\n");         /* iic_read_address16 is null */
       
        return 3;                                                               /* return error */
    }
    if (handle->iic_write_address16 == NULL)                                    /* check iic_write_address16 */
    {
        handle->debug_print("pca9548a: iic_write_address16 is null.\n");        /* iic_write_address16 is null */
       
        return 3;                                                               /* return error */
    }
    if (handle->delay_ms == NULL)                                               /* check delay_ms */
    {
        handle->debug_print("pca9548a: delay_ms is null.\n");                   /* delay_ms is null */
       
        return 3;                                                               /* return error */
    }
    
    if (handle->iic_init() != 0)                                                /* iic init */
    {
        handle->debug_print("pca9548a: iic init failed.\n");                    /* iic init failed */
       
        return 1;                                                               /* return error */
    }
    if (handle->reset_gpio_init() != 0)                                         /* reset gpio init */
    {
        handle->debug_print("pca9548a: reset gpio init failed.\n");             /* reset gpio init failed */
        (void)handle->iic_deinit();                                             /* iic deinit */
        
        return 1;                                                               /* return error */
    }
    if (handle->reset_gpio_write(0) != 0)                                       /* set low */
    {
        handle->debug_print("pca9548a: reset gpio write failed.\n");            /* reset gpio write failed */
        (void)handle->iic_deinit();                                             /* iic deinit */
        (void)handle->reset_gpio_deinit();                                      /* reset gpio deinit */
        
        return 4;                                                               /* return error */
    }
    handle->delay_ms(2);                                                        /* delay 2ms */
    if (handle->reset_gpio_write(1) != 0)                                       /* set high */
    {
        handle->debug_print("pca9548a: reset gpio write failed.\n");            /* reset gpio write failed */
        (void)handle->iic_deinit();                                             /* iic deinit */
        (void)handle->reset_gpio_deinit();                                      /* reset gpio deinit */
        
        return 4;                                                               /* return error */
    }
    handle->delay_ms(2);                                                        /* delay 2ms */
    handle->channel = 0x00;                                                     /* set 0x00 */
    if (handle->iic_write_cmd(handle->iic_addr, 
                             (uint8_t *)&handle->channel, 1) != 0)              /* write all channel disabled */
    {
        handle->debug_print("pca9548a: iic write failed.\n");                   /* iic write failed */
        (void)handle->iic_deinit();                                             /* iic deinit */
        
        return 5;                                                               /* return error */
    }
    handle->inited = 1;                                                         /* flag finish initialization */
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t pca9548a_deinit(pca9548a_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    handle->channel = 0x00;                                               /* set 0x00 */
    if (handle->iic_write_cmd(handle->iic_addr, 
                             (uint8_t *)&handle->channel, 1) != 0)        /* write all channel disabled */
    {
        handle->debug_print("pca9548a: iic write failed.\n");             /* iic write failed */
        
        return 4;                                                         /* return error */
    }
    res = handle->iic_deinit();                                           /* iic deinit */
    if (res != 0)                                                         /* check error */
    {
        handle->debug_print("pca9548a: iic deinit failed.\n");            /* iic deinit failed */
       
        return 1;                                                         /* return error */
    }
    res = handle->reset_gpio_deinit();                                    /* reset gpio deinit */
    if (res != 0)                                                         /* check error */
    {
        handle->debug_print("pca9548a: reset gpio deinit failed.\n");     /* reset gpio deinit failed */
       
        return 1;                                                         /* return error */
    }
    handle->inited = 0;                                                   /* flag closed */
    
    return 0;                                                             /* success return 0 */
}

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
uint8_t pca9548a_reset_bus(pca9548a_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = handle->reset_gpio_write(0);                                      /* set low */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("pca9548a: reset gpio write failed.\n");        /* reset gpio write failed */
        
        return 1;                                                           /* return error */
    }
    handle->delay_ms(2);                                                    /* delay 2ms */
    res = handle->reset_gpio_write(1);                                      /* set high */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("pca9548a: reset gpio write failed.\n");        /* reset gpio write failed */
        
        return 1;                                                           /* return error */
    }
    handle->delay_ms(2);                                                    /* delay 2ms */
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t pca9548a_set_channel(pca9548a_handle_t *handle, pca9548a_channel_t channel, pca9548a_bool_t enable)
{
    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }
    
    handle->channel &= ~(1 << channel);                                                      /* clear channel */
    handle->channel |= enable << channel;                                                    /* set channel */
    if (handle->iic_write_cmd(handle->iic_addr, (uint8_t *)&handle->channel, 1) != 0)        /* write channel config */
    {
        handle->debug_print("pca9548a: set channel failed.\n");                              /* set channel failed */
        
        return 1;                                                                            /* return error */
    }
    
    return 0;                                                                                /* success return 0 */
}

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
uint8_t pca9548a_get_channel(pca9548a_handle_t *handle, pca9548a_channel_t channel, pca9548a_bool_t *enable)
{
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    *enable = (pca9548a_bool_t)((handle->channel >> channel) & 0x01);        /* set channel */
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t pca9548a_iic_read_command(pca9548a_handle_t *handle, uint8_t addr, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                             /* check handle */
    {
        return 2;                                                   /* return error */
    }
    if (handle->inited != 1)                                        /* check handle initialization */
    {
        return 3;                                                   /* return error */
    }
    
    if (handle->iic_read_cmd(addr, buf, len) != 0)                  /* iic read */
    {
        handle->debug_print("pca9548a: iic read failed.\n");        /* iic read failed */
        
        return 1;                                                   /* return error */
    }
    
    return 0;                                                       /* success return 0 */
}

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
uint8_t pca9548a_iic_write_command(pca9548a_handle_t *handle, uint8_t addr, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (handle->iic_write_cmd(addr, buf, len) != 0)                  /* iic write */
    {
        handle->debug_print("pca9548a: iic write failed.\n");        /* iic write failed */
        
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t pca9548a_iic_read(pca9548a_handle_t *handle, uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                             /* check handle */
    {
        return 2;                                                   /* return error */
    }
    if (handle->inited != 1)                                        /* check handle initialization */
    {
        return 3;                                                   /* return error */
    }
    
    if (handle->iic_read(addr, reg, buf, len) != 0)                 /* iic read */
    {
        handle->debug_print("pca9548a: iic read failed.\n");        /* iic read failed */
        
        return 1;                                                   /* return error */
    }
    
    return 0;                                                       /* success return 0 */
}

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
uint8_t pca9548a_iic_write(pca9548a_handle_t *handle, uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (handle->iic_write(addr, reg, buf, len) != 0)                 /* iic write */
    {
        handle->debug_print("pca9548a: iic write failed.\n");        /* iic write failed */
        
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t pca9548a_iic_read_address16(pca9548a_handle_t *handle, uint8_t addr, uint16_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (handle->iic_read_address16(addr, reg, buf, len) != 0)        /* iic read */
    {
        handle->debug_print("pca9548a: iic read failed.\n");         /* iic read failed */
        
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t pca9548a_iic_write_address16(pca9548a_handle_t *handle, uint8_t addr, uint16_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    if (handle->iic_write_address16(addr, reg, buf, len) != 0)        /* iic write */
    {
        handle->debug_print("pca9548a: iic write failed.\n");         /* iic write failed */
        
        return 1;                                                     /* return error */
    }
    
    return 0;                                                         /* success return 0 */
}

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a pca9548a info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t pca9548a_info(pca9548a_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(pca9548a_info_t));                       /* initialize pca9548a info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
