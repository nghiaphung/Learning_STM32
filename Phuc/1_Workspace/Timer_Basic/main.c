#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"

void Init_GPIO (void);
void Init_TIMER (void);

int main (void)
{	
	Init_GPIO ();
	Init_TIMER ();		
	while(1)
	{	
		;// Cho ngat //
	}
}

void TIM1_UP_IRQHandler (void)
{
	if (TIM_GetITStatus(TIM1,TIM_IT_Update) == SET)
	{				
		if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == SET)
		{
			GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
		}
		else
		{
			GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
		}
	}
	TIM_ClearITPendingBit(TIM1,TIM_IT_Update);								
}		
			
void Init_GPIO (void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	// Khoi dong clock cho Port C
	GPIO_InitTypeDef GPIOC_InitStructure;	// Khoi tao khai bao GPIO
	GPIOC_InitStructure.GPIO_Pin = GPIO_Pin_13;	// Khai bao la chan so 13
	GPIOC_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	// Khai bao toc do la 50Mhz
	GPIOC_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// Khai bao o che do Output Push-Pull
	GPIO_Init(GPIOC,&GPIOC_InitStructure);	// Khoi tao GPIOC theo nhu da khai bao

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	// Khoi dong clock cho Port C
	GPIO_InitTypeDef GPIOA_InitStructure;	// Khoi tao khai bao GPIO
	GPIOA_InitStructure.GPIO_Pin = GPIO_Pin_0;	// Khai bao la chan so 0
	GPIOA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	// Khai bao toc do la 50Mhz
	GPIOA_InitStructure.GPIO_Mode = GPIO_Mode_IPU	;	// Khai bao o che do Input Push-up
	GPIO_Init(GPIOA,&GPIOA_InitStructure);	// Khoi tao GPIOA theo nhu da khai bao		
}			

void Init_TIMER (void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
    RCC_ClocksTypeDef RCC_ClockStatus;	// RCC_ClocksStatus: pointer to an RCC_ClocksTypeDef structure //
    // Get clock status //
    RCC_GetClocksFreq(&RCC_ClockStatus);												
//    // Gets PCLK1_Frequency //
//    uint32_t PCLK2_Frequency = RCC_ClockStatus.PCLK2_Frequency; 			
    // Calculate pre-scaler //
    uint16_t TIM1_Prescaler = ((RCC_ClockStatus.PCLK2_Frequency/10000)-1); // = 7199 ~ 10 ms; Do dem bat dau tu 0 //
    // setup timer's param //
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;		
    TIM_TimeBaseInitStruct.TIM_Period = (10000-1); // 9999 ~ 10000*100us = 1s; Do dem bat dau tu 0 //
    TIM_TimeBaseInitStruct.TIM_Prescaler = TIM1_Prescaler;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	// Start TIM1
	TIM_Cmd(TIM1, ENABLE);
    //  initialize NVIC //
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM1_UP_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_Init(&NVIC_InitStruct);
}
