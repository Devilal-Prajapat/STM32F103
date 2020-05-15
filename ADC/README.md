
/*
* include "adc.h" file in main.c
* I am using ADC1 (channel 1 & 2)
* Call ADC_Init() in main.c file
* Call  HAL_ADCEx_Calibration_Start(&hadc1).
* Call Read_ADC(uint32_t * adc_values) to read the adc data. 
* Example :
 uint32_t adc_vals[2];
 Read_ADC(&adc_vals[0]);  
  * adc_vals[0]---> channel 1 data 
  * adc_vals[1]---> channel 2 data
  */
 

