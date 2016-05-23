#include "led.h"

/*
 * ��������LED_GPIO_Config
 * ����  ������LED�õ���I/O��
 * ����  ����
 * ���  ����
 */
void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOG, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOG, &GPIO_InitStructure);

	GPIO_SetBits(GPIOG, GPIO_Pin_8);	 // turn off all led
}

void LED(char i)
{
	GPIO_WriteBit(GPIOG,GPIO_Pin_8,(BitAction)i);	
}
 
