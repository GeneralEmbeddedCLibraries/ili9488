// Copyright (c) 2021 Ziga Miklosic
// All Rights Reserved
// This software is under MIT licence (https://opensource.org/licenses/MIT)
////////////////////////////////////////////////////////////////////////////////
/**
*@file      ili9488.h
*@brief     API for ILI9488 chipset
*@author    Ziga Miklosic
*@date      31.04.2021
*@version	V1.0.2
*/
////////////////////////////////////////////////////////////////////////////////
/**
*@addtogroup ILI9488_API
* @{ <!-- BEGIN GROUP -->
*
* 	Application functions for ILI9488
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef _ILI9488_H_
#define _ILI9488_H_

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "project_config.h"
#include <stdint.h>
#include <stdbool.h>

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

/**
 * 	Module version
 */
#define ILI9488_VER_MAJOR		( 1 )
#define ILI9488_VER_MINOR		( 0 )
#define ILI9488_VER_DEVELOP		( 2 )

// General status
typedef enum
{
	eILI9488_OK 		= 0x00,		/**<Normal operation */
	eILI9488_ERROR 		= 0x01,		/**<General error */
	eILI9488_ERROR_SPI	= 0x02,		/**<SPI interface error */
} ili9488_status_t;

// Colors
typedef enum
{
	eILI9488_COLOR_BLACK = 0,
	eILI9488_COLOR_BLUE,
	eILI9488_COLOR_GREEN,
	eILI9488_COLOR_TURQUOISE,
	eILI9488_COLOR_RED,
	eILI9488_COLOR_PURPLE,
	eILI9488_COLOR_YELLOW,
	eILI9488_COLOR_WHITE,
	eILI9488_COLOR_LIGHT_GRAY,
	eILI9488_COLOR_GRAY,

} ili9488_color_t;

// Font options
typedef enum
{
	eILI9488_FONT_8 = 0,
	eILI9488_FONT_12,
	eILI9488_FONT_16,
	eILI9488_FONT_20,
	eILI9488_FONT_24,

	eILI9488_FONT_NUM_OF,
} ili9488_font_opt_t;

// Rectangle attributes
typedef struct
{
	// Position of rectangle
	struct
	{
		uint16_t start_page;
		uint16_t start_col;
		uint16_t page_size;
		uint16_t col_size;
	} position;

	// Rounded corners
	struct
	{
		bool	enable;
		uint8_t	radius;
	} rounded;

	// Filled rectangle
	struct
	{
		bool			enable;
		ili9488_color_t color;
	} fill;

	// Rectangle with border
	struct
	{
		bool			enable;
		ili9488_color_t color;
		uint8_t			width;
	} border;

} ili9488_rect_attr_t;

// Circle attributes
typedef struct
{
	// Position & size of circle
	struct
	{
		uint16_t start_page;
		uint16_t start_col;
		uint8_t radius;
	} position;

	// Filled circle
	struct
	{
		bool			enable;
		ili9488_color_t color;
	} fill;

	// Border
	struct
	{
		bool 			enable;
		ili9488_color_t	color;
		uint8_t			width;
	} border;

} ili9488_circ_attr_t;

////////////////////////////////////////////////////////////////////////////////
// Function Prototypes
////////////////////////////////////////////////////////////////////////////////

// General functions
ili9488_status_t 	ili9488_init			(void);
bool				ili9488_is_init			(void);
ili9488_status_t 	ili9488_set_backlight	(const float32_t brightness);
ili9488_status_t 	ili9488_get_backlight	(float32_t * const p_brightness);

// Graphics functions
ili9488_status_t 	ili9488_set_background	(const ili9488_color_t color);
ili9488_status_t	ili9488_draw_rectangle	(const ili9488_rect_attr_t * const p_rectanegle_attr);
ili9488_status_t	ili9488_draw_circle		(const ili9488_circ_attr_t * const p_circ_attr);

// Text functions
ili9488_status_t 	ili9488_set_string_pen	(const ili9488_color_t fg_color, const ili9488_color_t bg_color, const ili9488_font_opt_t font_opt);
ili9488_status_t 	ili9488_set_string		(const char* str, const uint16_t page, const uint16_t col);
ili9488_status_t	ili9488_set_cursor		(const uint16_t page, const uint16_t col);
void				ili9488_get_cursor		(uint16_t * const p_page, uint16_t * const p_col);
ili9488_status_t	ili9488_printf			(const char *args, ...);

uint8_t	ili9488_get_font_width	(void);
uint8_t	ili9488_get_font_height	(void);

////////////////////////////////////////////////////////////////////////////////
/**
* @} <!-- END GROUP -->
*/
////////////////////////////////////////////////////////////////////////////////
#endif // _ILI9488_H_
