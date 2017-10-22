#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "khoi tao timmer.h"
void Timmer_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
		RCC_ClocksTypeDef RCC_ClockStatus; 							// RCC_ClocksStatus: pointer to an RCC_ClocksTypeDef structure //
		// Get clock status //
		RCC_GetClocksFreq(&RCC_ClockStatus);												
		// Gets PCLK1_Frequency //
		u16 PCLK1_Frequency = RCC_ClockStatus.PCLK1_Frequency; 			
		// Calculate pre-scaler //
		u16 TIM1_Prescaler = ((PCLK1_Frequency/1000000));							  //(TIM1_Prescaler) CLK on 1 us //
		// setup timer's param //
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;		
		TIM_TimeBaseInitStruct.TIM_Period = (1000);
		TIM_TimeBaseInitStruct.TIM_Prescaler = TIM1_Prescaler;
		TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
		TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);
		TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
		//  initialize NVIC //
		NVIC_InitTypeDef NVIC_InitStruct;
		NVIC_InitStruct.NVIC_IRQChannel = TIM1_CC_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
		NVIC_Init(&NVIC_InitStruct);
}