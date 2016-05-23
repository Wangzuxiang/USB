#include "usb_api.h"

/*************************************************
o‘那y: void RCC_Configuration(void)
1|?邦: ?∩??o赤那㊣?車???? ????
2?那y: ?T
﹞米??: ?T
**************************************************/
void RCC_Configuration(void)
{
  ErrorStatus HSEStartUpStatus;                    //?“辰?赤a2????迄?∫足????‘℅∩足????迄㊣?芍?
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_DeInit();                                    //?∩??RCC赤a2?谷豕㊣???∩??¯米???豕??米
  RCC_HSEConfig(RCC_HSE_ON);                       //∩辰?a赤a2????迄?∫??
  HSEStartUpStatus = RCC_WaitForHSEStartUp();      //米豕∩y赤a2????迄那㊣?車℅?㊣?o?
  if(HSEStartUpStatus == SUCCESS)                  //赤a2????迄那㊣?車辰??-℅?㊣eo?
  {
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); //?a??FLASH?∟?芍?o3?1|?邦㏒??車?迄FLASH米??芍豕??㏒?迄車D3足D辰?D㊣?D?米?車?﹞“.????㏒oRCC3?那??‘℅車o‘那y角???㏒?那㊣?車?e????o車
    FLASH_SetLatency(FLASH_Latency_2);                    //flash2迄℅¯米??車那㊣
      	
    RCC_HCLKConfig(RCC_SYSCLK_Div1);               //????AHB(HCLK)那㊣?車米豕車迆==SYSCLK
    RCC_PCLK2Config(RCC_HCLK_Div1);                //????APB2(PCLK2)?車==AHB那㊣?車
    RCC_PCLK1Config(RCC_HCLK_Div2);                //????APB1(PCLK1)?車==AHB1/2那㊣?車
         
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);  //????PLL那㊣?車 == 赤a2????迄?∫足?那㊣?車 * 9 = 72MHz
    RCC_PLLCmd(ENABLE);                                   //那1?邦PLL那㊣?車
   
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)    //米豕∩yPLL那㊣?車?赤D¯
    {
    }
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);            //?????米赤3那㊣?車 = PLL那㊣?車
    while(RCC_GetSYSCLKSource() != 0x08)                  //?足2谷PLL那㊣?車那?﹞?℅¯?a?米赤3那㊣?車
    {
    }
  }
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);    //?那D赤AFIO那㊣?車

  /* Enable USB_DISCONNECT GPIO clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_DISCONNECT, ENABLE);

  /* Configure USB pull-up pin */
  GPIO_InitStructure.GPIO_Pin = USB_DISCONNECT_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(USB_DISCONNECT, &GPIO_InitStructure);
}

void Virtual_Com_Write_Buffer(u8* data_buffer, u8 Nb_bytes)
{
  /* The USB cable is plugged into the USB-Mini connector */
  u8 b_size = Nb_bytes;
  u8 b_index = 0;
  u8 actual_input_size;
  
  while (b_index < Nb_bytes)
  {
    if (b_size < VIRTUAL_COM_PORT_DATA_SIZE)
    {
      actual_input_size = b_size;
    } 
    else
    {
      actual_input_size = VIRTUAL_COM_PORT_DATA_SIZE;
      
    }
    
    /* wait until the data transmission is finished */
    while (GetEPTxStatus(ENDP1) == EP_TX_VALID); //0x30
    /* Write data to the virtual UART through USB port */
    UserToPMABufferCopy(&(data_buffer[b_index]), ENDP1_TXADDR,actual_input_size);
    SetEPTxCount(ENDP1,actual_input_size); 
    SetEPTxValid(ENDP1);
    
    b_size = b_size - actual_input_size;
    b_index= b_index + actual_input_size; 
  }  

}

void USB_Send_Data(u8* data_buffer)
{ 
  count_in=60;
  UserToPMABufferCopy(data_buffer, ENDP1_TXADDR, count_in);
  SetEPTxCount(ENDP1, count_in);
  SetEPTxValid(ENDP1);
} 

int fputc(int ch, FILE *f)
{
	unsigned char date[1];
	date[0] = (unsigned char)ch; 
	Virtual_Com_Write_Buffer(date, 1);
  return (ch);
}
