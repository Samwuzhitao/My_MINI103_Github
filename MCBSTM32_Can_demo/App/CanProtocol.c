/**
  ******************************************************************************
  * @file    APP/CanProtocol.c
  * @author  Samwu
  * @version V1.0.0
  * @date    24-2-2016
  * @brief   Evaluation board specific configuration file.
  ******************************************************************************
  */ 
/* Define to prevent recursive inclusion -------------------------------------*/
#include "platform_config.h"
#include "stm32f10x.h"                         // STM32F10x Library Definitions  
#include "CanProtocol.h"
#include "stdio.h"



#define CANRINGBUFFERLEN                   10

/* Private variables ---------------------------------------------------------*/
/* can peripheral variables */

#ifdef USE_CAN_STD_ID
CAN_STDIDTypedef CAN_ID;
CAN_ADDRTypedef CAN_ADDR;
#endif

#ifdef USE_CAN_EXT_ID
CAN_EXTIDTypedef CAN_ID;
CAN_EXTADDRTypedef CAN_ADDR;
#endif

__IO uint8_t CanRxCmdTopCounter = 0;
__IO uint8_t CanRxCmdButtomCounter = 0;
__IO uint8_t CanReceivecompleteFlg = 0;	

uint8_t CanRxCmdRingBuffer[CANRINGBUFFERLEN][11];


/******************************************************************************
  Function:Can_cmd_parse
  Description:
  Input:None
  Output:
  Return:
  Others:None
******************************************************************************/
void CAN_MessageGet( CanRxMsg *pMessage )
{	
	int i;
	
	if( CAN_ID_TYPE == CAN_ID_STD )
	{
		CAN_ID.Id = pMessage->StdId;
	}
	else
	{
		CAN_ID.Id = pMessage->ExtId;
	}
	
	CAN_ADDR.CAN_ProtocolAddr.DstAddr = CAN_ID.CanProtocolId.SrcAddr;
	CAN_ADDR.CAN_ProtocolAddr.SrcAddr = CAN_ID.CanProtocolId.DstAddr;
	
	if( CAN_ID.CanProtocolId.DstAddr == DSTADDR )
	{
		
		CanReceivecompleteFlg = 1;
		
		CanRxCmdTopCounter++;
		
		if(CanRxCmdTopCounter == CANRINGBUFFERLEN)
		{
			CanRxCmdTopCounter = 0;
		}
		
		CanRxCmdRingBuffer[CanRxCmdTopCounter][0] = CAN_ADDR.CAN_ProtocolAddr.SrcAddr;
		CanRxCmdRingBuffer[CanRxCmdTopCounter][1] = CAN_ADDR.CAN_ProtocolAddr.DstAddr;
		CanRxCmdRingBuffer[CanRxCmdTopCounter][2] = CAN_ID.CanProtocolId.FunCode;
		
		for( i =3; i<11; i++)
		{
			CanRxCmdRingBuffer[CanRxCmdTopCounter][i] = pMessage->Data[i-3];
		}
	}
}

/******************************************************************************
  Function:Can_Process
  Description:
  Input:None
  Output:
  Return:
  Others:None
******************************************************************************/
void Can_Process( void )
{
	if(CanReceivecompleteFlg == 1)
	{
		if(CanRxCmdTopCounter != CanRxCmdButtomCounter)
		{
			
			Can_cmd_parse();
			
			CanRxCmdButtomCounter++;
			
			if(CanRxCmdButtomCounter == CANRINGBUFFERLEN)
			{
				CanRxCmdButtomCounter = 0;
			}
			
			if(CanRxCmdTopCounter == CanRxCmdButtomCounter)
			{
				 CanReceivecompleteFlg = 0;
			}
		}
	}
}

/******************************************************************************
  Function:Can_Process
  Description:
  Input:None
  Output:
  Return:
  Others:None
******************************************************************************/
void Can_cmd_parse( void )
{
	switch(CanRxCmdRingBuffer[CanRxCmdButtomCounter][2])
	{
		case CAN_CMD_READ_AD:
		{
			/* TDB */
		}
		break;
		
		case CAN_CMD_READ_EEPROM:
		{
			/* TDB */
		}
		break;
		
		case CAN_CMD_WRITE_EEPROM:
		{
			/* TDB */
		}
		break;
		
		case CAN_CMD_READ_SN_ID:
		{
			Can_show_sn_msg();
		}
		break;
		
		case CAN_CMD_WRITE_SN_ID:
		{
			/* TDB */
		}
		break;	
		
		case CAN_CMD_CHECK_TEDS:
		{
			/* TDB */
		}
		break;
		
		case CAN_CMD_CHECK_PT1000:
		{
			/* TDB */
		}
		break;
		
		default:
			break;
	}
}
/* Private function prototypes -----------------------------------------------*/
/**
  * @brief  printf compile message.
  * @param  None
  * @retval None
  */
void Can_show_sn_msg( void )
{
	printf("SRC:%2x DST:%2x CMD:%2d SN is: %2x %2x %2x %2x %2x %2x %2x %2x \r\n",CanRxCmdRingBuffer[CanRxCmdButtomCounter][0],
					CanRxCmdRingBuffer[CanRxCmdButtomCounter][1],CanRxCmdRingBuffer[CanRxCmdButtomCounter][2],
					CanRxCmdRingBuffer[CanRxCmdButtomCounter][3],CanRxCmdRingBuffer[CanRxCmdButtomCounter][4],
					CanRxCmdRingBuffer[CanRxCmdButtomCounter][5],CanRxCmdRingBuffer[CanRxCmdButtomCounter][6],
					CanRxCmdRingBuffer[CanRxCmdButtomCounter][7],CanRxCmdRingBuffer[CanRxCmdButtomCounter][8],
					CanRxCmdRingBuffer[CanRxCmdButtomCounter][9],CanRxCmdRingBuffer[CanRxCmdButtomCounter][10]);
}

