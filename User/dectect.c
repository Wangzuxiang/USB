#include "dectect.h"

void TIM2_GPIO_RCC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void TIM2_Init(void)
{
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0x00;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_PWMIConfig(TIM2,&TIM_ICInitStructure);
	
	TIM_SelectInputTrigger(TIM2,TIM_TS_TI2FP2);
	
	TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Reset);
	
	TIM_SelectMasterSlaveMode(TIM2, TIM_MasterSlaveMode_Enable);
	TIM_Cmd(TIM2, ENABLE);
}

void TIM2_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
}

void TIM2_Init_All(void)
{
		TIM2_NVIC_Init();
		TIM2_Init();
		TIM2_GPIO_RCC_Init();
}

unsigned int cap_dec(void)
{
		float tmp1;
		float tmp2;
		unsigned int cap;
		TIM_ITConfig(TIM2,TIM_IT_CC2,ENABLE);	
		delay(10000);
		tmp1 = Fre / 1000.0;
		tmp2 = (32400.0/(tmp1*tmp1))*3.6;
		cap = (unsigned int)(tmp2);
		return cap;						
}



