#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "Timer_init.h"
void Timmer_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
		RCC_ClocksTypeDef RCC_ClockStatus; 							// RCC_ClocksStatus: pointer to an RCC_ClocksTypeDef structure //
		// Get clock status //
		RCC_GetClocksFreq(&RCC_ClockStatus);												
		// Gets PCLK1_Frequency //
		uint32_t PCLK2_Frequency = RCC_ClockStatus.PCLK2_Frequency; 			
		// Calculate pre-scaler //
		uint32_t TIM1_Prescaler = ((PCLK2_Frequency/1000000));							  //(TIM1_Prescaler) CLK on 1 us //
		// setup timer's param //
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;		
		TIM_TimeBaseInitStruct.TIM_Period = (10000);
		TIM_TimeBaseInitStruct.TIM_Prescaler = TIM1_Prescaler*100;
		TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
		TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);
		TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
		TIM_Cmd(TIM1,ENABLE); // Enable TIM1
		//  initialize NVIC //
		NVIC_InitTypeDef NVIC_InitStruct;
		NVIC_InitStruct.NVIC_IRQChannel = TIM1_UP_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
		NVIC_Init(&NVIC_InitStruct);
}

	void TIM1_UP_IRQHandler (void){
	if (TIM_GetITStatus(TIM1,TIM_IT_Update)==SET){
		if (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)==SET){
			GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		}
		else{
			GPIO_SetBits(GPIOC,GPIO_Pin_13);
		}
	
	}
	TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
}