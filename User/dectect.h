#ifndef _DECTECT_H
#define _DECTECT_H
#include "stm32f10x.h"
#include "manipulators_control.h"

void TIM2_NVIC_Init(void);
void TIM2_Init(void);
void TIM2_GPIO_RCC_Init(void);
void TIM2_Init_All(void);
unsigned int cap_dec(void);

extern float Fre;

#endif
