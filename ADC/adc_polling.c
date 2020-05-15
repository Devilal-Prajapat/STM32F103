/*
 * adc_polling.c
 *
 *  Created on: May 15, 2020
 *      Author: Devilal
 */

#include "adc.h"

ADC_HandleTypeDef hadc1;

void ADC_Init(void)
{
	ADC_ChannelConfTypeDef Channel_config;
	hadc1.Instance = ADC1;
	hadc1.Init.ContinuousConvMode = ENABLE;
	hadc1.Init.ScanConvMode = ENABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.NbrOfConversion = 2;

	if(HAL_ADC_Init(&hadc1)!=HAL_OK)
	{
		Error_Handler();
	}

	Channel_config.Rank = ADC_REGULAR_RANK_1;
	Channel_config.Channel = ADC_CHANNEL_0;
	Channel_config.SamplingTime = ADC_SAMPLETIME_13CYCLES_5; //  for 12 bit minimum this required
	if(HAL_ADC_ConfigChannel(&hadc1,&Channel_config)!=HAL_OK)
	{
		Error_Handler();
	}

	Channel_config.Rank = ADC_REGULAR_RANK_2;
	Channel_config.Channel = ADC_CHANNEL_1;
	Channel_config.SamplingTime = ADC_SAMPLETIME_13CYCLES_5; //  for 12 bit minimum this required
	if(HAL_ADC_ConfigChannel(&hadc1,&Channel_config)!=HAL_OK)
	{
		Error_Handler();
	}


	/*
	 * 	Implement HAL_ADC_MspInit(ADC_HandleTypeDef* hadc) in msp.c or in this file
	 * 	I am implementing in this file
	 */
}

HAL_StatusTypeDef Read_ADC(uint32_t *adc_values)
{
	HAL_StatusTypeDef status;
	HAL_ADC_Start(&hadc1);
	if (HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY) == HAL_OK)
	{
		adc_values[0] = HAL_ADC_GetValue(&hadc1); /* Gets 3V3 */
		HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
		adc_values[1] = HAL_ADC_GetValue(&hadc1); /* Gets GND */
		status = HAL_OK;
	}
	else
	{
		status = HAL_ERROR;
	}
	HAL_ADC_Stop(&hadc1);
	return status;
}

void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
	if(hadc->Instance == ADC1)
	{
		GPIO_InitTypeDef Gpio_InitStruct;
		__HAL_RCC_ADC1_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();

		Gpio_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
		Gpio_InitStruct.Mode = GPIO_MODE_ANALOG;
		Gpio_InitStruct.Pull = GPIO_NOPULL;
		Gpio_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOA,&Gpio_InitStruct);
	}
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{
	if(hadc->Instance == ADC1)
	{
		__HAL_RCC_ADC1_CLK_DISABLE();

		/**ADC1 GPIO Configuration
		PA0-WKUP     ------> ADC1_IN0
		PA1     ------> ADC1_IN1
		*/
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0|GPIO_PIN_1);
	}
}
