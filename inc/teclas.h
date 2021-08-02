/*=============================================================================
 * Author: Leandro Arrieta <leandroarrieta@gmail.com>
 * 		   Jonathan Cagua <jonathan.cagua@gmail.com >
 * Fecha: 02/08/2021
 *===========================================================================*/

#ifndef _TECLAS_H_
#define _TECLAS_H_

#include "sapi.h"

#define TECLAS_TODAS	4	//Cantidad de teclas en la EDU-CIAA
#define TIEMPO_RETARDO_TECLA 40 //Tiempo en ms para el anti-rebote

/* enum buttomState_t
 * Estados de la MEF que va a manejar la tecla
 */
typedef enum{
    BOTON_UP,
	BOTON_FALLING,
	BOTON_DOWN,
	BOTON_RISING
} buttomState_t;


/*struct dbn_t
 * Estructura que tiene todos los datos de la tecla para
 * ser utilizado por la MEF
 */
typedef struct {
	gpioMap_t tecla;
	delay_t delay;
	buttomState_t estado;
	bool_t flagTeclaSePresiono;
	bool_t flagTeclaSeSolto;
} dbn_t;

/* Funcion buttonPressed
 * Función que se ejecuta cuando se confirma que el botón se presiono realmente
 * No tiene implementada ninguna función en particular
 */
bool_t buttonPressed(gpioMap_t tecla);

/* Funcion buttonReleased
 * Función que se ejecuta cuando se confirma que el botón se liberó realmente
 * No tiene implementada ninguna función en particular
 */
bool_t buttonReleased(gpioMap_t tecla);

/* Funcion buttonFlagSePresionoLeer
 * Sirve para dar el servicio de que se lea el estado del flag
 * que indica si se presiono una tecla
 * Recibe el puntero a la estructura de la cual se quiere leer el estado
 * Devuelve true en caso de que vaya todo bien
 * Devuelve false en caso de que haya recibido un puntero a Null
 */
bool_t buttonFlagSePresionoLeer(dbn_t* button);

/* Funcion buttonFlagSeSoltoLeer
 * Sirve para dar el servicio de que se lea el estado del flag
 * que indica si se libero una tecla
 * Recibe el puntero a la estructura de la cual se quiere leer el estado
 * Devuelve true en caso de que vaya todo bien
 * Devuelve false en caso de que haya recibido un puntero a Null
 */
bool_t buttonFlagSeSoltoLeer(dbn_t* button);

/* Función buttonInicializar
 * Sirve para inicializar la MEF del botón
 * Recibe un puntero a la estructura que tiene los datos de la tecla
 * Devuelve true en caso de que vaya todo bien
 * Devuelve false en caso de que haya recibido un puntero a Null
 */
bool_t buttonInicializar(dbn_t* button);

/* Funcion buttonActualizar
 * Sirve para actualizar el estado de la MEF
 * Recibe un puntero a la estructura que tiene los datos de la tecla
 * Devuelve true en caso de que vaya todo bien
 * Devuelve false en caso de que haya recibido un puntero a Null o que se haya
 * detectado un estado erroneo en la MEF
 */
bool_t buttonActualizar(dbn_t* button);

/* Funcion leerTecla
 * Sirve para leer el estado de una tecla.
 * Recibe tecla a leer
 * Devuelve por valor el estado de la tecla pulsada (verdadero) o liberada (falso)*/
bool_t leerTecla(gpioMap_t teclax);

/* Funcion buttonCambioAEstadoTransitorio
 * Lee la tecla y cambia a un estado transitorio en caso de detectarse un cambio
 * Recibe un puntero a la estructura que tiene los datos de la tecla
 * Recibe un bool status que le indica si quiero detectar si la tecla se presiono o se libero
 * No devuelve nada
 */
static void buttonCambioAEstadoTransitorio(dbn_t* button , bool status);

/* Funcion buttonCambioAEstadoFijo
 * Espera que se cumpla el tiempo seteado para volver a leer la tecla y
 * verificar si realmente se libero o se soltó la tecla. Cambia el estado de
 * la tecla a un estado fijo, liberada o presionada según corresponda.
 * Recibe un puntero a la estructura que tiene los datos de la tecla
 * Recibe un bool status que le indica si quiero detectar si la tecla se presiono o se libero
 * No devuelve nada
 */
static void buttonCambioAEstadoFijo(dbn_t* button , bool status);

#endif /* _TECLAS_H_ */
