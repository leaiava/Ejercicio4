/*=============================================================================
 * Author: Leandro Arrieta <leandroarrieta@gmail.com>
 * 		   Jonathan Cagua <jonathan.cagua@gmail.com >
 * Fecha: 02/08/2021
 *===========================================================================*/

#include "semaforo.h"


bool_t semaforoInicializar(semaforoControl_t* ptrmiSemaforo){
	if ( ptrmiSemaforo == NULL)
		return false;
	ptrmiSemaforo->modo = SEMAFORO_DESCONECTADO;
	ptrmiSemaforo->color = SEMAFORO_AMARILLO;
	delayInit (&(ptrmiSemaforo->delay), TIEMPO_DESCONECTADO);
	return true;
}

bool_t semaforoActualizarModo(semaforoControl_t* ptrmiSemaforo){

	switch (ptrmiSemaforo->modo){
	// Paso al modo siguiente. Actualizo el color porque puede venir de un mood
	// que usaba un color que el próximo modo no utilice.
	case SEMAFORO_ALARMA:{
		ptrmiSemaforo->modo = SEMAFORO_DESCONECTADO;
		ptrmiSemaforo->color = SEMAFORO_AMARILLO;
		delayInit (&(ptrmiSemaforo->delay), TIEMPO_DESCONECTADO);
	}
	break;

	case SEMAFORO_DESCONECTADO:{
		ptrmiSemaforo->modo = SEMAFORO_NORMAL;
		ptrmiSemaforo->color = SEMAFORO_ROJO;
		delayInit (&(ptrmiSemaforo->delay), TIEMPO_ROJO_A_ROJOAMARILLO);
	}
	break;

	case SEMAFORO_NORMAL:{
		ptrmiSemaforo->modo = SEMAFORO_ALARMA;
		ptrmiSemaforo->color = SEMAFORO_ROJO;
		delayInit (&(ptrmiSemaforo->delay), TIEMPO_ALARMA);
	}
	break;
	default :
		semaforoInicializar(ptrmiSemaforo);
		return false;
	break;
	}
	return true;
}
bool_t semaforoActualizarColor(semaforoControl_t* ptrmiSemaforo){

	switch (ptrmiSemaforo->color) {

	case SEMAFORO_ROJO:{
		if(ptrmiSemaforo->modo == SEMAFORO_NORMAL){
			if(delayRead( &(ptrmiSemaforo->delay)) ){
				ptrmiSemaforo->color = SEMAFORO_ROJO_AMARILLO;
				delayWrite( &(ptrmiSemaforo->delay), TIEMPO_ROJOAMARILLO_A_VERDE );
			}
		}
		else if(ptrmiSemaforo->modo == SEMAFORO_ALARMA) {
			if(delayRead( &(ptrmiSemaforo->delay)) ){
				ptrmiSemaforo->color = SEMAFORO_APAGADO;
				delayWrite( &(ptrmiSemaforo->delay), TIEMPO_ALARMA );
			}
		}
		else
			semaforoInicializar(ptrmiSemaforo); //Por si hay un error mando a inicializar
	}
	break;

	case SEMAFORO_ROJO_AMARILLO:{
		if(delayRead( &(ptrmiSemaforo->delay)) ){
			ptrmiSemaforo->color = SEMAFORO_VERDE;
			delayWrite( &(ptrmiSemaforo->delay), TIEMPO_VERDE_A_AMARILLO );
		}
	}
	break;

	case SEMAFORO_VERDE:{
		if(delayRead( &(ptrmiSemaforo->delay)) ){
			ptrmiSemaforo->color = SEMAFORO_AMARILLO;
			delayWrite( &(ptrmiSemaforo->delay), TIEMPO_AMARILLO_A_ROJO );
		}
	}
	break;

	case SEMAFORO_AMARILLO:{
		if(ptrmiSemaforo->modo == SEMAFORO_NORMAL){
			if(delayRead( &(ptrmiSemaforo->delay)) ){
				ptrmiSemaforo->color = SEMAFORO_ROJO;
				delayWrite( &(ptrmiSemaforo->delay), TIEMPO_ROJO_A_ROJOAMARILLO );
			}
		}
		else if(ptrmiSemaforo->modo == SEMAFORO_DESCONECTADO){
			if(delayRead( &(ptrmiSemaforo->delay)) ){
				ptrmiSemaforo->color = SEMAFORO_APAGADO;
				delayWrite( &(ptrmiSemaforo->delay), TIEMPO_DESCONECTADO );

			}
		}
		else
			semaforoInicializar(ptrmiSemaforo); //Por si hay un error mando a inicializar
	}
	break;

	case SEMAFORO_APAGADO:{
		if(ptrmiSemaforo->modo == SEMAFORO_ALARMA){
			if(delayRead( &(ptrmiSemaforo->delay)) ){
				ptrmiSemaforo->color = SEMAFORO_ROJO;
				delayWrite( &(ptrmiSemaforo->delay), TIEMPO_ALARMA );
			}
		}
		else if(ptrmiSemaforo->modo == SEMAFORO_DESCONECTADO){
			if(delayRead( &(ptrmiSemaforo->delay)) ){
				ptrmiSemaforo->color = SEMAFORO_AMARILLO;
				delayWrite( &(ptrmiSemaforo->delay), TIEMPO_DESCONECTADO );
			}
		}
		else
			semaforoInicializar(ptrmiSemaforo);
	}
		break;
	default:
		semaforoInicializar(ptrmiSemaforo);
	break;

	}
	if ( !semaforoEncenderLed(ptrmiSemaforo) )
		return false;
	return true;
}

bool_t semaforoEncenderLed(semaforoControl_t* ptrmiSemaforo){
	if ( !ledApagarTodos() )
		return false;

	switch (ptrmiSemaforo->color) {
		case SEMAFORO_ROJO:{
			ledEncender( LEDR );
		}
		break;
		case SEMAFORO_ROJO_AMARILLO:{
			ledEncender( LEDR );
			ledEncender( LED1 );
		}
		break;
		case SEMAFORO_VERDE:{
			ledEncender( LEDG );
		}
		break;
		case SEMAFORO_AMARILLO:{
			ledEncender( LED1 );
		}
		break;
		case SEMAFORO_APAGADO:{
		}
	}
	return true;
}
