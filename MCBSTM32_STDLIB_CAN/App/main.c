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
#include "stm32f10x.h"                         // STM32F10x Library Definitions  
#include "stdio.h"
#include "platform_config.h"
#include "platform_init.h"
#include "SerialProtocol.h"
#include "CanProtocol.h"
#include "ADS1247.h"
#include "LCD.h"                               

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
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
	
	if (SysTick_Config(SystemCoreClock / 1000))
  { 
    /* Capture error */ 
    while (1);
  }
	
  /* NVIC configuration */
  NVIC_Config();
	
	/* USART configuration */
	UART_Config();
	
	/* SPI configuration */
	SPI_Config();

  /* CAN configuration */
  CAN_Config();

  /* IT Configuration for CAN1 */  
  CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
	
	/* LCD Initialization */
  lcd_init  ();                                   // initialise LCD
  delay(4500000);                                 // Wait for initial display (~5s)

	ADS1247_Init();

  lcd_clear ();
  lcd_print ("CAN at 500kbit/s");
	printf("\r\nCan Demo test:\r\n");
	
  while(1)
	{ 	
		int i;
		float x;
		
		Serial_Process();
		
		Can_Process();
		
		
//		for(i=0;i<0x0F;i++)
//		{
////			ADS1247_WriteRegister(i,0x02);
////			Delay(20);
//			printf("The ADS1247 Read Address %2x Register Value is : %2x \r\n",i,ADS1247_ReadRegister(i));
//			Delay(20);
//		}
		x = ADS1247_ReadData();
		printf("The ADS1247 Read Value is : %x \r\n",x);
		printf("The ADS1247 Read Value is : %f \r\n",( float )x*3300*5/0xffffff);
		Delay(100); 
		  
	}
} 




/***************************** END OF FILE ************************************/
