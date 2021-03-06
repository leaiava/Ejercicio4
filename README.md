# Ejercicio4

## Autores 鉁掞笍

_Este firmware tiene dos integrantes:_

* **L.Arrieta** - (https://github.com/leaiava)
* **J.Cagua** - (https://github.com/jonathancagua)

### Pre-requisitos 馃搵
- [Firmware V3](https://github.com/epernia/firmware_v3).
- [Utilizaci贸n b谩sica de firmware_v3](https://github.com/epernia/firmware_v3/blob/master/documentation/firmware/usage/usage-es.md).

## Resumen:
Implementar mediante el modelo de M谩quina de Estados Finitos el antirrebote de teclas y la l贸gica de funcionamiento de un sem谩foro.
## Condiciones de funcionamiento:
### Dependencias externas:
- sAPI.h
- Usar delay no bloqueantes
## Objetivo:

1. Implementar un m贸dulo de software en los archivos teclas.c y teclas.h, que encapsule el funcionamiento de las teclas de la EDU-CIAA-NXP. 

Dentro del m贸dulo se debe implementar:
- Una MEF que resuelva el antirrebote por software con dos funciones asociadas, una para inicializar la MEF y otra para actualizar el estado de la MEF.
- Los estados de la MEF se deben implementar con un tipo de dato enumerativo (enum).
- Una funci贸n buttonPressed(gpioMap_t tecla) que resuelva las acciones correspondientes al flanco descendente. 
La funci贸n puede aceptar un argumento que indique qu茅 tecla se presion贸
- Una funci贸n buttonReleased(gpioMap_t tecla) que resuelva las acciones correspondientes al flanco ascendente.
La funci贸n puede aceptar un argumento que indique qu茅 tecla se liber贸


2. [Optativo] Implementar una 煤nica MEF que permita controlar las cuatro teclas de forma independiente.  La funci贸n de actualizaci贸n de la MEF debe recibir como argumento por referencia una estructura con los siguientes campos:

- Nombre de la tecla
- Delay no bloqueante asociado a la tecla en particular
- Estado de la MEF asociado a esa tecla en particular

Por ejemplo:
    
    actualizarMEF(dbn_t * dataTecla1); //prototipo de la funci贸n para actualizar la MEF

    typedef struct {	// estructura para controlar el antirrebote de un tecla
    gpioMap_t tecla;
    delay_t delay;
    estadoMEF estado
    } dbn_t; 	

3. Implementar un controlador de sem谩foros dentro de un m贸dulo de software con archivos semaforo.c y semaforo.h.

- El controlador se debe implementar como una MEF con dos funciones asociadas, una para inicializar la MEF y otra para actualizar el estado de la MEF.
- Los estados de la MEF se deben implementar con un tipo de dato enumerativo (enum).
- El sem谩foro debe tener los siguientes modos de operaci贸n:
  * Normal: secuencia de leds: rojo 3 s, rojo y amarillo 500 mS, verde 1s, amarillo y rojo nuevamente....
  * Desconectado: led amarillo intermitente cada 500 mS.
  * Alarma: rojo intermitente cada 1 s
Con la tecla 2 de la EDU-CIAA-NXP se debe poder cambiar el modo de operaci贸n del sem谩foro a normal. Con cada flanco ascendente se debe ciclar el modo en el siguiente orden: normal, desconectado, alarma, normal, etc...

4. [Opcional] Implementar un controlador de UART en un m贸dulo de software con archivos uart.c y uart.h.
El m贸dulo debe implementar funciones para informar:
- Cambios en la MEF antirrebote (qu茅 tecla y en qu茅 estado est谩 la MEF).
- Cambios en la MEF del controlador de sem谩foros (modo de funcionamiento)
