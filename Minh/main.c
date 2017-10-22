#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "khoi tao timmer.h"
#include "GPIO_initt.h"
int statusled;

void checktimmer (void){
	if (TIM_GetITStatus(TIM1,TIM_IT_Update)==SET){
		if (statusled==SET){
			GPIO_ResetBits(GPIOA,GPIO_Pin_0);
		}
		else{
			GPIO_SetBits(GPIOA,GPIO_Pin_0);
		}
	}
}
int main (){
	
	GPIO_initt();
	Timmer_Init();
	GPIO_SetBits(GPIOA,GPIO_Pin_0);
	statusled=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
	while(1){
	}
}
	
