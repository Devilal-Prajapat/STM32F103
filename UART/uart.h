/*
 * uart.h
 *
 *  Created on: May 12, 2020
 *      Author: Devilal
 */

#ifndef UART_H_
#define UART_H_

#include "main.h"

extern UART_HandleTypeDef huart1;

void UART_Init(void);
void UART_Enable_Rx(void);

#endif /* UART_H_ */
