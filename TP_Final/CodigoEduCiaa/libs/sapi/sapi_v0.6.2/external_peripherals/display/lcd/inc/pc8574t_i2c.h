/* Copyright 2017, Eric Pernia.
 * All rights reserved.
 *
 * This file is part sAPI library for microcontrollers.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/* Date: 2017-12-05 */

#ifndef _PC8574T_I2C_LCD_H_
#define _PC8574T_I2C_LCD_H_

/*==================[inclusions]=============================================*/

#include "sapi.h"        // <= Biblioteca sAPI
#include "sapi_lcd.h"

/*==================[c++]====================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

#define PCF8574T_I2C_A0           1 // 1 connected to VDD, 0 to VSS
#define PCF8574T_I2C_A1           1 // 1 connected to VDD, 0 to VSS
#define PCF8574T_I2C_A2           1 // 1 connected to VDD, 0 to VSS

#define PCF8574T_I2C_BASE         0x20 // 0x40(fixed)
#define PCF8574T_I2C_ADDRESS      ( PCF8574T_I2C_BASE | ((PCF8574T_I2C_A2)<<2) | ((PCF8574T_I2C_A1)<<1) | PCF8574T_I2C_A0 )

/*==================[typedef]================================================*/

typedef enum{
   PCF8574T_P0 = (1<<0),
   PCF8574T_P1 = (1<<1),
   PCF8574T_P2 = (1<<2),
   PCF8574T_P3 = (1<<3),
   PCF8574T_P4 = (1<<4),
   PCF8574T_P5 = (1<<5),
   PCF8574T_P6 = (1<<6),
   PCF8574T_P7 = (1<<7),
} pcf8574T_gpio_t;

typedef enum{
   PCF8574_GPIO_INPUT = 1,
   PCF8574_GPIO_OUTPUT = 0,
} pcf8574T_gpioDirection_t;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

void pcf8574TInit( uint8_t i2c, uint8_t i2cAddress );
static uint8_t pcf8574TGpioPortRead( void );
bool_t pcf8574TGpioRead( pcf8574T_gpio_t pin );
void pcf8574TGpioWrite( pcf8574T_gpio_t pin, bool_t value );

/*==================[c++]====================================================*/
#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* _PC8574T_I2C_LCD_H_ */

