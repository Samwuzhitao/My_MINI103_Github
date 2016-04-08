/*
*******************************************************************************
  Copyright (C), 2010-2012, timll Tech. Co., Ltd.
  FileName      : STM32_F105-07_F2xx_USB-Host-Device_Lib_V2.0.0/Project/USB_Device_Examples/HID/main.c
  Author        : lichy       
  Version       : 1.0.0     
  Date          : 2011/10/31
  Description   : The HID example uses the USER1 & USER2 embedded in the devkit1207
                  evaluation boards to emulate the Mouse directions (ight & up)
  Function List : 
  History       :
  <author>      : lichy       
  <time>        : 2011/10/28
  <version>     : 1.0.0 	
  <desc>        : build this moudle				 
*******************************************************************************
*/   

/* Includes ------------------------------------------------------------------*/ 
#include  "stdio.h"
#include  <stdarg.h>
#include  "usbd_hid_core.h"
#include  "usbd_usr.h"
#include  "usbd_desc.h"
#include  "stm32_eval.h"
#include  "DAP_config.h"
#include  "DAP.h"


#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN USB_OTG_CORE_HANDLE  USB_OTG_dev __ALIGN_END;

static volatile uint8_t  USB_RequestFlag;       // Request  Buffer Usage Flag
volatile uint32_t USB_RequestIn;                // Request  Buffer In  Index
static volatile uint32_t USB_RequestOut;        // Request  Buffer Out Index

static volatile uint8_t  USB_ResponseIdle;      // Response Buffer Idle  Flag
static volatile uint8_t  USB_ResponseFlag;      // Response Buffer Usage Flag
volatile uint32_t USB_ResponseIn;               // Response Buffer In  Index
volatile uint32_t USB_ResponseOut;              // Response Buffer Out Index

uint8_t  USB_Request [DAP_PACKET_COUNT][DAP_PACKET_SIZE];  // Request  Buffer  //4K大小
uint8_t  USB_Response[DAP_PACKET_COUNT][DAP_PACKET_SIZE];  // Response Buffer

/******************************************************************************************/
// USB HID Callback: when system initializes
void usbd_hid_init (void)
{
	USB_RequestFlag   = 0;
	USB_RequestIn     = 0;
	USB_RequestOut    = 0;
	USB_ResponseIdle  = 1;
	USB_ResponseFlag  = 0;
	USB_ResponseIn    = 0;
	USB_ResponseOut   = 0;
}
/**************************************************************************************/
// 准备数据发送处理结果到 PC 端数据函数
/**************************************************************************************/
// USB HID Callback: when data needs to be prepared for the host
int usbd_hid_get_report (uint8_t rtype, uint8_t rid, uint8_t *buf, uint8_t req)
{
	switch (rtype)
	{
	  case HID_REPORT_INPUT:
		switch (req)
		{
		case USBD_HID_REQ_EP_CTRL:
		case USBD_HID_REQ_PERIOD_UPDATE:
			break;
		case USBD_HID_REQ_EP_INT:
			if ((USB_ResponseOut != USB_ResponseIn) || USB_ResponseFlag)
			{
				memcpy(buf, USB_Response[USB_ResponseOut], DAP_PACKET_SIZE);
				printf("USB_Response Out Index: %d \r\n",USB_ResponseOut);
				//printf("USB_Response addr: %d : %d %d %d %d \r\n",(USB_Response[USB_ResponseOut]),USB_Response[USB_ResponseOut][0],USB_Response[USB_ResponseOut][1],USB_Response[USB_ResponseOut][2],USB_Response[USB_ResponseOut][3]);
				USB_ResponseOut++;
				if (USB_ResponseOut == DAP_PACKET_COUNT)
				{
					USB_ResponseOut = 0;
				}
				if (USB_ResponseOut == USB_ResponseIn)
				{
					USB_ResponseFlag = 0;
				}
				return (DAP_PACKET_SIZE);
			}
			else
			{
				USB_ResponseIdle = 1;
			}
			break;
		}
		break;
	case HID_REPORT_FEATURE:
		break;
	}
	return (0);
}

/**************************************************************************************/
// 接收 PC 端数据函数,并存放在 USB_Request[USB_RequestIn] 中
/**************************************************************************************/
// USB HID Callback: when data is received from the host
void usbd_hid_set_report (uint8_t rtype, uint8_t rid, uint8_t *buf, int len, uint8_t req)
{
	switch (rtype)
	{
	case HID_REPORT_OUTPUT:
		if (len == 0)
			break;
		if (buf[0] == ID_DAP_TransferAbort)
		{
			DAP_TransferAbort = 1;
			break;
		}
		if (USB_RequestFlag && (USB_RequestIn == USB_RequestOut))
		{
			break;  // Discard packet when buffer is full
		}
		// Store data into request packet buffer
		memcpy(USB_Request[USB_RequestIn], buf, len);
		printf(" USB_Request Index  : %d   ",USB_RequestIn);
		printf(" USB_Request buffer : %d %d %d %d \r\n",USB_Request[USB_RequestIn][0],USB_Request[USB_RequestIn][1],USB_Request[USB_RequestIn][2],USB_Request[USB_RequestIn][3]);
		USB_RequestIn++;
		if (USB_RequestIn == DAP_PACKET_COUNT)
		{
			USB_RequestIn = 0;
		}
		if (USB_RequestIn == USB_RequestOut)
		{
			USB_RequestFlag = 1;
		}
		break;
	case HID_REPORT_FEATURE:
		break;
	}
}

// Process USB HID Data
void usbd_hid_process (void)
{
	uint32_t n;

	// Process pending requests
	if ((USB_RequestOut != USB_RequestIn) || USB_RequestFlag)
	{
		// Process DAP Command and prepare response
		DAP_ProcessCommand(USB_Request[USB_RequestOut], USB_Response[USB_ResponseIn]);
		// Update request index and flag
		/***************************************************************************/
		n = USB_RequestOut + 1;
		
		if (n == DAP_PACKET_COUNT)
		{
			n = 0;
		}
		USB_RequestOut = n;
		if (USB_RequestOut == USB_RequestIn)
		{
			USB_RequestFlag = 0;
		}
		//printf(" USB_ResponseIdle : %d \r\n",USB_ResponseIdle);
		if (USB_ResponseIdle)
		{
			// Request that data is send back to host
			USB_ResponseIdle = 0;
			// usbd_hid_get_report_trigger(0, USB_Response[USB_ResponseIn], DAP_PACKET_SIZE);
			// 此处编写发送函数
			DCD_EP_Tx (&USB_OTG_dev, HID_IN_EP, USB_Response[USB_ResponseIn], 64);
		  //printf(" USB_Response Index : %d   ",USB_ResponseIn);
			//printf(" USB_Response report: %d %d %d %d  \r\n",USB_Response[USB_ResponseIn][0],USB_Response[USB_ResponseIn][1],USB_Response[USB_ResponseIn][2],USB_Response[USB_ResponseIn][3]);
			//printf(" USBD_HID_SendReport \r\n");
			
		}
		else
		{
			// Update response index and flag
			n = USB_ResponseIn + 1;
			if (n == DAP_PACKET_COUNT)
			{
				n = 0;
			}
			USB_ResponseIn = n;
			if (USB_ResponseIn == USB_ResponseOut)
			{
				USB_ResponseFlag = 1;
			}
		}
	}
}

/*********************************************************************/
void My_Uart_init()
{
  USART_InitTypeDef USART_InitStructure;
  
  /* EVAL_COM1 default configuration */
  /* EVAL_COM1 configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - Parity Odd
        - Hardware flow control disabled
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_Odd;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  /* Configure and enable the USART */
  STM_EVAL_COMInit(COM1, &USART_InitStructure);
		
	USART_Cmd(USART3, ENABLE);
}

int fputc(int ch, FILE *f)
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
  //HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 0xFFFF);
  USART_SendData(USART3,(uint8_t)ch);  
  while(USART_GetFlagStatus(USART3, USART_FLAG_TXE)== RESET );  
  return ch; 
}
/**
  * @brief  Program entry point
  * @param  None
  * @retval None
  */
int main(void)
{
  __IO uint32_t i = 0;

  /*!< At this stage the microcontroller clock setting is already configured, 
  this is done through SystemInit() function which is called from startup
  file (startup_stm32fxxx_xx.s) before to branch to application main.
  To reconfigure the default setting of SystemInit() function, refer to
  system_stm32fxxx.c file
  */  
	My_Uart_init();

	DAP_Setup();
	
	Delayms(100);				        // Wait for 200ms
	LED_RUNNING_OUT(1);			    // Turn on LEDs
	LED_CONNECTED_OUT(1);
	
  USBD_Init(&USB_OTG_dev,
            USB_OTG_HS_CORE_ID,
            &USR_desc, 
            &USBD_HID_cb, 
            &USR_cb);
						
	Delayms(100);				        // Wait for 100ms
	LED_RUNNING_OUT(0);			    // Turn off LEDs
	LED_CONNECTED_OUT(0);		
	
  while (1)
  {
		usbd_hid_process ();
		
  }
} 






/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
