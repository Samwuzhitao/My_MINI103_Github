/**
  ******************************************************************************
  * @file    APP/SerialProtocol.c
  * @author  Samwu
  * @version V1.0.0
  * @date    23-2-2016
  * @brief   Evaluation board specific configuration file.
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#include "platform_config.h"
#include "stm32f10x.h"                         // STM32F10x Library Definitions  
#include "SerialProtocol.h"
#include "stdio.h"

/* Private typedef -----------------------------------------------------------*/
#define USARTRINGBUFFERLEN                   10

/* Private variables ---------------------------------------------------------*/
/* compile message variables */
const uint8_t compile_data[] = __DATE__;
const uint8_t compile_time[] = __TIME__;
const uint8_t version[]="1.0";
const uint8_t serial_number[]="0000";

/* usart peripheral variables */
USART_MeaasgeTypedef  USART_Meaasge;

__IO uint8_t UsartRxCmdTopCounter = 0;
__IO uint8_t UsartRxCmdButtomCounter = 0;
__IO uint8_t UsartReceivecompleteFlg = 0;		 

uint8_t UsartRxCmdRingBuffer[USARTRINGBUFFERLEN][100];

/******************************************************************************
  Function:GE_MessageGet
  Description:The Grid - Eye hook function,
              Used to Get PC message sent to Grid-Eye board
              The format of the message below
              -----------------------------------
             |   "***"   |   u8   |  Array       |
             |  pHeader  |  pLen  |  pCmdData[]  |
              -----------------------------------
  Input:
      pMeaasge:Grid-EYE message struct pointer
      TX_data :Character of the PC was sent
  Output:None
  Return:None
  Others:
******************************************************************************/
void USART_MessageGet( USART_MeaasgeTypedef *pMeaasge, uint8_t data )
{				
	int i;
	switch (pMeaasge->ReceiveState)
	{
	 	case USART_RECEIVE_IDLE:
		{
			if( data == '*' )
			{
				pMeaasge->ReceiveState =USART_RECEIVE_HEADER1;
			}	 
		}
		break;
				 
		case USART_RECEIVE_HEADER1:
		{
			if( data == '*' )
			{
				pMeaasge->ReceiveState = USART_RECEIVE_HEADER2;
			}
			else
			{
				pMeaasge->ReceiveState = USART_RECEIVE_IDLE;
			}
		}
		break;
				
		case USART_RECEIVE_HEADER2:
		{
			if( data == '*' )
			{
				pMeaasge->ReceiveState = USART_RECEIVE_CMDLEN;
			}
			else
			{
				pMeaasge->ReceiveState = USART_RECEIVE_IDLE;
			}
		}
		break;	
						 
		case USART_RECEIVE_CMDLEN:
		{
			if( data == '*' )
			{
				pMeaasge->ReceiveState = USART_RECEIVE_CMDLEN;
			}					
			else
			{
				pMeaasge->ReceiveDataLen = data;
				pMeaasge->ReceiveDataNum = 0;
				pMeaasge->ReceiveState = USART_RECEIVE_CMDDATA;
			}
		}
		break;
		
		case USART_RECEIVE_CMDDATA:
		{
			Serial_buffer_add( pMeaasge, data );
			/* Is the data receiving */
			if((pMeaasge->ReceiveDataNum == pMeaasge->ReceiveDataLen) 
				 && (pMeaasge->ReceiveDataNum != 0))
			{
				
				//printf("ReceiveDataBuf data is = %s \r\n",pMeaasge->ReceiveDataBuf+1);
				UsartReceivecompleteFlg = 1;
					
				UsartRxCmdTopCounter++;
				if(UsartRxCmdTopCounter == USARTRINGBUFFERLEN)
				{
					UsartRxCmdTopCounter = 0;
				}
				
				/* Complete CMD parse data reset, enter the idle state */
				for(i = 0; i < pMeaasge->ReceiveDataNum; i++)
				{
					UsartRxCmdRingBuffer[UsartRxCmdTopCounter][i] = pMeaasge->ReceivetmpData[i];
				}
				
				Serial_buffer_clear( pMeaasge );
				
				pMeaasge->ReceiveDataLen = 0;
				pMeaasge->ReceiveDataNum = 0;
				
				pMeaasge->ReceiveState = USART_RECEIVE_IDLE;
			}
			else
			{
				pMeaasge->ReceiveState = USART_RECEIVE_CMDDATA;
			}
		}
		break;
				
		default:
			break;
	}	
	
}

/**
  * @brief  printf compile message.
  * @param  None
  * @retval None
  */
void Serial_buffer_add( USART_MeaasgeTypedef *pMeaasge, uint8_t data )
{
	pMeaasge->ReceivetmpData[(pMeaasge->ReceiveDataNum)++] = data;
}

/**
  * @brief  printf compile message.
  * @param  None
  * @retval None
  */
void Serial_buffer_clear( USART_MeaasgeTypedef *pMeaasge )
{
	unsigned int i;
	for(i=0; i< pMeaasge->ReceiveDataNum; i++)
	{
		pMeaasge->ReceivetmpData[i] = 0;
	}
}

/******************************************************************************
  Function:Can_cmd_parse
  Description:
  Input:None
  Output:
  Return:
  Others:None
******************************************************************************/
void Serial_cmd_parse( void )
{
	if(UsartReceivecompleteFlg == 1)
	{
		if(UsartRxCmdTopCounter  !=  UsartRxCmdButtomCounter)
		{
			switch(UsartRxCmdRingBuffer[UsartRxCmdButtomCounter][0])
			{
				case USART_CMD_COMPILE:
				{
					Serial_show_compile_msg();
				}
				break;
				
				default:
				break;
			}	
			
			UsartRxCmdButtomCounter++;
			if(UsartRxCmdButtomCounter == USARTRINGBUFFERLEN)
			{
				UsartRxCmdButtomCounter = 0;
			}
			
			if(UsartRxCmdTopCounter == UsartRxCmdButtomCounter)
			{
				 UsartReceivecompleteFlg = 0;
			}
		}
	}
}

/* Private function prototypes -----------------------------------------------*/
/**
  * @brief  printf compile message.
  * @param  None
  * @retval None
  */
void Serial_show_compile_msg( void )
{
	printf("compile_data:%s\r\n",compile_data);
	printf("compile_data:%s\r\n",compile_time);
	printf("software_version:%s\r\n",version);
}


/***************************** END OF FILE ************************************/
