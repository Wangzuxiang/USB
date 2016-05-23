#include "uart.h"

void USART1_Config()
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;		
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);		

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable; 
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low; 
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge; 
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable; 
 
	USART_ClockInit(USART1, &USART_ClockInitStructure); 

  USART_InitStructure.USART_BaudRate=115200; 		
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;
	USART_Init(USART1,&USART_InitStructure);
	USART_Cmd(USART1,ENABLE); 
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	//USART_ITConfig(USART1,USART_IT_TXE,ENABLE);
	USART_ClearFlag(USART1,USART_FLAG_TXE); 
	USART_ClearFlag(USART1,USART_FLAG_RXNE);
}

void NVIC_uart(void)
{              
  NVIC_InitTypeDef NVIC_InitStructure;    
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;         
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void USART_Putc(char c)
{
		USART_SendData(USART1,c);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
}

