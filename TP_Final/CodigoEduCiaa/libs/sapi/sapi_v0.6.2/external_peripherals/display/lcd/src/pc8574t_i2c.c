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
 *
 */

/* Date: 2017-12-05 */

/*==================[inlcusiones]============================================*/

#include "sapi.h"        // <= Biblioteca sAPI
#include "sapi_lcd.h"
#include "pc8574t_i2c.h"

/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/

static uint8_t pcf8574TGpioPortDirections = 0x00;
static uint8_t pcf8574TGpioPortValue = 0x00;
static uint8_t pcf8574TI2cAddress = PCF8574T_I2C_ADDRESS;

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

static void pcf8574TGpioPortInit( uint8_t directions );
static void pcf8574TGpioPortWrite( uint8_t portValue );
static uint8_t pcf8574TGpioPortRead( void );
static void pcf8574TGpioInit( pcf8574T_gpio_t pin,
                              pcf8574T_gpioDirection_t direction );

/*==================[declaraciones de funciones externas]====================*/

void pcf8574TInit( uint8_t i2c, uint8_t i2cAddress );
bool_t pcf8574TGpioRead( pcf8574T_gpio_t pin );
void pcf8574TGpioWrite( pcf8574T_gpio_t pin, bool_t value );

/*==================[definiciones de funciones internas]=====================*/

static void pcf8574TGpioPortInit( uint8_t directions )
{
   pcf8574TGpioPortDirections = directions;
   i2cWrite( I2C0, pcf8574TI2cAddress, &directions, 1, TRUE );
}

static void pcf8574TGpioPortWrite( uint8_t portValue )
{
   pcf8574TGpioPortValue = portValue;
   // Or with pcf8574TGpioPortDirections to keep pins initialized as inputs
   uint8_t transmitDataBuffer = portValue | pcf8574TGpioPortDirections;
   i2cWrite( I2C0, pcf8574TI2cAddress, &transmitDataBuffer, 1, TRUE );
}

static uint8_t pcf8574TGpioPortRead( void )
{
   //uint8_t dataToReadBuffer[1] = { 0 };
   uint8_t receiveDataBuffer = 0;
   i2cRead( I2C0, pcf8574TI2cAddress,
            &receiveDataBuffer, 1, TRUE );
}

static void pcf8574TGpioInit( pcf8574T_gpio_t pin,
                              pcf8574T_gpioDirection_t direction )
{
   uint8_t directions = pcf8574TGpioPortDirections;
   if( direction ) {
      directions |= (1<<pin);
   } else {
      directions &= ~(1<<pin);
   }
   pcf8574TGpioPortInit( directions );
}

/*==================[definiciones de funciones externas]=====================*/

void pcf8574TInit( uint8_t i2c, uint8_t i2cAddress )
{

   pcf8574TI2cAddress = i2cAddress;
//   i2cInit( I2C0, 100000 );

   pcf8574TGpioPortInit( 0x00 ); // Init all GPIOs as outputs
   pcf8574TGpioPortWrite( 0x00 ); // Init all as zeros
   /*
   while(true){
      pcf8574TGpioPortWrite( 0x00 );
      delay(2000);
      pcf8574TGpioPortWrite( 0xFF );
      delay(2000);
   }
   */
}

bool_t pcf8574TGpioRead( pcf8574T_gpio_t pin )
{
   return pcf8574TGpioPortRead() & (1<<pin);
}

void pcf8574TGpioWrite( pcf8574T_gpio_t pin, bool_t value )
{
   uint8_t portValue = pcf8574TGpioPortValue;
   if( value ) {
      portValue |= (1<<pin);
   } else {
      portValue &= ~(1<<pin);
   }
   pcf8574TGpioPortWrite( portValue );
}

/*==================[fin del archivo]========================================*/
