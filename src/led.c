/*=============================================================================
 * Author: Leandro Arrieta <leandroarrieta@gmail.com>
 * 		   Jonathan Cagua <jonathan.cagua@gmail.com >
 * Date: 2021/07/07
 *===========================================================================*/

#include "led.h"

/* Funcion ledEncender
 * Sirve para encender un led en particular
 * Recibe el Led a encender
 * Devuelve 1 si pudo encender el led o si el led que se recibió es el LED_OFF
 * Devuelve 0 en caso de error */
bool_t ledEncender(gpioMap_t LedaEncender){
	if( (LedaEncender == LED_OFF))	//Si en el array viene el LED_OFF no intento prender y devuelve true
		return (true);

	if( (LedaEncender<LEDR)||(LedaEncender>LED3))	//verifico que sea un Led válido
		return(false);
	gpioWrite( LedaEncender, ON );              //prendo el led
	return( !led_esta_apagado(LedaEncender) );	//verifico que se haya prendido
}

/* Funcion ledApagar
 * Sirve para apagar un led
 * Recibe led a apagar
 * Devuelve 1 si pudo apagar el led
 * Devuelve 0 en caso de error */
bool_t ledApagar(gpioMap_t LedaApagar ){

	if( (LedaApagar == LED_OFF))	//Si recibo el LED_OFF no intento apagar y devuelve true
			return (true);

	bool_t resp = true;

	if( (LedaApagar<LEDR)||(LedaApagar>LED3))	//verifico que sea un Led válido
		return(false);
	resp &= led_apagar( LedaApagar );	//apago led
	resp &= led_esta_apagado( LedaApagar );	//verifico que se haya apagado
	return(resp);
}

bool_t ledApagarTodos( void){

	bool_t resp = true;
	resp &= led_apagar(LED1);
	resp &= led_esta_apagado(LED1);
	resp &= led_apagar(LED2);
	resp &= led_esta_apagado(LED2);
	resp &= led_apagar(LED3);
	resp &= led_esta_apagado(LED3);
	resp &= led_apagar(LEDR);
	resp &= led_esta_apagado(LEDR);
	resp &= led_apagar(LEDG);
	resp &= led_esta_apagado(LEDG);
	resp &= led_apagar(LEDB);
	resp &= led_esta_apagado(LEDB);
	return resp;
}
