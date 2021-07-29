/*
 * semaforo.h
 *
 *  Created on: Jul 29, 2021
 *      Author: lea
 */

#ifndef SEMAFORO_H_
#define SEMAFORO_H_

#include "sapi.h"
#include "led.h"

#define TIEMPO_ROJO_A_ROJOAMARILLO	3000
#define TIEMPO_ROJOAMARILLO_A_VERDE	500
#define TIEMPO_VERDE_A_AMARILLO		1000
#define TIEMPO_AMARILLO_A_ROJO		500
#define TIEMPO_DESCONECTADO			500
#define TIEMPO_ALARMA				1000

typedef enum{
    SEMAFORO_NORMAL,
	SEMAFORO_DESCONECTADO,
	SEMAFORO_ALARMA,
} semaforoState_t;

typedef enum{
	SEMAFORO_ROJO,
	SEMAFORO_ROJO_AMARILLO,
	SEMAFORO_VERDE,
	SEMAFORO_AMARILLO,
	SEMAFORO_APAGADO
} semaforoColores_t;

typedef struct {
	semaforoState_t modo;
	semaforoColores_t color;
	delay_t delay;
} semaforoControl_t;

bool_t semaforoInicializar(semaforoControl_t* semaforoEstado);

bool_t semaforoActualizarModo(semaforoControl_t* semaforoEstado);

bool_t semaforoActualizarColor(semaforoControl_t* ptrmiSemaforo);

bool_t semaforoEncenderLed(semaforoControl_t* ptrmiSemaforo);

#endif /* SEMAFORO_H_ */
