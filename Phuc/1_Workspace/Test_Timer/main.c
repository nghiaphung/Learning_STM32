#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"

void LED (void);
RCC_ClocksTypeDef RCC_ClockStatus; 							// RCC_ClocksStatus: pointer to an RCC_ClocksTypeDef structure //
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;	
NVIC_InitTypeDef NVIC_InitStruct;
void KHOI_TAO_GPIO (void);
void Blink_Led (void);
void Button_Led (void);
u8 ReadValue = 0; 

int main (void)
	{
		// Get clock status //
		RCC_GetClocksFreq(&RCC_ClockStatus);												
		// Gets PCLK1_Frequency //
		u16 PCLK1_Frequency = RCC_ClockStatus.PCLK1_Frequency; 			
		// Calculate pre-scaler //
		u16 TIM1_Prescaler = PCLK1_Frequency/1000000;							  //(TIM1_Prescaler) CLK on 1 us //
		// setup timer's param //				
		TIM_TimeBaseInitStruct.TIM_Period = 1000;
		TIM_TimeBaseInitStruct.TIM_Prescaler = TIM1_Prescaler;
		TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
		TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);
		TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
		//  initialize NVIC //
		NVIC_InitStruct.NVIC_IRQChannel = TIM1_CC_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
		NVIC_Init(&NVIC_InitStruct);							
				
		while(1)
			{	
				
				}
		}
	
		void KHOI_TAO_GPIO (void)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // Khoi dong clock cho Port C
		GPIO_InitTypeDef GPIOC_InitStructure;									// Khoi tao khai bao GPIO
		GPIOC_InitStructure.GPIO_Pin = GPIO_Pin_13;						// Khai bao la chan so 13
		GPIOC_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		// Khai bao toc do la 50Mhz
		GPIOC_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			// Khai bao o che do Output Push-Pull
		GPIO_Init(GPIOC,&GPIOC_InitStructure);								// Khoi tao GPIOC theo nhu da khai bao 
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // Khoi dong clock cho Port C
		GPIO_InitTypeDef GPIOA_InitStructure;									// Khoi tao khai bao GPIO
		GPIOA_InitStructure.GPIO_Pin = GPIO_Pin_0;						// Khai bao la chan so 0
		GPIOA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		// Khai bao toc do la 50Mhz
		GPIOA_InitStructure.GPIO_Mode = GPIO_Mode_IPU	;				// Khai bao o che do Input Push-up
		GPIO_Init(GPIOA,&GPIOA_InitStructure);								// Khoi tao GPIOA theo nhu da khai bao 
	}

		
		