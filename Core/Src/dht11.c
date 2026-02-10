/*
 * dht11.c
 *
 *  Created on: Jan 27, 2026
 *      Author: Adrian
 */

#include "dht11.h"
#include "stm32f1xx_hal_conf.h"
#include "stm32f1xx_it.h"
#include "stm32f1xx_hal_def.h"
#include "main.h"

uint32_t pMillis , cMillis ;

extern TIM_HandleTypeDef htim1;


void microDelay(uint16_t delay){
	__HAL_TIM_SET_COUNTER(&htim1,0);
	 while (__HAL_TIM_GET_COUNTER(&htim1)< delay);
}
uint8_t DHT11_Start(void){
	uint8_t Response = 0;
	          /*---- GPIO EN MODO DE SALIDA ---*/
	GPIO_InitTypeDef GPIO_InitStructPrivate = {0};
	GPIO_InitStructPrivate.Pin = DHT11_PIN;
	GPIO_InitStructPrivate.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructPrivate.Pull = GPIO_NOPULL;
	GPIO_InitStructPrivate.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStructPrivate);
	HAL_GPIO_WritePin (DHT11_PORT, DHT11_PIN, 0);   // pull the pin low
	microDelay(20000); // espera 20 ms
	HAL_GPIO_WritePin (DHT11_PORT, DHT11_PIN, 1);   // pull the pin high
	microDelay (30);   // wait for 30us
	/*------------GPIO EN MODO ENTRADA----*/
	GPIO_InitStructPrivate.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructPrivate.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStructPrivate); // set the pin as input
	microDelay (40);

	/* ---- LOGICA DE LA RESPUESTA DEL DHT11 -----*/

	if (!(HAL_GPIO_ReadPin (DHT11_PORT, DHT11_PIN)))
		  {
		     microDelay (80);
		     if ((HAL_GPIO_ReadPin (DHT11_PORT, DHT11_PIN))) Response = 1;
		  }
		   pMillis = HAL_GetTick();
		   cMillis = HAL_GetTick();
		   while ((HAL_GPIO_ReadPin (DHT11_PORT, DHT11_PIN)) && pMillis + 2 > cMillis)
		   {
		     cMillis = HAL_GetTick();
		   }
		   return Response;
}

uint8_t DHT11_Read (void){

	uint8_t a,b;
	for( a = 0 ; a < 8 ; a++) {
		pMillis= HAL_GetTick();
		cMillis= HAL_GetTick();
		while(!(HAL_GPIO_ReadPin(DHT11_PORT,DHT11_PIN)) && pMillis +2 > cMillis){
			cMillis = HAL_GetTick();
		}
		microDelay(40);
		  if (!(HAL_GPIO_ReadPin (DHT11_PORT, DHT11_PIN)))
			  b&= ~(1<<(7-a));
		  else
			  b|=(1<<(7-a));
		  pMillis= HAL_GetTick();
		  cMillis= HAL_GetTick();
		  while((HAL_GPIO_ReadPin(DHT11_PORT,DHT11_PIN)) && pMillis +2 > cMillis)
		  {
		      cMillis = HAL_GetTick();

		  }
	}

	return b;
}



