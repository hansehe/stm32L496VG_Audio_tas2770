/*
 * battery.h
 *
 *  Created on: 10. sep. 2021
 *      Author: Hans Erik Heggem
 */


#ifndef BATTERY_HY4145_H_
#define BATTERY_HY4145_H_

// Return types: I2 = 2-byte Signed Integer; U2 = 2-byte Unsigned Integer.
// Because each command consists of two bytes of data, two consecutive transmissions must be executed both to initiate the command function, and to read or write the corresponding two bytes of data.

#define HY4145_AT_REATE_TIME_TO_EMTPY  				0x04 //U2
#define HY4145_TEMPERATURE      					0x06 //U2
#define HY4145_VOLTAGE      						0x08 //U2
#define HY4145_FLAGS 								0x0a //U2
#define HY4145_NOMINAL_AVAILABLE_CAPACITY       	0x0c //U2
#define HY4145_FULL_AVAILABLE_CAPACITY    			0x0e //U2
#define HY4145_REMAINING_CAPACITY       			0x10 //U2
#define HY4145_FULL_CHARGE_CAPACITY       			0x12 //U2
#define HY4145_AVERAGE_CURRENT       				0x14 //I2
#define HY4145_RUN_TIME_TO_EMPTY       				0x16 //U2
#define HY4145_AVERAGE_TIME_TO_FULL       			0x18 //U2
#define HY4145_STANDBY_CURRENT       				0x1a //I2
#define HY4145_STANDBY_TIME_TO_EMPTY       			0x1c //U2
#define HY4145_MAX_LOAD_CURRENT     				0x1e //I2
#define HY4145_MAX_LOAD_TIME_TO_EMPTY         		0x20 //U2
#define HY4145_AVAILABLE_ENERGY         			0x22 //U2
#define HY4145_AVAILABLE_POWER         				0x24 //U2
#define HY4145_TIME_TO_EMPTY_AT_CONSTANT_POWER      0x26 //U2
#define HY4145_INTERNAL_TEMPERATURE         		0x28 //U2
#define HY4145_CYCLE_COUNT         					0x2a //U2
#define HY4145_RELATIVE_STATE_OF_CHARGE   			0x2c //U2
#define HY4145_STATE_OF_HEALTH    					0x2e //U2
#define HY4145_CURRENT        						0x30 //U2
#define HY4145_SAFETY_STATUS     					0x32 //U2
#define HY4145_PASSED_CHARGE        				0x34 //U2
#define HY4145_DEPTH_OF_DISCHARGE   				0x36 //U2

#define HY4145_I2C_SLAVE_ADDRESS (0b1010101 << 1)

#endif /* BATTERY_HY4145_H_ */
