/*=============================================================================
 * Author: Leandro Arrieta <leandroarrieta@gmail.com>
 * 		   Jonathan Cagua <jonathan.cagua@gmail.com >
 * Fecha: 02/08/2021
 *===========================================================================*/

#ifndef _UART_H_
#define _UART_H_

#include "sapi.h"
#include "teclas.h"
#include "semaforo.h"

/* Funcion UARTInicializar
 * Inicializa la uart
 */
void UARTInicializar (uartMap_t uart , uint32_t baudRate );

/* Funcion UARTimprimirEstadoBoton
 * Recibe un puntero a la estructura de la tecla e imprime su estado
 */
void UARTimprimirEstadoBoton (dbn_t* button);

/* Funcion UARTimprimirEstadoSemaforo
 * Recibe un puntero a la estructura del semaforo e imprime su estado
 */
void UARTimprimirEstadoSemaforo (semaforoControl_t* semaforoEstado);

#endif /* _UART_H_ */
