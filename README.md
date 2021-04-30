# ILI9488 MODULE
This module contains C library for display driver for 3.5" SPI TFT 480x320 with resistive touch.
Module was written and tested on STM32F746 Nucleo board, using STM32CubeIDE. 

## USAGE
### 1. Setting up configuration
Display driver is fully configurable via **ili9488_cfg.h** file. Low level interface shall be change only in **ili9488_if.c/.h** files.

##### NOTE: When debug mode is enabled user should provide debug communication port by the choice!

### 2. Low level interface

- User shall change **ili9488_if.c/.h** file between USER_CODE_BEGIN and USER_CODE_END sections

### 3. Includes
  Only top level modules are needed, therefore single include should be provided. E.g.:
```
  #include "ili9488.h"
```

### 4. Initialization
- Initialization of display driver should be done only once in project.
- User can access initilization status by calling **ili9488_is_init()** function.
- Example of initialization routine:
```
  // Init display controller
  if ( eILI9488_OK != ili9488_init() )
  { 
    // Initialization failed, further actions here...
  }

```

## DISPLAY API

### Colors
Driver supports following colors:

```
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
```

### Background set
- Function:
``` 
  //////////////////////////////////////////////////////////////
  /*
  *			Set display background
  *
  *	param:		color - Color of background
  *	return:		status - Status of operation
  */
  //////////////////////////////////////////////////////////////
  ili9488_status_t ili9488_set_background(const ili9488_color_t color)
```

- Example:

``` 
  // Set black background 
  ili9488_set_background( eILI9488_COLOR_BLACK );
```

### Rectangle drawing
Driver supports four types of rectangle: simple, simple with border, rounded and rounded with border. Before drawing rectangle attributes must be determined. Examples of all four types of rectangles are demonstrated below:

- Function:
```
  //////////////////////////////////////////////////////////////
  /*
  *			Draw rectangle
  *
  *	param:		p_rectanegle_attr - Pointer to rectangle attributes
  *	return:		status 	- Status of operation
  */
  //////////////////////////////////////////////////////////////
  ili9488_status_t ili9488_draw_rectangle(const ili9488_rect_attr_t * const p_rectanegle_attr)
```

- Example:

```
  // Rectangle attributes
  ili9488_rect_attr_t rect_attr;

  // -------------------------------------------
  //	RECTANGLE DRAWINGS
  // -------------------------------------------

  // 1. Simple filled rectangle
  rect_attr.position.start_page = 50;
  rect_attr.position.start_col  = 10;
  rect_attr.position.page_size  = 100;
  rect_attr.position.col_size   = 50;

  rect_attr.rounded.enable      = false;
  rect_attr.rounded.radius      = 0;

  rect_attr.fill.enable         = true;
  rect_attr.fill.color          = eILI9488_COLOR_BLUE;

  rect_attr.border.enable       = false;
  rect_attr.border.width        = 0;
  rect_attr.border.color        = eILI9488_COLOR_BLACK;

  ili9488_draw_rectangle( &rect_attr );


  // 2. Simple with border rectangle
  rect_attr.position.start_page = 270;
  rect_attr.position.start_col  = 10;
  rect_attr.position.page_size  = 100;
  rect_attr.position.col_size   = 50;

  rect_attr.rounded.enable      = false;
  rect_attr.rounded.radius      = 0;

  rect_attr.fill.enable         = true;
  rect_attr.fill.color          = eILI9488_COLOR_BLUE;

  rect_attr.border.enable       = true;
  rect_attr.border.width        = 8;
  rect_attr.border.color        = eILI9488_COLOR_WHITE;

  ili9488_draw_rectangle( &rect_attr );


  // 3. Round filled rectangle
  rect_attr.position.start_page = 50;
  rect_attr.position.start_col  = 150;
  rect_attr.position.page_size  = 100;
  rect_attr.position.col_size   = 140;

  rect_attr.rounded.enable      = true;
  rect_attr.rounded.radius      = 9;

  rect_attr.fill.enable         = true;
  rect_attr.fill.color          = eILI9488_COLOR_PURPLE;

  rect_attr.border.enable       = false;
  rect_attr.border.width        = 0;
  rect_attr.border.color        = eILI9488_COLOR_BLACK;

  ili9488_draw_rectangle( &rect_attr );


  // 4. Round with border rectangle
  rect_attr.position.start_page = 270;
  rect_attr.position.start_col  = 150;
  rect_attr.position.page_size  = 50;
  rect_attr.position.col_size   = 75;

  rect_attr.rounded.enable      = true;
  rect_attr.rounded.radius      = 13;

  rect_attr.fill.enable         = true;
  rect_attr.fill.color          = eILI9488_COLOR_RED;

  rect_attr.border.enable       = true;
  rect_attr.border.width        = 3;
  rect_attr.border.color        = eILI9488_COLOR_YELLOW;

  ili9488_draw_rectangle( &rect_attr );
```


### Circle drawing
Driver supports two kinds of circle drawings: simple and with border. Similar to rectangle drawing, attributes for circle must be set first. Both types of circle drawing are shown below: 

- Function:
```
  //////////////////////////////////////////////////////////////
  /*
  *			Draw circle
  *
  *	param: 		p_circle_attr 	- Pointer to circle attributes
  *	return:		status 			- Status of operation
  */
  //////////////////////////////////////////////////////////////
  ili9488_status_t ili9488_draw_circle(const ili9488_circ_attr_t * const p_circle_attr)
```

- Example:

```
  // Circle attributes
  ili9488_circ_attr_t circ_attr;

  // -------------------------------------------
  //	CIRCLE DRAWINGS
  // -------------------------------------------

  // 1. Simple circle
  circ_attr.position.start_page = 50;
  circ_attr.position.start_col  = 260;
  circ_attr.position.radius     = 25;

  circ_attr.border.enable       = false;
  circ_attr.border.width        = 0;
  circ_attr.border.color        = eILI9488_COLOR_BLACK;

  circ_attr.fill.enable         = true;
  circ_attr.fill.color          = eILI9488_COLOR_TURQUOISE;

  ili9488_draw_circle( &circ_attr );


  // 2. Circle with border
  circ_attr.position.start_page = 250;
  circ_attr.position.start_col  = 260;
  circ_attr.position.radius     = 50;

  circ_attr.border.enable       = true;
  circ_attr.border.width        = 7;
  circ_attr.border.color        = eILI9488_COLOR_GREEN;

  circ_attr.fill.enable         = true;
  circ_attr.fill.color          = eILI9488_COLOR_LIGHT_GRAY;

  ili9488_draw_circle( &circ_attr );
```

### String drawing
For drawing string onto display string pen should be set first. String pen defines font, foreground and background color of string. Five different font sizes are available (from 8pt to 24pt).

- Function:
```
  //////////////////////////////////////////////////////////////
  /*
  *			Set string pen
  *
  *	param:		fg_color - Foreground color
  *	param:		bg_color - Background color
  *	param:		font_opt - Font of choise
  *	return:		status - Always OK
  */
  //////////////////////////////////////////////////////////////
  ili9488_status_t ili9488_set_string_pen(const ili9488_color_t fg_color, const ili9488_color_t bg_color, const ili9488_font_opt_t font_opt)

  //////////////////////////////////////////////////////////////
  /*
  *			Display string
  *
  *	param:		str - String to display
  *	param:		page - Start page
  *	param:		col - Start column
  *	return:		status - Either Ok or Error
  */
  //////////////////////////////////////////////////////////////
  ili9488_status_t ili9488_set_string(const char* str, const uint16_t page, const uint16_t col)
```

- Example:

```
  // Set string pen
  ili9488_set_string_pen( eILI9488_COLOR_RED, eILI9488_COLOR_WHITE, eILI9488_FONT_20 );

  // Draw string 
  ili9488_set_string( "HelloWorld", 100, 120 );
```


### Formated string drawing
Driver also supports formated string drawing. Similar as drawing a string first string pen and cursor must be set. Cursor defines initial coordinates of formated string.

- Function:

```
  //////////////////////////////////////////////////////////////
  /*
  *			Set cursor for printf functionality
  *
  *	param:		page 	- Cursor page (x) coordinate
  *	param:		col 	- Cursor column (y) coordinate
  *	return:		status 	- Status of operation
  */
  //////////////////////////////////////////////////////////////
  ili9488_status_t ili9488_set_cursor(const uint16_t page, const uint16_t col)

  //////////////////////////////////////////////////////////////
  /*
  *			Print formated string to display
  *
  *	param:		format - Formated string
  *	return:		status 	- Status of operation
  */
  //////////////////////////////////////////////////////////////
  ili9488_status_t ili9488_printf(const char *format, ...)
```

- Example:

```	
  // Set string pen
  ili9488_set_string_pen( eILI9488_COLOR_RED, eILI9488_COLOR_WHITE, eILI9488_FONT_20 );

  // Set cursor
  ili9488_set_cursor( 20, 20 );

  // Draw formated string
  ili9488_printf( "%d", HAL_GetTick() );
```
Printf function also supports linebreak ('\n' or '\r')
**NOTE: Formated string uses sprintf, thus use it with care!**

### Backlight brigthness
Display backlight brigthness setup.
- Function:
```
  //////////////////////////////////////////////////////////////
  /*
  *			Set up display backlight
  *
  *	param: 		brightness 	- Brightness value from 0.0 - 1.0
  *	return:		status 		- Status of operation
  */
  //////////////////////////////////////////////////////////////
  ili9488_status_t ili9488_set_backlight(const float32_t brightness)
```

- Example:
```
  // Set 90% of full brigtness
  ili9488_set_backlight( 0.9f );
```

- NOTE: Startup value of brightness can be changed in ili9488_config.h file (check ILI9488_LED_STARTUP_VAL).

