/*=============================================================================
 * Author: Leandro Arrieta <leandroarrieta@gmail.com>
 * 		   Jonathan Cagua <jonathan.cagua@gmail.com >
 * Date: 2021/07/07
 *===========================================================================*/


#ifndef _LED_H_
#define _LED_H_

#include "sapi.h"

#define led_apagar(ledx)	gpioWrite( ledx, OFF )
#define led_esta_apagado(teclax)	!gpioRead( teclax )
#define LED_OFF LED3+1	//defino el LED_OFF con uno más del último led de la placa

/*=====[Prototypes (declarations) of public functions]=======================*/

bool_t ledEncender(gpioMap_t LedaEncender);

bool_t ledApagar(gpioMap_t LedaApagar );

bool_t ledApagarTodos( void);

#endif /*_LED_H_ */

