/*
 * callback.c
 *
 *  Created on: Jul 25, 2020
 *      Author: 0h2
 */


#include "usart.h"
#include "tim.h"

/* USER CODE BEGIN 0 */
uint8_t GPSRecvComplt_F = 0;
uint8_t Rx_BuffCount = 0;
uint8_t RxData = 0;
uint8_t Gps_RxBuff[512];
uint8_t gps_string_f = 0;

//GSM
uint8_t GSMRecvComplt_F = 0;
uint8_t GSM_RxBuffer[256];
uint8_t GSM_RxData;
uint8_t GSM_RxCount = 0;
uint8_t GSM_Timer_F = 0;



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance ==  USART3)
	{
		if(Rx_BuffCount>180)
		{
			__HAL_UART_DISABLE_IT(&huart3, UART_IT_RXNE);
			HAL_NVIC_ClearPendingIRQ(USART3_IRQn);
			GPSRecvComplt_F = 1;
		}
		else if((RxData == '$' || RxData == 'G' || RxData == 'P' || RxData == 'R' || RxData == 'M' || RxData == 'C') && (gps_string_f == 0))
		{
			if(Rx_BuffCount == 0 && RxData == '$')
			{
				Gps_RxBuff[Rx_BuffCount] = RxData;
				Rx_BuffCount++;
			}
			if(Rx_BuffCount == 1 && RxData == 'G')
			{
				Gps_RxBuff[Rx_BuffCount] = RxData;
				Rx_BuffCount++;
			}
			else if(Rx_BuffCount == 2 && RxData == 'P')
			{
				Gps_RxBuff[Rx_BuffCount] = RxData;
				Rx_BuffCount++;
			}
			else if(Rx_BuffCount == 3 && RxData == 'R')
			{
				Gps_RxBuff[Rx_BuffCount] = RxData;
				Rx_BuffCount++;
			}
			else if(Rx_BuffCount == 4 && RxData == 'M')
			{
				Gps_RxBuff[Rx_BuffCount] = RxData;
				Rx_BuffCount++;
			}
			else if(Rx_BuffCount == 5 && RxData == 'C')
			{
				Gps_RxBuff[Rx_BuffCount] = RxData;
				Rx_BuffCount++;
				gps_string_f = 1;
			}
		}
		else
		{
			if(gps_string_f == 1)
			{
				Gps_RxBuff[Rx_BuffCount] = RxData;
				Rx_BuffCount++;
			}else
			{
				Rx_BuffCount = 0;
			}
		}
		HAL_UART_Receive_IT(&huart3, (uint8_t *)&RxData, 1);
	}

	//GSM
	if(huart->Instance == USART2)
	{
		/*if(GSM_RxData == '\r' || GSM_RxData == '\n')
		{

		}
		else
		{
		}*/
		GSM_RxBuffer[GSM_RxCount] = GSM_RxData;
		GSM_RxCount++;
		HAL_UART_Receive_IT(&huart2, (uint8_t *)&GSM_RxData, 1);
		HAL_TIM_Base_Stop_IT(&htim3);
		__HAL_TIM_SET_COUNTER(&htim3,0);
		HAL_TIM_Base_Start_IT(&htim3);
		GSM_Timer_F = 1;
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM3)
	{
		if(GSM_Timer_F == 1)
		{
			GSM_Timer_F = 0;
			HAL_TIM_Base_Stop_IT(&htim3);
			HAL_NVIC_ClearPendingIRQ(USART2_IRQn);
			__HAL_UART_DISABLE_IT(&huart2, UART_IT_RXNE);
			GSMRecvComplt_F = 1;
		}
	}

}
