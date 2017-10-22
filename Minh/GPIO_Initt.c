#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "GPIO_initt.h"
void GPIO_initt (void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_InitStrust;
	GPIO_InitStrust.GPIO_Mode= GPIO_Mode_Out_PP;
	GPIO_InitStrust.GPIO_Pin= GPIO_Pin_13;
	GPIO_InitStrust.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStrust);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStrusts;
  GPIO_InitStrusts.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStrusts.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStrusts.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStrusts);
	
	
	
}