#include "delay.h"

TIM_HandleTypeDef htim1;

void Delay_Init(void)
{
	__HAL_RCC_TIM1_CLK_ENABLE();
	htim1.Instance = TIM6;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.Prescaler = 15;                   /* 16 bit value */
	htim1.Init.Period = 0;                       /* 16 bit value */
	if(HAL_TIM_Base_Init(&htim1)!= HAL_OK)
	{
	Error_Handler();
	}
}

void Delay_MilliSeconds(uint32_t ms)
{		
	while(ms--)
	{
		Delay_MicroSeconds(1000);
	}
}


void Delay_MicroSeconds(uint32_t us)
{
	//	TIM1->SR = 0;                                  /* Status Register */
	//	TIM1->PSC = 31;                                /* Prescaler value */
	//	TIM1->ARR = us;                                /* Any Value 0xFFFF   */
	//	TIM1->CR1 |= TIM_CR1_CEN;                      /* Start the timer counter */
	__HAL_TIM_SetAutoreload(&htim1,us & 0xFFFF);
	htim1.Instance->SR = 0;
	HAL_TIM_Base_Start(&htim1);
	while (!(TIM1->SR & TIM_SR_UIF));                 /* Loop until the update event flag is set */
}

