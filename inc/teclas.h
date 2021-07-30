/*
 * teclas.h
 *
 *  Created on: Jul 28, 2021
 *      Author: lea
 */

#ifndef _TECLAS_H_
#define _TECLAS_H_

#include "sapi.h"

#define TECLAS_TODAS	4
#define TIEMPO_RETARDO_TECLA 40

typedef enum{
    BOTON_UP,
	BOTON_FALLING,
	BOTON_DOWN,
	BOTON_RISING
} buttomState_t;

typedef struct {
	gpioMap_t tecla;
	delay_t delay;
	buttomState_t estado;
	bool_t flagTeclaSePresiono;
	bool_t flagTeclaSeSolto;
} dbn_t;

bool_t buttonPressed(gpioMap_t tecla);

bool_t buttonReleased(gpioMap_t tecla);

bool_t buttonFlagSePresionoLeer(dbn_t* button);

bool_t buttonFlagSeSoltoLeer(dbn_t* button);

bool_t buttonInicializar(dbn_t* button);

bool_t buttonActualizar(dbn_t* button);


bool_t leerTecla(gpioMap_t teclax);

#endif /* _TECLAS_H_ */
