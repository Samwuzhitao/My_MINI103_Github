/**
  ******************************************************************************
  * @file    APP/SerialProtocol.h
  * @author  Samwu
  * @version V1.0.0
  * @date    23-2-2016
  * @brief   Evaluation board specific configuration file.
  ******************************************************************************
  */ 
#ifndef __SERIALPROTOCOL_H
#define __SERIALPROTOCOL_H

/* Define to prevent recursive inclusion -------------------------------------*/
#include "platform_config.h"
#include "stm32f10x.h"                         // STM32F10x Library Definitions  

/* Private typedef -----------------------------------------------------------*/
/* A serial port receiving character relevant variables */
typedef struct 
{
	uint32_t ReceiveDataNum;       /* the conuter for the databuf   */
	uint8_t  ReceiveState;         /* receive state                 */
	uint8_t  ReceiveDataLen;       /* The length of the data        */
	uint8_t  ReceivetmpData[11];  /* The length of the data        */
} USART_MeaasgeTypedef;

typedef struct 
{ 
	uint8_t  Funcode;              /* receive state                 */	
	uint8_t  CanIDType;            /* receive state                 */
	uint8_t  CanDstID;             /* receive state                 */
	uint8_t  Data[8];             /* The length of the data        */
} USART_FrameTypedef;

/* Data statement */
#define USART_RECEIVE_IDLE         0     /* no received data      */
#define USART_RECEIVE_HEADER1      1     /* start receive Header  */
#define USART_RECEIVE_HEADER2      2     /* start receive Header  */
#define USART_RECEIVE_CMDLEN       3     /* start receive Header  */
#define USART_RECEIVE_CMDDATA      4     /* start receive CmdData */

/* Data statement */
#define USART_CMD_COMPILE_MESSAGE            '0'   /*  */
#define USART_CMD_SET_CAN_SCR_ADDR           '1'   /*  */

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void Serial_show_compile_msg( void );
void USART_MessageGet( USART_MeaasgeTypedef *pMeaasge, uint8_t TX_data );

void Serial_buffer_clear( USART_MeaasgeTypedef *pMeaasge );
void Serial_buffer_add( USART_MeaasgeTypedef *pMeaasge, uint8_t data );
void Serial_Process( void );
void Serial_cmd_parse( void );
void Serial_SetCanID(CanTxMsg *pMessage, uint8_t CanCmd, uint8_t Idtype, uint8_t CanDstID );
void Serial_set_srcaddr(void);
void Serial_send_cmd_to_can( void );

#endif
/***************************** END OF FILE ************************************/
