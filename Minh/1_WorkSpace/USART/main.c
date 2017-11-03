#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
void USART1_Init(void);
void GPIOC_Init(void);

int main (void){
	GPIOC_Init();
	USART1_Init();
	while(1){
	}
	
}
void GPIOC_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_Init_Struct;
	GPIO_Init_Struct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init_Struct.GPIO_Pin=GPIO_Pin_13;
	GPIO_Init_Struct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_Init_Struct);
}
void USART1_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIOA_Init_Struct;
	
	GPIOA_Init_Struct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIOA_Init_Struct.GPIO_Pin=GPIO_Pin_9;
	GPIOA_Init_Struct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIOA_Init_Struct);
	
	GPIOA_Init_Struct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIOA_Init_Struct.GPIO_Pin=GPIO_Pin_10;
	GPIOA_Init_Struct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOA_Init_Struct);
	
	USART_InitTypeDef USART1_Init_Struct;
	USART1_Init_Struct.USART_BaudRate=9600;
	USART1_Init_Struct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART1_Init_Struct.USART_StopBits=USART_StopBits_1;
	USART1_Init_Struct.USART_Parity=USART_Parity_No;
	USART1_Init_Struct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART1_Init_Struct.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART1,&USART1_Init_Struct);
	USART_Cmd(USART1,ENABLE);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	NVIC_EnableIRQ(USART1_IRQn);
}
void USART1_IRQHandler(void){
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
	if (USART_GetITStatus(USART1, USART_IT_RXNE)!=RESET){
		if((char)USART_ReceiveData(USART1) =='o'){
			GPIO_ResetBits(GPIOC,GPIO_Pin_13);
			USART_SendData(USART1,'O');
		}
		else{
			GPIO_SetBits(GPIOC,GPIO_Pin_13);
			USART_SendData(USART1,'F');
		}
			
	}
		
}