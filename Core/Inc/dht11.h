/*
 * dht11.h
 *
 *  Created on: Jan 27, 2026
 *      Author: Adrian
 */

#ifndef INC_DHT11_H_
#define INC_DHT11_H_

#define DHT11_PORT GPIOB
#define DHT11_PIN GPIO_PIN_9

#include "main.h"
#include "stdio.h"

void microDelay(uint16_t delay) ; // Funcion para el tiempo en microsegundos exactos
// delay es de 16 bits por la configuracion maxima del contadora 2^16

uint8_t DHT11_Start(void) ; // Fucion para inicializar el DHT11

uint8_t DHT11_Read (void) ; // funcion para lectura de datos del DHt11




#endif /* INC_DHT11_H_ */
