/*
 * uart.c
 *
 *  Created on: May 12, 2020
 *      Author: Devilal
 */

#include "uart.h"

UART_HandleTypeDef huart1;

uint16_t rxindex = 0;
uint8_t RxData;
uint8_t Rx_Buffer[256];
uint8_t Recv_Complete_F = false;


/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
void UART_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* configure UART parameter */
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 9600;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;

	if(HAL_UART_Init(&huart1)!= HAL_OK)
	{
		Error_Handler();
	}

	/* Enable peripheral clock */
	__HAL_RCC_USART1_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/* PA9 ---> USART1_TX
	 * PA10 --> USART1_RX
	 */
	GPIO_InitStruct.Pin = GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA,&GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA,&GPIO_InitStruct);

	/* Enable IRQ */
	HAL_NVIC_SetPriority(USART1_IRQn,0,0);
	HAL_NVIC_EnableIRQ(USART1_IRQn);
}
/**
  * @brief USART1 Receive Complete Call back
  * @param None
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance == USART1)
  {
	  if(Recv_Complete_F == false)
	  {
		  if(rxindex>255)
		  {
			  rxindex = 0;
			  memset(Rx_Buffer,0x00,256);
		  }
		  else if(RxData == '\n')
		  {
			  Rx_Buffer[rxindex] = RxData;
			  __HAL_UART_DISABLE_IT(&huart1,UART_IT_RXNE); // to overcome uart hangup
			  Recv_Complete_F = true;
		  }
		  else
		  {
			  Rx_Buffer[rxindex] = RxData;
			  rxindex++;
		  }
		  HAL_UART_Receive_IT(&huart1,(uint8_t *)&RxData,1);
	  }
  }
}

/**
  * @brief USART1 Enable Rx
  * @param None
  * @retval None
  */
void UART_Enable_Rx(void)
{
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);
	 HAL_UART_Receive_IT(&huart1,(uint8_t *)&RxData,1);
}
