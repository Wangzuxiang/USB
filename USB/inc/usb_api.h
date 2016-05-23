#ifndef _USB_API
#define _USB_API

#include "stm32f10x.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "stm32f10x_tim.h"
#include "platform_config.h"
#include "stdio.h"

void RCC_Configuration(void);
void Virtual_Com_Write_Buffer(u8* data_buffer, u8 Nb_bytes);
void USB_Send_Data(u8* data_buffer);

extern u32 count_out;
extern u32 count_in;
extern u8 buffer_out[VIRTUAL_COM_PORT_DATA_SIZE];

#endif
