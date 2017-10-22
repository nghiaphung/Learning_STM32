#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "buttonled.h"
void buttonled (void){
	while(1){
		if (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))
			GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		else
			GPIO_SetBits(GPIOC,GPIO_Pin_13);
	}
}