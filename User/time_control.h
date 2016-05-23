#ifndef _TIME_CONTROL_H
#define _TIME_CONTROL_H

#include "stm32f10x.h"

void NVIC_Config(void);
void EXIT_NVIC_Init(void);
void EXTI_Config(void);
void GPIO_EXTI_Config(void);
void TIM5_Int_Init(u16 arr,u16 psc);
void TIM5_NVIC_Init(void);
void TIM2_Int_Init(u16 arr,u16 psc);
void TIM2_NVIC_Init(void);
void TIM7_NVIC_Init(void);
void TIM7_Int_Init(u16 arr,u16 psc);

#endif
