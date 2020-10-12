/*=============================================================================
 * Author: ctrinidad
 * Date: 2020/09/27
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "main.h"

#include "teclas.h"
#include "sapi.h"

/*=====[Definition macros of private constants]==============================*/

#define V_CANT_DIG 3
#define I_CANT_DIG 4

#define WELCOME_1  "+------------------+"
#define WELCOME_2  "|  Trabajo  Final  |"
#define WELCOME_3  "|       PCSE       |"
#define WELCOME_4  "+------------------+"

#define PPAL_1  "Caracterizando trafo"
#define PPAL_2  " Midiendo Primario  "
#define PPAL_3  "Vp=    V  Ip=     mA"
#define PPAL_4  "Vs=    V  Is=     mA"

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

char ConvertBuff[10];
#define N_TECLAS 4
tTecla tecla[N_TECLAS];
delay_t delay1, delay2;
uint32_t Vp = 0, Vs = 0, Ip = 0, Is = 0;

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

int main( void )
{
   lcd_config_t lcd_config;

   // ----- Setup -----------------------------------
   boardInit();

   delay( LCD_STARTUP_WAIT_MS );   // Wait for stable power (some LCD need that)

   // Inicializar LCD de 20x2 (caracteres x lineas) con cada caracter de 5x8 pixeles
   lcd_config.lineWidth = 20 ;
   lcd_config.amountOfLines = 4 ;
   lcd_config.lcd_set = LCD_SET_4BITMODE_2LINE;
   lcd_config.lcd_control = LCD_CONTROL_CURSOROFF_BLINKOFF;
   lcd_config.lcd_entry_mode = LCD_ENTRY_MODE_LEFT;

   lcdInit( &lcd_config );
   lcdSendString(WELCOME_1);
   lcdSendString(WELCOME_2);
   lcdSendString(WELCOME_3);
   lcdSendString(WELCOME_4);

   delay(3000);

   lcdGoToXY(0,0);
   lcdSendString(PPAL_1);
   lcdSendString(PPAL_2);
   lcdSendString(PPAL_3);
   lcdSendString(PPAL_4);

   /* Inicializar Retardo no bloqueante con tiempo en ms */
   delayConfig( &delay1, 1000 );
   delayConfig( &delay2, 200 );

   tecla_init( TEC1, &tecla[0] );
   tecla_init( TEC2, &tecla[1] );
   tecla_init( TEC3, &tecla[2] );
   tecla_init( TEC4, &tecla[3] );

   // ----- Repeat for ever -------------------------
   while( true ) {

	  fsmButtonUpdate( &tecla[0] );
	  fsmButtonUpdate( &tecla[1] );
	  fsmButtonUpdate( &tecla[2] );
	  fsmButtonUpdate( &tecla[3] );

	  if ( delayRead( &delay2 ) ){
		  if(tecla[0].fsmButtonState == BUTTON_DOWN) {
			  gpioWrite(LED, 1);
			  Vp += 10;
			  if (Vp > 999) Vp = 0;
		  } else
		  {
			  gpioWrite(LED, 0);
		  }

		  if(tecla[1].fsmButtonState == BUTTON_DOWN) {
			  gpioWrite(LED1, 1);
			  Ip += 20;
			  if (Ip > 9999) Ip = 0;
		  } else
		  {
			  gpioWrite(LED1, 0);
		  }

		  if(tecla[2].fsmButtonState == BUTTON_DOWN) {
			  gpioWrite(LED2, 1);
			  Vs += 10;
			  if (Vs > 999) Vs = 0;
		  } else
		  {
			  gpioWrite(LED2, 0);
		  }

		  if(tecla[3].fsmButtonState == BUTTON_DOWN) {
			  gpioWrite(LED3, 1);
			  Is += 30;
			  if (Is > 9999) Is = 0;
		  } else
		  {
			  gpioWrite(LED3, 0);
		  }
	  }

      /* delayRead retorna TRUE cuando se cumple el tiempo de retardo */
      if ( delayRead( &delay1 ) ){
    	  // Tension Primaria
    	  lcdGoToXY(4,2);
    	  lcdSendIntFixedDigit( Vp, V_CANT_DIG, 0 );
    	  // Corriente Primaria
    	  lcdGoToXY(14,2);
    	  lcdSendIntFixedDigit( Ip, I_CANT_DIG, 0 );
    	  // Tension Secundaria
    	  lcdGoToXY(3,3);
		  lcdSendIntFixedDigit( Vs, V_CANT_DIG, 1 );
		  // Corriente Secundaria
		  lcdGoToXY(14,3);
		  lcdSendIntFixedDigit( Is, I_CANT_DIG, 0 );
      }
   }

   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not called by any Operating System, as in the 
   // case of a PC program.
   return 0;
}






