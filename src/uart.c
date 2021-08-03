/*=============================================================================
 * Author: Leandro Arrieta <leandroarrieta@gmail.com>
 * 		   Jonathan Cagua <jonathan.cagua@gmail.com >
 * Fecha: 02/08/2021
 *===========================================================================*/

#include "uart.h"

static uartMap_t MiUART;
const char ArrayTeclas[][6] = {"TEC1\0","TEC2\0","TEC3\0","TEC4\0"};
const char ArrayEstadosBoton[][12] = { "Liberada\0" , "Bajando\0" , "Presionada\0" , "Subiendo\0" };
const char ArrayEstadoSemaforo[][14] = { "NORMAL\0" , "DESCONECTADO\0" , "ALARMA\0"};

void UARTInicializar (uartMap_t uart , uint32_t baudRate ){
	MiUART = uart;
	uartInit( uart, baudRate );
	return;
}

void UARTimprimirEstadoBoton (dbn_t* button){
	uartWriteString( MiUART , "La tecla " );
	uartWriteString( MiUART ,  &ArrayTeclas[button->tecla-TEC1][0] );
	uartWriteString( MiUART , " se encuentra " );
	uartWriteString( MiUART ,  &ArrayEstadosBoton[button->estado][0] );
	uartWriteString( MiUART , "\r\n" );
	return;
}

void UARTimprimirEstadoSemaforo (semaforoControl_t* semaforoEstado){

	uartWriteString( MiUART , "El semaforo cambia al modo " );
	uartWriteString( MiUART ,  &ArrayEstadoSemaforo[semaforoEstado->modo][0] );
	uartWriteString( MiUART , "\r\n" );
	return;
}
