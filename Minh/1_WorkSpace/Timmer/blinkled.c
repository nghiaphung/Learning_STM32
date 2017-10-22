#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "Blinkled.h"
void blinkled(void){
	int i;
	while(1){
		for(i=0;i<100000;i++)
			GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		for(i=0;i<100000;i++)
			GPIO_SetBits(GPIOC,GPIO_Pin_13);
	}
}	