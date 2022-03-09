/*
 * audio_driver.c
 *
 *  Created on: 14. okt. 2021
 *      Author: Hans Erik Heggem
 */

#include <stdint.h>
#include "main.h"
#include "stm32L4xx_hal.h"
#include "audio_driver.h"
#include "tas2770.h"
#include "../i2c_port/i2c_port.h"

#define I2S_TX_TIMEOUT_MS 1000
#define AUDIO_I2C_TIMEOUT_MS 10000U

extern SAI_HandleTypeDef hsai_BlockA2;

HAL_StatusTypeDef audio_init()
{
	uint8_t txData[2];

    HAL_GPIO_WritePin(SOUND_ENABLE_GPIO_Port, SOUND_ENABLE_Pin, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(SOUND_ENABLE_GPIO_Port, SOUND_ENABLE_Pin, GPIO_PIN_SET);
    HAL_Delay(100);

	// Verify revision id and pg id
	txData[0] = 0x7d;
	if(i2c_port_write_read(TAS2770_I2C_SLAVE_ADDRESS, txData, 1, txData, 1, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
	{
		return HAL_ERROR;
	}
	uint8_t revision_id = (txData[0] & 0xf0) >> 4;
	uint8_t pg_id = txData[0] & 0x0f;

	if (revision_id != 0x02 || pg_id != 0x00)
	{
		return HAL_ERROR;
	}


		txData[0] = 0x00;
		txData[1] = 0x00;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		// Book-0
		txData[0] = 0x7f;
		txData[1] = 0x00;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x00;
		txData[1] = 0x00;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x01;
		txData[1] = 0x01;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		HAL_Delay(100);



		txData[0] = 0x00;
		txData[1] = 0x00;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x7f;
		txData[1] = 0x00;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x00;
		txData[1] = 0x00;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x02;
		txData[1] = 0x0e;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}


		txData[0] = 0x03;
		txData[1] = 0x0a;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x0a;
		txData[1] = 0x17;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x0b;
		txData[1] = 0x02;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x0c;
		txData[1] = 0x0a;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}


		txData[0] = 0x0e;
		txData[1] = 0xf3;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x12;
		txData[1] = 0x06;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x20;
		txData[1] = 0xfc;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x21;
		txData[1] = 0xb1;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x30;
		txData[1] = 0x05;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x32;
		txData[1] = 0x00;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x3c;
		txData[1] = 0x09;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x00;
		txData[1] = 0x00;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x7f;
		txData[1] = 0x00;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x00;
		txData[1] = 0x00;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x0c;
		txData[1] = 0x0a;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x0d;
		txData[1] = 0x10;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x0f;
		txData[1] = 0x02;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x10;
		txData[1] = 0x00;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x11;
		txData[1] = 0x04;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x12;
		txData[1] = 0x06;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x13;
		txData[1] = 0x07;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x14;
		txData[1] = 0x08;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x00;
		txData[1] = 0x00;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x7f;
		txData[1] = 0x00;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x00;
		txData[1] = 0x00;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x02;
		txData[1] = 0x0e;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x03;
		txData[1] = 0x0a;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x04;
		txData[1] = 0x01;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x05;
		txData[1] = 0x00;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x06;
		txData[1] = 0x00;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x07;
		txData[1] = 0x06;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x08;
		txData[1] = 0x00;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x09;
		txData[1] = 0x08;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x0b;
		txData[1] = 0x02;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x0e;
		txData[1] = 0xf3;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x15;
		txData[1] = 0x14;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x16;
		txData[1] = 0x76;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x17;
		txData[1] = 0x10;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x18;
		txData[1] = 0x6e;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x19;
		txData[1] = 0x1e;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x1a;
		txData[1] = 0x58;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x1b;
		txData[1] = 0x01;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x1c;
		txData[1] = 0x14;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x1d;
		txData[1] = 0x4e;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x74;
		txData[1] = 0x00;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x00;
		txData[1] = 0x00;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x7f;
		txData[1] = 0x00;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x00;
		txData[1] = 0x00;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x07;
		txData[1] = 0x06;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x0e;
		txData[1] = 0xf3;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x31;
		txData[1] = 0x00;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x00;
		txData[1] = 0x00;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x7f;
		txData[1] = 0x00;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x00;
		txData[1] = 0x00;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}

		txData[0] = 0x02;
		txData[1] = 0x0c;
		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
		{
			return HAL_ERROR;
		}


//		txData[0] = 0x02;
//		txData[1] = 0x00;
//		if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
//		{
//			return HAL_ERROR;
//		}




//	// Page-0
//	txData[0] = 0x00;
//	txData[1] = 0x00;
//	if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
//	{
//		return HAL_ERROR;
//	}
//
//	// Book-0
//	txData[0] = 0x7f;
//	txData[1] = 0x00;
//	if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
//	{
//		return HAL_ERROR;
//	}
//
//	txData[0] = 0x00;
//	txData[1] = 0x00;
//	if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
//	{
//		return HAL_ERROR;
//	}
//
//	txData[0] = 0x01;
//	txData[1] = 0x01;
//	if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
//	{
//		return HAL_ERROR;
//	}
//
//	HAL_Delay(100);
//
//	txData[0] = 0x00;
//	txData[1] = 0x00;
//	if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
//	{
//		return HAL_ERROR;
//	}
//
//	txData[0] = 0x7f;
//	txData[1] = 0x00;
//	if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
//	{
//		return HAL_ERROR;
//	}
//
//	txData[0] = 0x00;
//	txData[1] = 0x00;
//	if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
//	{
//		return HAL_ERROR;
//	}
//
//	txData[0] = 0x03;
//	txData[1] = 0x08;
//	if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
//	{
//		return HAL_ERROR;
//	}
//
//	txData[0] = 0x0a;
//	txData[1] = 0x17;
//	if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
//	{
//		return HAL_ERROR;
//	}
//
//	txData[0] = 0x0e;
//	txData[1] = 0xf3;
//	if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
//	{
//		return HAL_ERROR;
//	}
//
//	txData[0] = 0x32;
//	txData[1] = 0x00;
//	if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
//	{
//		return HAL_ERROR;
//	}
//
//	txData[0] = 0x3c;
//	txData[1] = 0x09;
//	if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
//	{
//		return HAL_ERROR;
//	}
//
//	txData[0] = 0x7e;
//	txData[1] = 0xaa;
//	if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
//	{
//		return HAL_ERROR;
//	}
//
//
//	txData[0] = 0x00;
//	txData[1] = 0x00;
//	if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
//	{
//		return HAL_ERROR;
//	}
//
//	// Book-0
//	txData[0] = 0x7f;
//	txData[1] = 0x00;
//	if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
//	{
//		return HAL_ERROR;
//	}
//
//	txData[0] = 0x00;
//	txData[1] = 0x01;
//	if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
//	{
//		return HAL_ERROR;
//	}




//	// Software Reset
//	txData[0] = 0x01;
//	txData[1] = 0x01;
//	if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
//	{
//		return HAL_ERROR;
//	}
//
//	HAL_Delay(100);
//
//	// sbclk to fs ratio = 32 / 8 TDM Slots
//	txData[0] = 0x3c;
//	txData[1] = 0b00001001;
//	if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
//	{
//		return HAL_ERROR;
//	}
//
//	// 48KHz, Auto TDM off, Frame start High to Low
//	txData[0] = 0x0a;
//	txData[1] = 0b00110110;
//	if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
//	{
//		return HAL_ERROR;
//	}
//
//	// TDM slot by address, Word = 16 bit, Frame = 16 bit
//	txData[0] = 0x0c;
//	txData[1] = 0b00000000;
//	if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
//	{
//		return HAL_ERROR;
//	}
//
//	// 21 dB gain
//	txData[0] = 0x03;
//	txData[1] = 0x14;
//	if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
//	{
//		return HAL_ERROR;
//	}
//
//	// power up audio playback with I,V enabled
//	txData[0] = 0x02;
//	txData[1] = 0x00;
//	if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
//	{
//		return HAL_ERROR;
//	}
//
//	HAL_Delay(100);
//
//	txData[0] = 0x77;
//	if(i2c_port_write_read(TAS2770_I2C_SLAVE_ADDRESS, txData, 1, txData, 1, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
//	{
//		return HAL_ERROR;
//	}
//	uint8_t fs_ratio = (txData[0] & 0b00011100) >> 2; // 05h = 96
//	uint8_t fs_rate_v = txData[0] & 0b00000011; // 011b = 44.1/48 KHz
//
//	txData[0] = 0x24;
//	if(i2c_port_write_read(TAS2770_I2C_SLAVE_ADDRESS, txData, 1, txData, 1, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
//	{
//		return HAL_ERROR;
//	}
//
//	if (txData[0] != 0x00)
//	{
////		return HAL_ERROR;
//	}
//
//	txData[0] = 0x25;
//	if(i2c_port_write_read(TAS2770_I2C_SLAVE_ADDRESS, txData, 1, txData, 1, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
//	{
//		return HAL_ERROR;
//	}
//
//	if (txData[0] != 0x00)
//	{
////		return HAL_ERROR;
//	}

	return HAL_OK;
}

HAL_StatusTypeDef audio_mute()
{
	uint8_t txData[2];

	// Set DVC Ramp Rate to 0.5 dB / 8 samples
	txData[0] = 0x07;
	txData[1] = 0x80;
	if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
	{
		return HAL_ERROR;
	}

	// Mute
	txData[0] = 0x02;
	txData[1] = 0x01;
	if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
	{
		return HAL_ERROR;
	}

	osDelay(100);
	return HAL_OK;
}

HAL_StatusTypeDef audio_unmute()
{
	uint8_t txData[2];

	// Set DVC Ramp Rate to 0.5 dB / 8 samples
	txData[0] = 0x07;
	txData[1] = 0x80;
	if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
	{
		return HAL_ERROR;
	}

	// Un-mute
	txData[0] = 0x02;
	txData[1] = 0x00;
	if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
	{
		return HAL_ERROR;
	}

	osDelay(100);
	return HAL_OK;
}

HAL_StatusTypeDef audio_sleep()
{
	audio_mute();
	uint8_t txData[2];

	// Software shutdown
	txData[0] = 0x02;
	txData[1] = 0x02;
	if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
	{
		return HAL_ERROR;
	}

	return HAL_OK;
}

HAL_StatusTypeDef audio_wakeup()
{
	if (audio_mute() != HAL_OK) {
		return HAL_ERROR;
	}

	uint8_t txData[2];

	// Set DVC Ramp Rate to 0.5 dB / 8 samples
	txData[0] = 0x07;
	txData[1] = 0x80;
	if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
	{
		return HAL_ERROR;
	}

	// Take device out of low-power shutdown
	txData[0] = 0x02;
	txData[1] = 0x01;
	if(i2c_port_write(TAS2770_I2C_SLAVE_ADDRESS, txData, 2, AUDIO_I2C_TIMEOUT_MS) != I2C_PORT_OK)
	{
		return HAL_ERROR;
	}

	osDelay(100);
	return audio_unmute();
}

HAL_StatusTypeDef audio_play(int16_t *buffer, uint16_t buflen)
{
	return HAL_SAI_Transmit(&hsai_BlockA2, (uint8_t*)buffer, buflen, I2S_TX_TIMEOUT_MS);
}
