/*----------------------------------------------------------------------------
 * Name:    CanDemo.c
 * Purpose: CAN example for STM32
 * Version: V1.00
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * Copyright (c) 2005-2007 Keil Software. All rights reserved.
 *----------------------------------------------------------------------------*/
#include "platform_config.h"
#include "platform_init.h"
#include "stm32f10x.h"                         // STM32F10x Library Definitions  
#include "LCD.h"                               // LCD function prototypes
#include "stdio.h"
#include "SerialProtocol.h"
#include "CanProtocol.h"

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


extern CanTxMsg TxMessage;
extern CanRxMsg RxMessage;
extern __IO uint8_t CanRxMessageCounter;
extern uint8_t CanRxMsgFlg;
extern USART_MeaasgeTypedef  USART_Meaasge;

/* Private function prototypes -----------------------------------------------*/

/*----------------------------------------------------------------------------
  insert a delay time.
 *----------------------------------------------------------------------------*/
void delay(unsigned int nCount)	
{
  for(; nCount != 0; nCount--);
}

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void)  
{
	char SentMsgCounter = 0;
	char MsgBuf[15];
        
  /* NVIC configuration */
  NVIC_Config();
	
	/* USART configuration */
	UART_Config();
	
  /* CAN configuration */
  CAN_Config();

  /* IT Configuration for CAN1 */  
  CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
	
	/* LCD Initialization */
  lcd_init  ();                                   // initialise LCD
  delay(4500000);                                 // Wait for initial display (~5s)

  lcd_clear ();
  lcd_print ("CAN at 500kbit/s");
	printf("\r\nCan Demo test:\r\n");
	
  while(1)
	{ 
		Serial_cmd_parse();
		
		Can_Process();
		
//		for(SentMsgCounter = 0; SentMsgCounter <100; SentMsgCounter++ )
//		{
//			TxMessage.Data[0] = SentMsgCounter;
//			TxMessage.Data[1] = 0x11;
//			TxMessage.Data[2] = 0x22;
//			TxMessage.Data[3] = 0x33;
//			TxMessage.Data[4] = 0x44;
//			TxMessage.Data[5] = 0x55;
//			TxMessage.Data[6] = 0x66;
//			TxMessage.Data[7] = 0x77;
//			CAN_Transmit(CAN1, &TxMessage);
//			delay (450000);
//		}
	}
} 




/***************************** END OF FILE ************************************/
