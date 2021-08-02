/*=============================================================================
 * Author: Leandro Arrieta <leandroarrieta@gmail.com>
 * 		   Jonathan Cagua <jonathan.cagua@gmail.com >
 * Fecha: 02/08/2021
 *===========================================================================*/

#ifndef SEMAFORO_H_
#define SEMAFORO_H_

#include "sapi.h"
#include "led.h"

//Tiempos de transicion para el semaforo
#define TIEMPO_ROJO_A_ROJOAMARILLO	3000
#define TIEMPO_ROJOAMARILLO_A_VERDE	500
#define TIEMPO_VERDE_A_AMARILLO		1000
#define TIEMPO_AMARILLO_A_ROJO		500
#define TIEMPO_DESCONECTADO			500
#define TIEMPO_ALARMA				1000

/* enum semaforoState_t
 * Estados de la MEF que va a manejar los modos del semáforo
 */
typedef enum{
    SEMAFORO_NORMAL,
	SEMAFORO_DESCONECTADO,
	SEMAFORO_ALARMA,
} semaforoState_t;

/* enum semaforoColores_t
 * Estados de la MEF que maneja los colores del semáforo según el modo.
 */
typedef enum{
	SEMAFORO_ROJO,
	SEMAFORO_ROJO_AMARILLO,
	SEMAFORO_VERDE,
	SEMAFORO_AMARILLO,
	SEMAFORO_APAGADO
} semaforoColores_t;

/* struct semaforoControl_t
 * Estructura que tiene los datos del semaforo
 */
typedef struct {
	semaforoState_t modo;
	semaforoColores_t color;
	delay_t delay;
} semaforoControl_t;

/* funcion semaforoInicializar
 * Sirve para inicializar la MEF del semáforo
 * Recibe un puntero a la estructura de control del semáforo
 * Devuelve true en caso de que vaya todo bien
 * Devuelve false en caso de que haya recibido un puntero a Null
 */
bool_t semaforoInicializar(semaforoControl_t* semaforoEstado);

/* Funcion semaforoActualizarModo
 * Sirve para actualizar el modo de funcionamiento del semáforo
 * Recibe un puntero a la estructura de control del semáforo
 * Devuelve false en caso de que haya detectado un estado inválido
 * Devuelve true si cambio bien de estado
 */
bool_t semaforoActualizarModo(semaforoControl_t* semaforoEstado);

/* Funcion semaforoActualizarColor
 * Sirve para actualizar los colores dependiendo el modo del semáforo
 * Recibe un puntero a la estructura de control del semáforo
 * Devuelve false en caso de que haya detectado un estado inválido
 * Devuelve true si cambio bien de estado
 */
bool_t semaforoActualizarColor(semaforoControl_t* ptrmiSemaforo);

/* Funcion semaforoEncenderLed
 * Recibe un puntero a la estructura de control del semáforo
 * Enciende los leds correspondientes de a cuerdo al estado del semaforo
 * Devuelve true si pudo prender los leds
 * En caso contrario devuelve false
 */
bool_t semaforoEncenderLed(semaforoControl_t* ptrmiSemaforo);

#endif /* SEMAFORO_H_ */
