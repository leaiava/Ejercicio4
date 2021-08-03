# Ejercicio4

## Autores ✒️

_Este firmware tiene dos integrantes:_

* **L.Arrieta** - (https://github.com/leaiava)
* **J.Cagua** - (https://github.com/jonathancagua)

### Pre-requisitos 📋
- [Firmware V3](https://github.com/epernia/firmware_v3).
- [Utilización básica de firmware_v3](https://github.com/epernia/firmware_v3/blob/master/documentation/firmware/usage/usage-es.md).

## Resumen:
Implementar mediante el modelo de Máquina de Estados Finitos el antirrebote de teclas y la lógica de funcionamiento de un semáforo.
## Condiciones de funcionamiento:
### Dependencias externas:
- sAPI.h
- Usar delay no bloqueantes
## Objetivo:

1. Implementar un módulo de software en los archivos teclas.c y teclas.h, que encapsule el funcionamiento de las teclas de la EDU-CIAA-NXP. 

Dentro del módulo se debe implementar:
- Una MEF que resuelva el antirrebote por software con dos funciones asociadas, una para inicializar la MEF y otra para actualizar el estado de la MEF.
- Los estados de la MEF se deben implementar con un tipo de dato enumerativo (enum).
- Una función buttonPressed(gpioMap_t tecla) que resuelva las acciones correspondientes al flanco descendente. 
La función puede aceptar un argumento que indique qué tecla se presionó
- Una función buttonReleased(gpioMap_t tecla) que resuelva las acciones correspondientes al flanco ascendente.
La función puede aceptar un argumento que indique qué tecla se liberó


2. [Optativo] Implementar una única MEF que permita controlar las cuatro teclas de forma independiente.  La función de actualización de la MEF debe recibir como argumento por referencia una estructura con los siguientes campos:

- Nombre de la tecla
- Delay no bloqueante asociado a la tecla en particular
- Estado de la MEF asociado a esa tecla en particular

Por ejemplo:
    
    actualizarMEF(dbn_t * dataTecla1); //prototipo de la función para actualizar la MEF

    typedef struct {	// estructura para controlar el antirrebote de un tecla
    gpioMap_t tecla;
    delay_t delay;
    estadoMEF estado
    } dbn_t; 	

3. Implementar un controlador de semáforos dentro de un módulo de software con archivos semaforo.c y semaforo.h.

- El controlador se debe implementar como una MEF con dos funciones asociadas, una para inicializar la MEF y otra para actualizar el estado de la MEF.
- Los estados de la MEF se deben implementar con un tipo de dato enumerativo (enum).
- El semáforo debe tener los siguientes modos de operación:
  * Normal: secuencia de leds: rojo 3 s, rojo y amarillo 500 mS, verde 1s, amarillo y rojo nuevamente....
  * Desconectado: led amarillo intermitente cada 500 mS.
  * Alarma: rojo intermitente cada 1 s
Con la tecla 2 de la EDU-CIAA-NXP se debe poder cambiar el modo de operación del semáforo a normal. Con cada flanco ascendente se debe ciclar el modo en el siguiente orden: normal, desconectado, alarma, normal, etc...

4. [Opcional] Implementar un controlador de UART en un módulo de software con archivos uart.c y uart.h.
El módulo debe implementar funciones para informar:
- Cambios en la MEF antirrebote (qué tecla y en qué estado está la MEF).
- Cambios en la MEF del controlador de semáforos (modo de funcionamiento)
