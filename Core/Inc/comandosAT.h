/*
 * comandosAT.h
 *
 *  Created on: Jan 27, 2026
 *      Author: Adrian
 */

#ifndef INC_COMANDOSAT_H_
#define INC_COMANDOSAT_H_

void RAK_sendCmd(unsigned char *comando, unsigned int time);

void init_Rak(); // Incializamos el RAK

void joinRakloop(); // Inicializamos el joiun


#endif /* INC_COMANDOSAT_H_ */
