#ifndef _UART_H
#define _UART_H

#include "stm32f10x.h"
#define RCC_USART	RCC_APB2Periph_USART1|RCC_APB2Periph_AFIO

void USART1_Config(void);
void USART_Putc(char c);
void NVIC_uart(void);

#endif

