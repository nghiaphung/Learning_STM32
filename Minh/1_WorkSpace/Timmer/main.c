#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "Timer_init.h"
#include "GPIO_initt.h"



int main (){
	
	GPIO_initt();
	Timmer_Init();
	GPIO_SetBits(GPIOC,GPIO_Pin_13);

	while(1){
	}
}
	
