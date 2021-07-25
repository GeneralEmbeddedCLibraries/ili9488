// Copyright (c) 2021 Ziga Miklosic
// All Rights Reserved
// This software is under MIT licence (https://opensource.org/licenses/MIT)
////////////////////////////////////////////////////////////////////////////////
/**
*@file      ili9488_low_if.c
*@brief     Low level interface with ILI9488 chip
*@author    Ziga Miklosic
*@date      31.04.2021
*@version	V1.0.1
*/
////////////////////////////////////////////////////////////////////////////////
/**
*@addtogroup LOW_LEVEL_IF
* @{ <!-- BEGIN GROUP -->
*
* 	Low level interface with ILI9488 chip
*/
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "ili9488_low_if.h"
#include "../../ili9488_if.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

// CS
#define ILI9488_LOW_IF_CS_LOW()			( ili9488_if_set_cs( false ))
#define ILI9488_LOW_IF_CS_HIGH()		( ili9488_if_set_cs( true ))

// DC
#define ILI9488_LOW_IF_DC_COMMAND()		( ili9488_if_set_dc( false ))
#define ILI9488_LOW_IF_DC_DATA()		( ili9488_if_set_dc( true ))

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Function prototypes
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**
*		Write to LCD register
*
*	If sending only command, size shall be 0. Add size only
*	for data bytes.
*
* @param[in]	cmd 		- Command name
* @param[in]	tx_data 	- Pointer to transmit data
* @param[in]	size 		- Number of data to transmit
* @return		status 		- Either Ok or Error
*/
////////////////////////////////////////////////////////////////////////////////
ili9488_status_t ili9488_low_if_write_register(const ili9488_cmd_t cmd, const uint8_t * const tx_data, const uint32_t size)
{
	ili9488_status_t 	status 	= eILI9488_OK;
	uint8_t 			command = cmd;

	// Set CS & DC
	ILI9488_LOW_IF_CS_LOW();
	ILI9488_LOW_IF_DC_COMMAND();

	// Send command
	if ( eILI9488_OK != ili9488_if_spi_transmit( &command, 1U ))
	{
		status = eILI9488_ERROR;
	}

	// Command send OK
	else
	{
		// In case of parameters send them as well
		if ( size > 0 )
		{
			// Data transmit
			ILI9488_LOW_IF_DC_DATA();

			if ( eILI9488_OK != ili9488_if_spi_transmit((uint8_t*) tx_data, size ))
			{
				status = eILI9488_ERROR;
			}
		}
	}

	// Set CS
	ILI9488_LOW_IF_CS_HIGH();

	return status;
}

////////////////////////////////////////////////////////////////////////////////
/**
*		Read from LCD register
*
* @param[in]	cmd 	- Command name
* @param[in]	rx_data - Pointer to read data
* @param[in]	size 	- Number of data to read
* @return		status 	- Either Ok or Error
*/
////////////////////////////////////////////////////////////////////////////////
ili9488_status_t ili9488_low_if_read_register(const ili9488_cmd_t cmd, uint8_t * const rx_data, const uint32_t size)
{
	ili9488_status_t 	status 	= eILI9488_OK;
	uint8_t 			command = cmd;

	// Set CS & DC
	ILI9488_LOW_IF_CS_LOW();
	ILI9488_LOW_IF_DC_COMMAND();

	// Send command
	if ( eILI9488_OK != ili9488_if_spi_transmit( &command, 1U ))
	{
		status = eILI9488_ERROR;
	}

	// Command send OK
	else
	{
		// In case of parameters send them as well
		if ( size > 0 )
		{
			// Data transmit
			ILI9488_LOW_IF_DC_DATA();

			if ( eILI9488_OK != ili9488_if_spi_receive( rx_data, size ))
			{
				status = eILI9488_ERROR;
			}
		}
	}

	// Set CS
	ILI9488_LOW_IF_CS_HIGH();

	return status;
}

////////////////////////////////////////////////////////////////////////////////
/**
*		Write to RGB code to GRAM
*
*	This function writes constant RGB code and write size
*	number pixels.
*
* @param[in]	p_rgb 	- Pointer to rgb code
* @param[in]	size 	- Number of data to transmit
* @return		status 	- Either Ok or Error
*/
////////////////////////////////////////////////////////////////////////////////
ili9488_status_t ili9488_low_if_write_rgb_to_gram(const ili9488_rgb_t * const p_rgb, const uint32_t size)
{
			ili9488_status_t 	status 	= eILI9488_OK;
	const 	uint8_t 		 	cmd 	= eILI9488_WRITE_MEM_CMD;
			uint32_t 			i		= 0UL;

	// Set CS & DC
	ILI9488_LOW_IF_CS_LOW();
	ILI9488_LOW_IF_DC_COMMAND();

	// Send command
	if ( eILI9488_OK != ili9488_if_spi_transmit((uint8_t*) &cmd, 1U ))
	{
		status = eILI9488_ERROR;
	}
	else
	{
		// In case of parameters send them as well
		if ( size > 0 )
		{
			// Data transmit
			ILI9488_LOW_IF_DC_DATA();

			for ( i = 0; i < size; i++ )
			{
				ili9488_if_spi_transmit((uint8_t*) p_rgb, 3U );
			}
		}
	}

	// Set CS
	ILI9488_LOW_IF_CS_HIGH();

	return status;
}

////////////////////////////////////////////////////////////////////////////////
/**
* @} <!-- END GROUP -->
*/
////////////////////////////////////////////////////////////////////////////////
