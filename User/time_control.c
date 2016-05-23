#include "time_control.h"


void NVIC_Config(void)
{	
	EXIT_NVIC_Init();
	TIM7_NVIC_Init();
}

void EXIT_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
}

void EXTI_Config(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOG,GPIO_PinSource0);
	EXTI_ClearITPendingBit(EXTI_Line0);
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}	

void GPIO_EXTI_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOG,ENABLE);	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOG,&GPIO_InitStructure);	
}

void TIM7_NVIC_Init(void)
{
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;
		NVIC_Init(&NVIC_InitStructure);
}

void TIM7_Int_Init(u16 arr,u16 psc) 
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); /*  ±÷” πƒ‹ */
		TIM_TimeBaseStructure.TIM_Prescaler = psc;
		TIM_TimeBaseStructure.TIM_ClockDivision = 0;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	
		TIM_TimeBaseStructure.TIM_Period = arr;
		TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
		TIM_TimeBaseInit(TIM7,&TIM_TimeBaseStructure);
		TIM_UpdateRequestConfig(TIM7, TIM_UpdateSource_Regular);
		TIM_Cmd(TIM7,ENABLE);
		TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);
		TIM_ClearFlag(TIM7,TIM_FLAG_Update);
}


