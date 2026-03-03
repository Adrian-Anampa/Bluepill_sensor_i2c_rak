/*
 * comandosAt.c
 *
 *  Created on: Jan 27, 2026
 *      Author: Adrian
 */

#include "comandosAT.h"
#include "stm32f1xx_it.h"
#include "stdio.h"
#include "string.h"
#include "stm32f1xx_hal.h"


extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;


unsigned char rx_buffer[128];
uint8_t flag_joined=0;

void RAK_sendCmd(unsigned char *comando, unsigned int time){

	memset(rx_buffer, 0, 100); // Limpia buffer

	HAL_UART_Transmit(&huart2, (unsigned char*)"Tx: ", 4, 100);
	HAL_UART_Transmit(&huart2, comando, strlen((char*)comando), HAL_MAX_DELAY);

	HAL_UART_Transmit(&huart1, comando, strlen((char*)comando), HAL_MAX_DELAY);

	// Esperamos respuesta
	HAL_UART_Receive(&huart1, rx_buffer, sizeof(rx_buffer), 1000);

	HAL_UART_Transmit(&huart2, (unsigned char*)"Rx: ", 4, 100);

	HAL_Delay(time);

	HAL_UART_Transmit(&huart2, rx_buffer, strlen((char*)rx_buffer), 400);

	HAL_UART_Transmit(&huart2, (unsigned char*)"\r\n", 2, 100);

}

void init_Rak() {
    RAK_sendCmd((unsigned char*)"ATZ\r\n", 1500);
    RAK_sendCmd((unsigned char*)"AT+NWM=1\r\n", 800);
    RAK_sendCmd((unsigned char*)"AT+BAND=6\r\n", 800);
    RAK_sendCmd((unsigned char*)"AT+DEVEUI=AC1F09FFFE08250B\r\n", 800);
    RAK_sendCmd((unsigned char*)"AT+APPKEY=2658398efec01a91dd2716cbf5247353\r\n", 1000);
    joinRakloop();
  }

void joinRakloop(){
 HAL_UART_Transmit(&huart2, (unsigned char*)"--- JOINING... ---\r\n", 20, 100);
 RAK_sendCmd((unsigned char*)"AT+JOIN=1:0:10:8\r\n", 200);
}
uint8_t Check_Join_Status(){

	if(flag_joined == 1) return 1 ;
	memset(rx_buffer,0,100);
	RAK_sendCmd((unsigned char*)"AT+NJS=?\r\n", 5000);
	if(strstr((char*)rx_buffer,"+AT+NJS=1") != NULL ){
		flag_joined =1 ; //exito
		HAL_UART_Transmit(&huart2, (unsigned char*)"RAK: JOINED!", 12, 100);
		return 1;
	}
	return 0;
}

