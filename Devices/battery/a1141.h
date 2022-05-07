/*
 * a1141.h
 *
 *  Created on: 6 May 2022
 *      Author: magnu
 */

#ifndef BATTERY_A1141_H_
#define BATTERY_A1141_H_

#define	A1141_CNTL		0x00
#define	A1141_AR		0X02
#define	A1141_UFSOC		0X04
#define	A1141_TEMP		0X06
#define	A1141_VOLT		0X08
#define	A1141_FLAGS		0X0A
#define	A1141_NAC		0X0C
#define	A1141_FAC		0X0E
#define	A1141_RM		0X10
#define	A1141_FCC		0X12
#define	A1141_AI		0X14
#define	A1141_TTE		0X16
#define	A1141_MLI		0X1E
#define	A1141_SI		0X1A
#define	A1141_UFRM		0X20
#define	A1141_AP		0X24
#define	A1141_INTTEMP	0X28

#define	A1141_I2C_SLAVE_ADDRESS	0XAA //10101010

#define HY4145_I2C_SLAVE_ADDRESS (0b1010101 << 1)

#endif /* BATTERY_A1141_H_ */
