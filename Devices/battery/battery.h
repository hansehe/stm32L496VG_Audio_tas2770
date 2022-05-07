/*
 * battery.h
 *
 *  Created on: 10. sep. 2021
 *      Author: Hans Erik Heggem
 */

#ifndef BATTERY_BATTERY_H_
#define BATTERY_BATTERY_H_

#include <stdint.h>

typedef enum
{
    BATTERY_OK,
    BATTERY_ERR_SPI,
} battery_status_t;

battery_status_t battery_voltage(uint16_t *voltage);

battery_status_t battery_state_of_charge(uint16_t *relative_soc);

battery_status_t battery_internal_temperature(uint16_t *internal_temp);

battery_status_t battery_temperature_sensor(uint16_t *temp_sensor);

battery_status_t battery_full_capacity(uint16_t *full_capacity);

battery_status_t battery_remaining_capacity(uint16_t *remaining_capacity);


#endif /* BATTERY_BATTERY_H_ */
