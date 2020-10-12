/*=============================================================================
 * Copyright (c) 2020, Martin N. Menendez <menendezmartin81@gmail.com>
 * All rights reserved.
 * License: Free
 * Date: 2020/09/03
 * Version: v1.1
 *===========================================================================*/
#ifndef _TIPOS_H_
#define _TIPOS_H_

#include "sapi.h"

//#define CANT	4

typedef enum
{
    STATE_BUTTON_UP,
    STATE_BUTTON_DOWN,
    STATE_BUTTON_FALLING,
    STATE_BUTTON_RISING
} fsmButtonState_t;

typedef struct
{
	gpioMap_t tecla;			//config

	fsmButtonState_t fsmButtonState;//variables

	uint8_t contFalling  ;		//variables
	uint8_t contRising  ;		//variables
} tTecla;

void tecla_init( gpioMap_t tecla, tTecla* config );
void fsmButtonUpdate( tTecla* config );

#endif /* _TIPOS_H_ */
