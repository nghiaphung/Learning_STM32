#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_exti.h"

int Tim_Period = 7199; // Tan so 1KHz; 7199 = (7.2MHz/1KHz -1); do dem tu 0
int Duty_Cycle = 75;
int Brightness;

int main (void)
{	
	// Init Structure//
	GPIO_InitTypeDef GPIOA0_InitStructure;
	GPIO_InitTypeDef GPIOC13_InitStructure;
	TIM_TimeBaseInitTypeDef TIM2_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	// Inint GPIOA0 //
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIOA0_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIOA0_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIOA0_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIOA0_InitStructure);
	// Init GPIOC13 //
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIOC13_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIOC13_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIOC13_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,&GPIOC13_InitStructure);
	// Init time //
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM2_InitStructure.TIM_Prescaler = 9; // Tan so tim2 gio la 7.2MHz = 72/10; Do dem tu 0
	TIM2_InitStructure.TIM_Period = Tim_Period; 
	TIM2_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM2_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	//TIM2_InitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM2_InitStructure);
	// Start time //
	TIM_Cmd(TIM2,ENABLE);
	// PWM Settings //
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = (((Tim_Period + 1) * Duty_Cycle)/100 -1); 
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);
	
while (1)
{
//	// Set LED Brightness from 0 to max //
//	for (Brightness = 0; Brightness <= 3599; Brightness += 10)
//	{						
//		TIM2->CCR1 = Brightness;			
//	}
//	// Set LED Brightness from max to 0 //
//	for (Brightness = 3599; Brightness >= 0; Brightness -= 10)
//	{
//		TIM2->CCR1 = Brightness;			
//	}
}
}