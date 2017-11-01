#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

void USART1_Init (void);
int main (void)
{
	//Initialization USART1 //
	USART1_Init();
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
	while(1)
	{
		;
	}
}
void USART1_Init ()	
{	
	// Enable Clock //
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1|RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOC,ENABLE);
	
	// Initialization GPIO PA9_Tx //
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	// Initialization GPIO PA10_RX //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	// Initialization GPIO PC13_Led //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	// Initialization USART1 //
	USART_InitTypeDef USART1_InitStructure;
	USART1_InitStructure.USART_BaudRate = 9600;
	USART1_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART1_InitStructure.USART_WordLength = USART_WordLength_9b;
	USART1_InitStructure.USART_Parity = USART_Parity_Odd;
	USART1_InitStructure.USART_StopBits = USART_StopBits_1;
	USART1_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	USART_Init(USART1,&USART1_InitStructure);	
	USART_Cmd(USART1,ENABLE);
	// Enable RXNE Interrupt //
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE); 	// cho phep ngat khi nhan duoc 1 ky tu
	// Enable usart1 Interrupt //
	NVIC_EnableIRQ(USART1_IRQn);	// cho phep usart1 ngat
}
void USART1_IRQHandler ()
{
	if (USART_GetFlagStatus(USART1,USART_IT_RXNE) != RESET) // Cho doc xong 
	{
		char GetChar = USART_ReceiveData(USART1); // Doc vao 
		if ((char)GetChar == 'o') // So sanh voi ky tu 'o'
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_13); 	// Sang led
			USART_SendData(USART1,'O');			// Gui ra ky tu 'O' bao den sang
		}
		else
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_13);	// Tat led
			USART_SendData(USART1,'F');			// Gui ra ky tu 'F' bao den tat
		}
	}
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) // Cho gui xong
	{
	}	
}