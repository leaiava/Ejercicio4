/*=============================================================================
 * Author: Leandro Arrieta <leandroarrieta@gmail.com>
 * 		   Jonathan Cagua <jonathan.cagua@gmail.com >
 * Fecha: 02/08/2021
 *===========================================================================*/

#include "teclas.h"
#include "sapi.h"
#include "main.h"
#include "semaforo.h"

int main (void){

	dbn_t button[TECLAS_TODAS];
	semaforoControl_t miSemaforo;

	boardInit();

// Inicializar UART_USB a 115200 baudios
   uartConfig( UART_USB, 115200 );

	button[0].tecla = TEC1;
	button[1].tecla = TEC2;
	button[2].tecla = TEC3;
	button[3].tecla = TEC4;
	buttonInicializar( &button[0] );
	buttonInicializar( &button[1] );
	buttonInicializar( &button[2] );
	buttonInicializar( &button[3] );

	semaforoInicializar(&miSemaforo);

	while(1){

		for(int i=0; i<TECLAS_TODAS; i++){
			if (!buttonActualizar( &button[i]) )
				atenderError();
		}

		if ( buttonFlagSeSoltoLeer(&button[1]))
			semaforoActualizarModo(&miSemaforo);

		if (!semaforoActualizarColor(&miSemaforo))
			atenderError();
	}

	return 0;
}

// No se implementa la atención del error, se deja colgado con el while(1)
void atenderError()
{
	while(1);
}
