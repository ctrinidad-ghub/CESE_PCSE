/*
 * lcdBoard.h
 *
 *  Created on: 26 sep. 2020
 *      Author: Cristian
 */

#ifndef INC_LCDBOARD_H_
#define INC_LCDBOARD_H_

#include "sapi.h"        // <= Biblioteca sAPI
#include "sapi_lcd.h"
#include "pc8574t_i2c.h"

//#define LCD_HD44780_I2C_PCF8574T

// LCD Delay HAL
inline void lcdDelay_ms( uint32_t time ){
	delayInaccurateMs(time);
}
inline void lcdDelay_us( uint32_t time ){
	delayInaccurateUs(time);
}
#define lcdCommandDelay()           lcdDelay_us(LCD_CMD_WAIT_US)
#define lcdDataDelay()              lcdDelay_us(LCD_CMD_WAIT_US)

#ifdef LCD_HD44780_I2C_PCF8574T
   // Configure LCD I2C Pin positions
   #define LCD_HD44780_D7          7 // Data bit 7.
   #define LCD_HD44780_D6          6 // Data bit 4.
   #define LCD_HD44780_D5          5 // Data bit 5.
   #define LCD_HD44780_D4          4 // Data bit 4.
   #define LCD_HD44780_BACKLIGHT   3 // Backlight. LCD backlight anode.
   #define LCD_HD44780_EN          2 // Enable bit.
   #define LCD_HD44780_RW          1 // Read/Write bit. R/W = 0 for write, R/W = 1 for read (LCD_RW pin connected to GND).
   #define LCD_HD44780_RS          0 // Register select bit. RS = 0 to select command register, RS = 1 to select data register.
#else
	#if (BOARD == ciaa_sim_ia32)
	   #error CIAA-SIM_IA32 not supported yet!
	#elif (BOARD == ciaa_sim_ia64)
	   #error CIAA-SIM_IA64 not supported yet!
	#elif (BOARD == ciaa_nxp)
		// Configure LCD pins
		#define LCD_HD44780_D7          GPIO3    // Data bit 7.
		#define LCD_HD44780_D6          GPIO2    // Data bit 4.
		#define LCD_HD44780_D5          GPIO1    // Data bit 5.
		#define LCD_HD44780_D4          GPIO0    // Data bit 4.
		#define LCD_HD44780_BACKLIGHT   SPI_MISO // Backlight.
		#define LCD_HD44780_EN          GPIO8    // Enable bit.
		#define LCD_HD44780_RW          GND      // Read/Write bit. R/W = 0 for write, R/W = 1 for read (LCD_RW pin connected to GND).
		#define LCD_HD44780_RS          GPIO7    // Register select bit. RS = 0 to select command register, RS = 1 to select data register.
		#define LCD_HD44780_RST         GPIO7    // Reset.
	#elif (BOARD == edu_ciaa_nxp)
		// Configure LCD pins
		#define LCD_HD44780_D7          LCD4   // Data bit 7.
		#define LCD_HD44780_D6          LCD3   // Data bit 4.
		#define LCD_HD44780_D5          LCD2   // Data bit 5.
		#define LCD_HD44780_D4          LCD1   // Data bit 4.
		#define LCD_HD44780_D3          GPIO0  // Data bit 3.
		#define LCD_HD44780_D2          GPIO2  // Data bit 2.
		#define LCD_HD44780_D1          GPIO4  // Data bit 1.
		#define LCD_HD44780_D0          GPIO6  // Data bit 0.
		#define LCD_HD44780_BACKLIGHT   GPIO0  // Backlight.
		#define LCD_HD44780_EN          LCDEN  // Enable bit.
		#define LCD_HD44780_RW          GND    // Read/Write bit. R/W = 0 for write, R/W = 1 for read (LCD_RW pin connected to GND).
		#define LCD_HD44780_RS          LCDRS  // Register select bit. RS = 0 to select command register, RS = 1 to select data register.
        #define LCD_HD44780_RST         GPIO1    // Reset.
	#elif (BOARD == ciaa_fsl)
	   #error CIAA-FSL not supported yet!
	#elif (BOARD == ciaa_pic)
	   #error CIAA-PIC not supported yet!
	#elif (BOARD == pico_ciaa)
	   #error picoCIAA not supported yet!
	#elif (BOARD == ciaa_leon3_fpga_nfp)
	   #error CIAA-LEON3-FPGA-NFP not supported yet!
	#elif (BOARD == ciaa_z3r0)
	   #error CIAA-Z3R0 not supported yet!
	#elif (BOARD == ciaa_7st)
	   #error CIAA-7-ST not supported yet!
	#endif
#endif

// GPIO
// LCD GPIO HAL
#define lcdInitPinAsOutput(pin)     gpioInit( (pin), GPIO_OUTPUT )

#ifdef LCD_HD44780_I2C_PCF8574T
	#define lcdPinSet( pin, status )    pcf8574TGpioWrite( pin, status );
#else
	#define lcdPinSet( pin, status )    gpioWrite( pin, status );
#endif

inline void lcdRSClear(void){
	lcdPinSet( LCD_HD44780_RS, OFF );
}

inline void lcdRSSet(void){
	lcdPinSet( LCD_HD44780_RS, ON );
}

inline void lcdENSet(void){
	lcdPinSet( LCD_HD44780_EN, ON );
}

inline void lcdENClear(void){
	lcdPinSet( LCD_HD44780_EN, OFF );
}

inline void lcdRWClear( void ) {
	lcdPinSet( LCD_HD44780_RW, OFF );
};

inline void lcdBoardInit( lcd_set_t lcd_set )
{
#ifdef LCD_HD44780_I2C_PCF8574T
   // Init I2C
   pcf8574TInit( I2C0, PCF8574T_I2C_ADDRESS );
   lcdPinSet( LCD_HD44780_BACKLIGHT, ON );
//   delay(100);
#else
	// Configure LCD Pins as Outputs
	lcdInitPinAsOutput( LCD_HD44780_RST );
	lcdInitPinAsOutput( LCD_HD44780_RS );
	lcdInitPinAsOutput( LCD_HD44780_RW );
	lcdInitPinAsOutput( LCD_HD44780_EN );
	if (lcd_set & LCD_8BITMODE) {
		lcdInitPinAsOutput( LCD_HD44780_D0 );
		lcdInitPinAsOutput( LCD_HD44780_D1 );
		lcdInitPinAsOutput( LCD_HD44780_D2 );
		lcdInitPinAsOutput( LCD_HD44780_D3 );
	}
	lcdInitPinAsOutput( LCD_HD44780_D4 );
	lcdInitPinAsOutput( LCD_HD44780_D5 );
	lcdInitPinAsOutput( LCD_HD44780_D6 );
	lcdInitPinAsOutput( LCD_HD44780_D7 );
#endif
}

inline void lcdSendNibble( uint8_t nibble )
{
   lcdPinSet( LCD_HD44780_D7, ( nibble & 0x80 ) );
   lcdPinSet( LCD_HD44780_D6, ( nibble & 0x40 ) );
   lcdPinSet( LCD_HD44780_D5, ( nibble & 0x20 ) );
   lcdPinSet( LCD_HD44780_D4, ( nibble & 0x10 ) );
}

inline void lcdSendPort( uint8_t data )
{
// TODO: verificar si el PCF8574T tiene compatibilidad para 8 pines
#ifndef LCD_HD44780_I2C_PCF8574T
   lcdSendNibble( data & 0xF0 );
   lcdPinSet( LCD_HD44780_D3, ( data & 0x08 ) );
   lcdPinSet( LCD_HD44780_D2, ( data & 0x04 ) );
   lcdPinSet( LCD_HD44780_D1, ( data & 0x02 ) );
   lcdPinSet( LCD_HD44780_D0, ( data & 0x01 ) );
#endif
}

#endif /* INC_LCDBOARD_H_ */
