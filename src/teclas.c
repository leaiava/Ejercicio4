/*=============================================================================
 * Author: Leandro Arrieta <leandroarrieta@gmail.com>
 * 		   Jonathan Cagua <jonathan.cagua@gmail.com >
 * Fecha: 02/08/2021
 *===========================================================================*/

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
	if ( button == NULL)
				return false;

	switch (button->estado) {
			case BOTON_UP:
				buttonCambioAEstadoTransitorio(button,true);
			break;

			case BOTON_FALLING:
				buttonCambioAEstadoFijo(button,true);
			break;
			case BOTON_DOWN:
				buttonCambioAEstadoTransitorio(button,false);
			break;

			case BOTON_RISING:
				buttonCambioAEstadoFijo(button,false);
			break;

			default:{
				buttonInicializar(button);
				return false;
			}
			break;
	}
	 return true;
}

static void buttonCambioAEstadoTransitorio(dbn_t* button , bool status){
	if ( leerTecla( button->tecla) == status){
		button->estado++;
		//printf("BOTON ESTADO: %d \r\n" , button->estado);
		delayWrite( &(button->delay), TIEMPO_RETARDO_TECLA );
	}
}

static void buttonCambioAEstadoFijo(dbn_t* button , bool status){
	if(delayRead( &(button->delay)) ){
		if ( leerTecla( button->tecla) == status){
			button->estado++;
			if(button->estado > BOTON_RISING){
				button->estado = BOTON_UP;
				buttonReleased(button->tecla);
				button->flagTeclaSeSolto = true;
			}
			else{
				buttonPressed(button->tecla);
				button->flagTeclaSePresiono = true;
			}
			//printf("BOTON LOOP: %d \r\n" , button->estado);
		}
		else {
			button->estado--;
		}
	}
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

bool_t leerTecla (gpioMap_t teclax){
	if ( !( (teclax== TEC1) || (teclax== TEC2) || (teclax== TEC3) || (teclax== TEC4) ) ) //verifico que sea una tecla válida
			return 0;
	return !gpioRead( teclax );
}

/*
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
*/
