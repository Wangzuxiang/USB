/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : main.c
* Author             : MCD Application Team
* Version            : V3.2.1
* Date               : 07/05/2010
* Description        : Virtual Com Port Demo main file
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "stm32f10x_tim.h"
#include "platform_config.h"
#include "led.h"
#include "pwm.h"
#include "usb_api.h"
#include "manipulators_control.h"
#include "time_control.h"
#include "stdio.h"
#include "dectect.h"
#include "uart.h"

//#define TEST
//#define WORK

void set_throw_pos(void);
void set_crawlay_pos(void);
void set_lay_pos(void);
void set_craw_pos(void);
void set_return(void);

//Global 
int flag = 0;
int run_cnt = 1;
float Fre;
float Pau;

unsigned char buffer_rx[64];
unsigned int buffer_count = 0;



int main(void)
{
	count_out = 0;
	SystemInit();
	LED_GPIO_Config();
	RCC_Configuration();
	PWM_init();
	Set_USBClock();
	USB_Interrupts_Config();
	USB_Init();
	LED(1);
		
	NVIC_Config();
	NVIC_uart();
	GPIO_EXTI_Config();
	EXTI_Config();
	TIM2_Init_All();
	USART1_Config();
	
	LED(0);
	
	while (bDeviceState != CONFIGURED);

	while(1) 
	{
			printf("\rtest\n");
			if(count_out != 0)
			{
					count_out = 0;
				  printf("recieve data:%c", buffer_out[0]+1);
			}
	}
}
	







