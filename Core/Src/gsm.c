/*
 * gsm.c
 *
 *  Created on: Jul 26, 2020
 *      Author: 0h2
 */

#include "gsm.h"


extern  char send_buffer[100];
extern char  gps_string[256];
extern int gps_string_len;

char *gsm_cmd[100] = {"AT\r\n",
		"ATE0\r\n",
		"AT+CPIN?\r\n",
		"AT+CREG?\r\n",
		"AT+QICLOSE\r\n",
		"AT+QIDEACT\r\n",
		"AT+QIMODE=0\r\n",
		"AT+QICSGP=1,\"INTERNET\"\r\n",
		"AT+QIREGAPP\r\n",
		"AT+QICSGP?\r\n",
		"AT+QIACT\r\n",
		"AT+QILOCIP\r\n",
		"AT+QIHEAD=1\r\n",
		"AT+QIDNSIP=0\r\n",
		"AT+QIOPEN=\"TCP\",\"13.126.54.198\",\"62330\"\r\n",
		"AT+QISEND\r\n"
};

AT_CMDCcode  Process_CMD(uint8_t cmd_code, uint8_t *pBuffer)
{
	AT_CMDCcode cmd = cmd_code;
	switch(cmd)
	{
		case AT:
			cmd = ATE0;
			break;
		case ATE0:
			cmd = AT_CPIN;
			break;
		case AT_CPIN:
			cmd = AT_CREG;
			break;
		case AT_CREG:
			cmd = AT_QICLOSE;
			break;
		case AT_QICLOSE:
			cmd = AT_QIDEACT;
			break;
		case AT_QIDEACT:
			cmd = AT_QIMODE;
			break;
		case AT_QIMODE:
			cmd = AT_QICSGP;
			break;

		case AT_QICSGP:
			cmd = AT_QIREGAPP;
			break;
		case AT_QIREGAPP:
			cmd = AT_QICSGP_CM;
			break;
		case AT_QICSGP_CM:
			cmd = AT_QIACT;
			break;
		case AT_QIACT:
			cmd = AT_QILOCIP;
			break;
		case AT_QILOCIP:
			cmd = AT_QIHEAD;
			break;
		case AT_QIHEAD:
			cmd = AT_QIDNSIP;
			break;
		case AT_QIDNSIP:
			__HAL_TIM_SET_AUTORELOAD(&htim3,10000);
			cmd = AT_QIOPEN;
			break;
		case AT_QIOPEN:
		__HAL_TIM_SET_AUTORELOAD(&htim3,60);
			cmd = AT_QISEND;
			break;
		case AT_QISEND:
//			AT_CMD("This is Test String\r\n");
			AT_CMD(gps_string);
			AT_CMD("%c\r\n",26);
			cmd = AT;
			break;

		default:

			break;
	}
	return cmd;
}

void Send_CMD(AT_CMDCcode cmd)
{
	AT_CMD(gsm_cmd[cmd]);
}

