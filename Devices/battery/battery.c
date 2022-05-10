/*
 * battery.c
 *
 *  Created on: 10. sep. 2021
 *      Author: Hans Erik Heggem
 */

#include "battery.h"

#include <stdbool.h>
#include "main.h"
#include "../i2c_port/i2c_port.h"
#include "battery.h"
#include "hy4145.h"
#include "a1141.h"

#define BATTERY_I2C_TIMEOUT_MS 10000U

battery_status_t battery_read_command(uint8_t command, uint16_t *response)
{
    uint8_t txdata[] = {command};
    uint8_t txdata_sec[] = {command + 0x01};

//	uint8_t txdata[] = {command >> 8};
//	uint8_t txdata_sec[] = {command & 0x00ff};

    uint8_t rxdata[] = {0, 0};

    if(i2c_port_write(A1141_I2C_SLAVE_ADDRESS, txdata, 1, BATTERY_I2C_TIMEOUT_MS) != I2C_PORT_OK)
    {
        return BATTERY_ERR_SPI;
    }
    if(i2c_port_write(A1141_I2C_SLAVE_ADDRESS, txdata_sec, 1, BATTERY_I2C_TIMEOUT_MS) != I2C_PORT_OK)
    {
        return BATTERY_ERR_SPI;
    }

    if(i2c_port_read(A1141_I2C_SLAVE_ADDRESS, rxdata, 2, BATTERY_I2C_TIMEOUT_MS) != I2C_PORT_OK)
    {
        return BATTERY_ERR_SPI;
    }

    *response = (rxdata[0] << 8) | rxdata[1];
    return BATTERY_OK;
}


battery_status_t battery_state_of_charge(uint16_t *relative_soc)
{
	return battery_read_command(HY4145_RELATIVE_STATE_OF_CHARGE, relative_soc);
}



