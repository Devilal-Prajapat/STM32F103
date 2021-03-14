/*
 * gsm.h
 *
 *  Created on: Jul 26, 2020
 *      Author: 0h2
 */

#ifndef INC_GSM_H_
#define INC_GSM_H_

#include  "main.h"
#include "tim.h"
#include "usart.h"



typedef enum
{
	AT = 0,
	ATE0,
	AT_CPIN,
	AT_CREG,
	AT_QICLOSE,
	AT_QIDEACT,
	AT_QIMODE,
	AT_QICSGP,
	AT_QIREGAPP,
	AT_QICSGP_CM,
	AT_QIACT,
	AT_QILOCIP,
	AT_QIHEAD,
	AT_QIDNSIP,
	AT_QIOPEN,
	AT_QISEND,
}AT_CMDCcode;


AT_CMDCcode  Process_CMD(uint8_t cmd_code, uint8_t *pBuffer);
void Send_CMD(AT_CMDCcode cmd);

#endif /* INC_GSM_H_ */
