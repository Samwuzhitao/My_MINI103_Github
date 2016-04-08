/**
  ******************************************************************************
  * @file    APP/platform_init.c
  * @author  Samwu
  * @version V1.0.0
  * @date    23-2-2016
  * @brief   Evaluation board specific configuration file.
  ******************************************************************************
  */ 
#ifndef __PLATFORM_INIT_H
#define __PLATFORM_INIT_H

/* Define to prevent recursive inclusion -------------------------------------*/
#include "platform_config.h"
#include "stm32f10x.h"                         // STM32F10x Library Definitions  

/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void NVIC_Config(void);
void CAN_Config(void);
void UART_Config(void);
void SPI_Config( void );
void Init_RxMes(CanRxMsg *RxMessage);
void Show_compile_msg(void);

#endif
/***************************** END OF FILE ************************************/
