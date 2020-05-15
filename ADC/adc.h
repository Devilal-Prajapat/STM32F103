/*
 * adc.h
 *
 *  Created on: May 15, 2020
 *      Author: Devilal
 */

#ifndef ADC_H_
#define ADC_H_

#include "main.h"


extern ADC_HandleTypeDef hadc1;

void ADC_Init(void);
HAL_StatusTypeDef Read_ADC(uint32_t *adc_values);

#endif /* ADC_H_ */
