/* Thoi gian sang tat led chi uoc luong, sau nay se dung timer de tinh chinh xac
	 Khi nhan nut led se sang-tat mot luc, neu con giu nut nhan nua thi se led se sang luon mot luc roi lap lai
	 Khi khong co nhan nut thi led se tat*/

#include <stm32f10x.h>			
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

void BLINK_LED (void);	    	// Tao ham BLINK_LED
void KHOI_TAO_GPIO (void);	  // Tao ham KHOI_TAO_GPIO

int main (void)
	{	
		KHOI_TAO_GPIO();
		while(1)
			{	
				BLINK_LED();				
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
	void BLINK_LED (void)
	{
		u8 ReadValue = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);	// Doc gia tri phim nhan vao
		if (ReadValue == RESET)				 											  	// Neu duoc nhan
			{		
				u8 j = 0;
				while(j<=5)																				// Lap lai (j+1) lan
					{		
						for(int i=0; i<200000; i++)											// Thoi gian sang Led (sau nay se dung timer)
						
						GPIO_ResetBits(GPIOC,GPIO_Pin_13);							// Dua PC13 ve 0 de sang Led
						
						for(int i=0; i<200000; i++)											// Thoi gian tat Led (sau nay se dung timer)
						GPIO_SetBits(GPIOC,GPIO_Pin_13);								// Dua PC13 len 1 de tat Led
						j++;																						// Tang j len 1 don vi
						
					}				
			}
		ReadValue = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);			
		if (ReadValue == RESET)																	// Neu van con nhan nut
			{
				for(int i=0; i< 4000000; i++)											// Thoi gian sang Led (sau nay se dung timer)
				GPIO_ResetBits(GPIOC,GPIO_Pin_13);								  // Dua PC13 ve 0 de sang Led
			}
		else
			{	
				GPIO_SetBits(GPIOC,GPIO_Pin_13);							 		  // Dua PC13 len 1 de tat Led
			}
	}			