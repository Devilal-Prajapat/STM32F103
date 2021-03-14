/*
 * extern_variable.h
 *
 *  Created on: Jul 26, 2020
 *      Author: 0h2
 */

#ifndef INC_EXTERN_VARIABLE_H_
#define INC_EXTERN_VARIABLE_H_

#include "main.h"

//gps
extern uint8_t GPSRecvComplt_F;
extern uint8_t Rx_BuffCount;
extern uint8_t RxData;
extern uint8_t Gps_RxBuff[156];
extern uint8_t gps_string_f;

// GSM
extern uint8_t GSMRecvComplt_F;
extern uint8_t GSM_RxBuffer[256];
extern uint8_t GSM_RxData;
extern uint8_t GSM_RxCount;

#endif /* INC_EXTERN_VARIABLE_H_ */
