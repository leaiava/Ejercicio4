/*
 * teclas.c
 *
 *  Created on: Jul 28, 2021
 *      Author: lea
 */
#include "teclas.h"

bool_t buttonInicializar(dbn_t* button){

	if ( button == NULL)
			return false;
	//agregar validacion tecla.
	delayInit (&(button->delay), TIEMPO_RETARDO_TECLA);
	button->estado = BOTON_UP;
	button->flagTeclaSePresiono = false;
	button->flagTeclaSeSolto = false;
	return true;
}

bool_t buttonActualizar(dbn_t* button){

	static delay_t myDelay;
	if ( button == NULL)
				return false;

	switch (button->estado) {
			case BOTON_UP:{
				// si leo tecla presionada, entonces paso al estado BOTON_FALLING
				if ( leerTecla( button->tecla) ){
					button->estado = BOTON_FALLING;
					uartWriteString( UART_USB, "BOTON_FALLING " );
					//Inicio el delay para verificar si realmente se presionó
					delayWrite( &(button->delay), TIEMPO_RETARDO_TECLA );
				}
			}
			break;

			case BOTON_FALLING:{
				//Si se cumplió el delay entro para volver a leer la tecla
				if(delayRead( &(button->delay)) ){
					// si leo tecla presionada, entonces paso al estado BOTON_DOWN
					if ( leerTecla( button->tecla) ){
						button->estado = BOTON_DOWN;
						uartWriteString( UART_USB, "BOTON_DOWN\r\n " );
						button->flagTeclaSePresiono = true;
						buttonPressed( button->tecla);
					}
					else {
						button->estado = BOTON_UP;
					}
				}

			}
			break;
			case BOTON_DOWN:{
			// si leo la tecla liberada, entonces paso al estado BOTON_RISING
				if ( !leerTecla( button->tecla) ){
					button->estado = BOTON_RISING;
					uartWriteString( UART_USB, "BOTON_RISING " );
					delayWrite(  &(button->delay), TIEMPO_RETARDO_TECLA  );
				}
			}
			break;

			case BOTON_RISING:{
				//Si se cumplió el delay entro para volver a leer la tecla
				if(delayRead(&myDelay)){
					// si leo tecla liberada, entonces paso al estado BOTON_UP
					if ( !leerTecla( button->tecla) ){
						button->estado = BOTON_UP;
						uartWriteString( UART_USB, "BOTON_UP\r\n " );
						button->flagTeclaSeSolto = true;
						buttonReleased( button->tecla);
					}
					else {
						button->estado = BOTON_DOWN;
					}
				}

			}
			break;

			default:{
				return false;
				buttonInicializar(button);
			}
			break;
	}
	 return true;
}

bool_t buttonPressed(gpioMap_t tecla){

	uartWriteString( UART_USB, "Se presiono una tecla\r\n" );
	return true;
}

bool_t  buttonReleased(gpioMap_t tecla){

	uartWriteString( UART_USB, "Se libero una tecla\r\n" );
	return true;
}
bool_t buttonFlagSePresionoLeer(dbn_t* button){

	if ( button->flagTeclaSePresiono ){
		button->flagTeclaSePresiono = false;
		return true;
	}
	else
		return false;
}

bool_t buttonFlagSeSoltoLeer(dbn_t* button){

	if ( button->flagTeclaSeSolto ){
		button->flagTeclaSeSolto = false;

		return true;
	}
	else
		return false;
}

/* Funcion leerTecla
 * Sirve para leer el estado de una tecla.
 * Recibe tecla a leer
 * Devuelve por valor el estado de la tecla pulsada (verdadero) o liberada (falso)*/
bool_t leerTecla (gpioMap_t teclax){
	if ( !( (teclax== TEC1) || (teclax== TEC2) || (teclax== TEC3) || (teclax== TEC4) ) ) //verifico que sea una tecla válida
			return 0;
	return !gpioRead( teclax );
}

