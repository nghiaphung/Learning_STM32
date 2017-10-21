#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"

void LED (void);

	

void KHOI_TAO_GPIO (void);
void KHOI_TAO_TIMER (void);
void Blink_Led (void);

//int x = 0;
int main (void)
{	
    KHOI_TAO_GPIO();
    KHOI_TAO_TIMER();
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

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE); // Khoi dong clock cho Port C
    GPIO_InitTypeDef GPIOA_InitStructure;									// Khoi tao khai bao GPIO
    GPIOA_InitStructure.GPIO_Pin = GPIO_Pin_0;						// Khai bao la chan so 0
    GPIOA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		// Khai bao toc do la 50Mhz
    GPIOA_InitStructure.GPIO_Mode = GPIO_Mode_IPU	;				// Khai bao o che do Input Push-up
    GPIO_Init(GPIOA,&GPIOA_InitStructure);								// Khoi tao GPIOA theo nhu da khai bao 
}		
	
	

void KHOI_TAO_TIMER (void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
    RCC_ClocksTypeDef RCC_ClockStatus; 							// RCC_ClocksStatus: pointer to an RCC_ClocksTypeDef structure //
    // Get clock status //
    RCC_GetClocksFreq(&RCC_ClockStatus);												
    // Gets PCLK1_Frequency //
    uint16_t PCLK1_Frequency = RCC_ClockStatus.PCLK1_Frequency; 			
    // Calculate pre-scaler //
    uint16_t TIM1_Prescaler = ((PCLK1_Frequency/1000000)-1);							  //(TIM1_Prescaler) CLK on 1 us //
    // setup timer's param //
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;		
    TIM_TimeBaseInitStruct.TIM_Period = (1000-1);
    TIM_TimeBaseInitStruct.TIM_Prescaler = TIM1_Prescaler;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
    //  initialize NVIC //
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM1_UP_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_Init(&NVIC_InitStruct);
}
	
	
void Blink_Led (void)
{
    if (0x01 == GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13))
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
    else
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
            
}
	
void TIM1_UP_IRQHandler	(void)
{
    if (SET == TIM_GetITStatus (TIM1, TIM_IT_Update))
        Blink_Led();
    TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
}