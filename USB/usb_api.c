#include "usb_api.h"

/*************************************************
o����y: void RCC_Configuration(void)
1|?��: ?��??o������?��???? ????
2?��y: ?T
����??: ?T
**************************************************/
void RCC_Configuration(void)
{
  ErrorStatus HSEStartUpStatus;                    //?����?��a2????��?�쨬????�����䨬????����?��?
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_DeInit();                                    //?��??RCC��a2?������???��??�¦�???��??��
  RCC_HSEConfig(RCC_HSE_ON);                       //�䨰?a��a2????��?��??
  HSEStartUpStatus = RCC_WaitForHSEStartUp();      //�̨���y��a2????������?����?��?o?
  if(HSEStartUpStatus == SUCCESS)                  //��a2????������?����??-��?��eo?
  {
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); //?a??FLASH?��?��?o3?1|?����??��?��FLASH��??����??��?����D3��D��?D��?D?��?��?����.????��oRCC3?��??������o����y��???��?����?��?e????o��
    FLASH_SetLatency(FLASH_Latency_2);                    //flash2�����¦�??������
      	
    RCC_HCLKConfig(RCC_SYSCLK_Div1);               //????AHB(HCLK)����?���̨�����==SYSCLK
    RCC_PCLK2Config(RCC_HCLK_Div1);                //????APB2(PCLK2)?��==AHB����?��
    RCC_PCLK1Config(RCC_HCLK_Div2);                //????APB1(PCLK1)?��==AHB1/2����?��
         
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);  //????PLL����?�� == ��a2????��?�쨬?����?�� * 9 = 72MHz
    RCC_PLLCmd(ENABLE);                                   //��1?��PLL����?��
   
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)    //�̨���yPLL����?��?��D��
    {
    }
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);            //?????�̨�3����?�� = PLL����?��
    while(RCC_GetSYSCLKSource() != 0x08)                  //?��2��PLL����?����?��?����?a?�̨�3����?��
    {
    }
  }
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);    //?��D��AFIO����?��

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
