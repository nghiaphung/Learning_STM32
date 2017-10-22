#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
void buttonblinkled (void)
	{
		u8 ReadValue = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);	// Doc gia tri phim nhan vao
		if (ReadValue == RESET)				 											  	// Neu duoc nhan
			{		
				u8 j = 0;
				while(j<=10)																				// Lap lai (j+1) lan
					{		
						for(int i=0; i<200000; i++)											// Thoi gian sang Led (sau nay se dung timer)
						GPIO_ResetBits(GPIOC,GPIO_Pin_13);							// Dua PC13 ve 0 de sang Led
						for(int i=0; i<200000; i++)											// Thoi gian tat Led (sau nay se dung timer)
						GPIO_SetBits(GPIOC,GPIO_Pin_13);								// Dua PC13 len 1 de tat Led
						j++;																						// Tang j len 1 don vi
					}				
			}				
		if (ReadValue == RESET)																	// Neu van con nhan nut
			{
				for(int i=0; i< 20000000; i++)											// Thoi gian sang Led (sau nay se dung timer)
				GPIO_ResetBits(GPIOC,GPIO_Pin_13);								  // Dua PC13 ve 0 de sang Led
			}
		else
			{	
				GPIO_SetBits(GPIOC,GPIO_Pin_13);							 		  // Dua PC13 len 1 de tat Led
			}
		}