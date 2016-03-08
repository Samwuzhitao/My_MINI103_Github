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
__IO uint8_t CanSetSrcAddr = 0;

uint8_t CanRxCmdTopCounter = 0;
uint8_t CanRxCmdButtomCounter = 0;
uint8_t CanReceivecompleteFlg = 0;	

CAN_MessageTypedef CanRxCmdRingBuffer[CANRINGBUFFERLEN];

/******************************************************************************
  Function:CAN_MessageGet
  Description:
  Input:None
  Output:
  Return:
  Others:None
******************************************************************************/
void CAN_MessageGet( CanRxMsg *pMessage )
{	
	int i;
	CAN_STDEXTIDAddrTypedef CanSrcAddr,CanDstAddr;
	CAN_EXTSTDIDTypedef CAN_ID;
	
	if( pMessage->IDE  == CAN_ID_STD )
	{
		CAN_ID.Id = pMessage->StdId;
		CanDstAddr.CanIDAddr.ExtIDAddr = 0x00;
		CanSrcAddr.CanIDAddr.ExtIDAddr = 0x00;
	}
	else
	{
		CAN_ID.Id = pMessage->ExtId;
		CanDstAddr.CanIDAddr.ExtIDAddr = CAN_ID.CanProtocolId.ExtDstAddr;
		CanSrcAddr.CanIDAddr.ExtIDAddr = CAN_ID.CanProtocolId.ExtSrcAddr;
	}
	
	CanDstAddr.CanIDAddr.StdIDAddr = CAN_ID.CanProtocolId.DstAddr;
	CanSrcAddr.CanIDAddr.StdIDAddr = CAN_ID.CanProtocolId.SrcAddr;
	
	printf("CAN_ID.CanProtocolId.FunCode: %x\r\n",(CAN_ID.CanProtocolId.FunCode) & 0x1f);
	printf("CAN_ID.CanProtocolId.SrcAddr: %x\r\n",CanSrcAddr.IDAddr );
	printf("CAN_ID.CanProtocolId.DstAddr: %x\r\n",CanDstAddr.IDAddr);
	
	if( CanDstAddr.IDAddr == CanSetSrcAddr  )
	{
		CanRxCmdRingBuffer[CanRxCmdTopCounter].SrcAddr = CanSrcAddr.IDAddr;
		CanRxCmdRingBuffer[CanRxCmdTopCounter].DstAddr = CanDstAddr.IDAddr;
		CanRxCmdRingBuffer[CanRxCmdTopCounter].CanCmd = (CAN_ID.CanProtocolId.FunCode) & 0x1f;
		CanRxCmdRingBuffer[CanRxCmdTopCounter].IdType = pMessage->IDE;
		
		for( i=0; i<8; i++)
		{
			CanRxCmdRingBuffer[CanRxCmdTopCounter].data[i] = pMessage->Data[i];
		}
		
		CanReceivecompleteFlg = 1;
		
		CanRxCmdTopCounter++;
		
		if(CanRxCmdTopCounter == CANRINGBUFFERLEN)
		{
			CanRxCmdTopCounter = 0;
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
  Function:Can_cmd_parse
  Description:
  Input:None
  Output:
  Return:
  Others:None
******************************************************************************/
void Can_cmd_parse( void )
{
	uint8_t CanCmdReturnFlg = 0;
	
	if((CanRxCmdRingBuffer[CanRxCmdButtomCounter].CanCmd & 0x10) == 0x10)
		CanCmdReturnFlg = 1;
	
	switch(CanRxCmdRingBuffer[CanRxCmdButtomCounter].CanCmd & 0x0f)	
	{
		case CAN_CMD_READ_AD:
		{
			if(CanCmdReturnFlg == 1)
			{
				Can_show_ad_msg();
			}
			else
			{
				Can_return_ad_msg();
			}
		}
		break;
		
		case CAN_CMD_CHECK_BOARD:
		{
			if(CanCmdReturnFlg == 1)
			{
				Can_show_board_msg();
			}
			else
			{
				Can_return_board_msg();
			}
		}
		break;
		
		case CAN_CMD_RW_EEPROM:
		{
			if(CanCmdReturnFlg == 1)
			{
				Can_show_eeprom_msg();
			}
			else
			{
				Can_return_eeprom_msg();
			}
		}
		break;
		
		case CAN_CMD_READ_SN_ID:
		{
			if(CanCmdReturnFlg == 1)
			{
				Can_show_sn_msg();
			}
			else
			{
				Can_return_sn_msg();
			}
		}
		break;
		
		default:
			break;
	}
}

/******************************************************************************
  Function:Can_to_can_change_id
  Description:
  Input:None
  Output:
  Return:
  Others:None
******************************************************************************/
void Can_change_return_id( CanTxMsg *pMessage, uint8_t cmd )
{

	CAN_EXTSTDIDTypedef MyCAN_ID;
	CAN_STDEXTIDAddrTypedef MySrcIDAddr,MyDstIDAddr;
	
	MyDstIDAddr.IDAddr = CanRxCmdRingBuffer[CanRxCmdButtomCounter].SrcAddr; 
	MySrcIDAddr.IDAddr = CanRxCmdRingBuffer[CanRxCmdButtomCounter].DstAddr;
	
	MyCAN_ID.CanProtocolId.DstAddr = MyDstIDAddr.CanIDAddr.StdIDAddr ;
	MyCAN_ID.CanProtocolId.ExtDstAddr = MyDstIDAddr.CanIDAddr.ExtIDAddr; 
	MyCAN_ID.CanProtocolId.SrcAddr = MySrcIDAddr.CanIDAddr.StdIDAddr ;
	MyCAN_ID.CanProtocolId.ExtSrcAddr = MySrcIDAddr.CanIDAddr.ExtIDAddr; 
	
	MyCAN_ID.CanProtocolId.FunCode = cmd | 0x10;
	
	/* Transmit */
	if(  CanRxCmdRingBuffer[CanRxCmdButtomCounter].IdType == CAN_ID_STD )
	{
		pMessage->StdId = MyCAN_ID.Id;
	}
	else
	{
		pMessage->ExtId = MyCAN_ID.Id;
	}
	
	pMessage->RTR = CAN_RTR_DATA;
	
	pMessage->IDE = CanRxCmdRingBuffer[CanRxCmdButtomCounter].IdType;
	
	pMessage->DLC = 8;
}

/******************************************************************************
  Function:Can_show_sn_msg
  Description:
  Input:None
  Output:
  Return:
  Others:None
******************************************************************************/
void Can_show_sn_msg( void )
{
	printf("SRC:%2x DST:%2x CMD:%2x SN is: %2x %2x %2x %2x %2x %2x %2x %2x \r\n",
					CanRxCmdRingBuffer[CanRxCmdButtomCounter].SrcAddr,
					CanRxCmdRingBuffer[CanRxCmdButtomCounter].DstAddr,
					CanRxCmdRingBuffer[CanRxCmdButtomCounter].CanCmd,
					CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[0],
					CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[1],
					CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[2],
					CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[3],
					CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[4],
					CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[5],
					CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[6],
					CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[7]);
}

/******************************************************************************
  Function:Can_return_sn_msg
  Description:
  Input:None
  Output:
  Return:
  Others:None
******************************************************************************/
void Can_return_sn_msg( void )
{
	CanTxMsg CanToCanTxMessage;
	
	Can_change_return_id( &CanToCanTxMessage, CAN_CMD_READ_SN_ID );
	
#ifdef USE_CAN_TEST	
	CanToCanTxMessage.Data[0] = 0x11;
	CanToCanTxMessage.Data[1] = 0x22;
	CanToCanTxMessage.Data[2] = 0x33;
	CanToCanTxMessage.Data[3] = 0x44;
	CanToCanTxMessage.Data[4] = 0x55;
	CanToCanTxMessage.Data[5] = 0x66;
	CanToCanTxMessage.Data[6] = 0x77;
	CanToCanTxMessage.Data[7] = 0x88;
#endif
	
	CAN_Transmit(CAN1, &CanToCanTxMessage);
}

/******************************************************************************
  Function:Can_read_ad_msg
  Description:
  Input:None
  Output:
  Return:
  Others:None
******************************************************************************/
void Can_show_ad_msg( void )
{
	printf("SRC:%2x DST:%2x CMD:%2x ADC Channel %2d Value is: %8x \r\n",
					CanRxCmdRingBuffer[CanRxCmdButtomCounter].SrcAddr,
					CanRxCmdRingBuffer[CanRxCmdButtomCounter].DstAddr,
					CanRxCmdRingBuffer[CanRxCmdButtomCounter].CanCmd,
					CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[0],
					*((uint32_t *)(&(CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[1]))));
}

/******************************************************************************
  Function:Can_read_ad_msg
  Description:
  Input:None
  Output:
  Return:
  Others:None
******************************************************************************/
void Can_return_ad_msg( void )
{
	uint32_t AdcValue = 0;
	
	CanTxMsg CanToCanTxMessage;
	
	Can_change_return_id( &CanToCanTxMessage, CAN_CMD_READ_AD );
	
#ifdef USE_CAN_NORMAL
	AdcValue = Adc_get_value(CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[0]);
#endif
	
#ifdef USE_CAN_TEST	
	AdcValue = 0x123456;
#endif
	
	CanToCanTxMessage.Data[0] = CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[0];
	
	CanToCanTxMessage.Data[1] = *((uint8_t *)(&AdcValue));
	CanToCanTxMessage.Data[2] = *((uint8_t *)(&AdcValue)+1);
	CanToCanTxMessage.Data[3] = *((uint8_t *)(&AdcValue)+2);
	CanToCanTxMessage.Data[4] = 0x00;
	CanToCanTxMessage.Data[5] = 0x00;
	CanToCanTxMessage.Data[6] = 0x00;
	CanToCanTxMessage.Data[7] = 0x00;
	
	CAN_Transmit(CAN1, &CanToCanTxMessage);
}

/******************************************************************************
  Function:Can_show_eeprom_msg
  Description:
  Input:None
  Output:
  Return:
  Others:None
******************************************************************************/
void Can_show_eeprom_msg( void )
{
	if((CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[0] & 0x10))
	{
		if((CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[0] & 0x80))
		{
			printf("SRC:%2x DST:%2x CMD:%2x Write %2xch EEPROM %2x byte %4x addr data \r\n",
					CanRxCmdRingBuffer[CanRxCmdButtomCounter].SrcAddr,
					CanRxCmdRingBuffer[CanRxCmdButtomCounter].DstAddr,
					CanRxCmdRingBuffer[CanRxCmdButtomCounter].CanCmd,
					CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[1],
					(CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[0] & 0x0f),
				  *(uint16_t *)(&(CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[2])));
		}
		else
		{
			printf("SRC:%2x DST:%2x CMD:%2x Read %2xch EEPROM %2x byte %4x addr data is:  %2x %2x %2x %2x \r\n",
					CanRxCmdRingBuffer[CanRxCmdButtomCounter].SrcAddr,
					CanRxCmdRingBuffer[CanRxCmdButtomCounter].DstAddr,
					CanRxCmdRingBuffer[CanRxCmdButtomCounter].CanCmd,
					CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[1],
					(CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[0] & 0x0f),
				  *(uint16_t *)(&(CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[2])),
					CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[4],
					CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[5],
					CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[6],
					CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[7]);
		}
			
	}
	else
	{
		if((CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[0] & 0x80))
		{
			printf(" Write fail \r\n");
		}
		else
		{
			printf(" Read fail \r\n");
		}
	}
}

/******************************************************************************
  Function:Can_return_eeprom_msg
  Description:
  Input:None
  Output:
  Return:
  Others:None
******************************************************************************/
void Can_return_eeprom_msg( void )
{
	uint8_t i;
	uint8_t Eepromdata[4];
	uint8_t EepromCh = 0;
	uint8_t EepromCmd = 0;
	uint8_t EepromBackState = 0;
	uint8_t EepromReadWriteCmd = 0;
	uint16_t EepromStartAddr = 0;
	CanTxMsg CanToCanTxMessage;
	
	Can_change_return_id( &CanToCanTxMessage, CAN_CMD_RW_EEPROM );
	
	// CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[0]:ch
	// CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[1]:ReadWriteCmd
	// ReadWriteCmd :bit8(W =1/R=0)   bit5(Operate state:1=OK 0=Fail) bit[0..3]:num
	// CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[2..3]:startaddr
	EepromReadWriteCmd = CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[0];
	EepromCh = CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[1] ;
	EepromStartAddr = *(uint16_t *)(&(CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[2]));
	
#ifdef USE_CAN_NORMAL

	for(i=0; i<(EepromReadWriteCmd & 0x0f); i++)
	{
		Eepromdata[i] = CanToCanTxMessage.Data[4+i];
	}
	
	EepromBackState = Eeprom_write_value(Eepromdata,
												EepromCh,EepromReadWriteCmd,EepromStartAddr);										
#endif
	
#ifdef USE_CAN_TEST	
	if( EepromReadWriteCmd & 0x80)
	{
		/* TDB */
	}
	else
	{
		Eepromdata[0] = 0x11;
		Eepromdata[1] = 0x22;
		Eepromdata[2] = 0x33;
		Eepromdata[3] = 0x44;
	}
	// bit5(Operate state:1=OK 0=Fail) 
	EepromBackState = EepromReadWriteCmd | 0x10 ;
#endif
	
	CanToCanTxMessage.Data[0] = EepromBackState;
	CanToCanTxMessage.Data[1] = EepromCh;
	CanToCanTxMessage.Data[2] = CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[2];
	CanToCanTxMessage.Data[3] = CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[3];
	
	if( (EepromBackState & 0x80) & (EepromBackState & 0x10))
	{
		for(i=0; i<4; i++)
		{
			CanToCanTxMessage.Data[4+i] = 0x00;
		}
	}
	else
	{
		for(i=0; i<(EepromBackState & 0x0f); i++)
		{
			CanToCanTxMessage.Data[4+i] = Eepromdata[i];
		}
		
		for(i=0; i<4-(EepromBackState & 0x0f); i++)
		{
			CanToCanTxMessage.Data[4+(EepromBackState & 0x0f)+i] = 0x00;
		}
	}

	CAN_Transmit(CAN1, &CanToCanTxMessage);
}

/******************************************************************************
  Function:Can_show_board_msg
  Description:
  Input:None
  Output:
  Return:
  Others:None
******************************************************************************/
void Can_show_board_msg( void )
{
	uint8_t * Str;
	
	switch((CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[0]))
	{
		case 0x01:
		{ 
			Str = "TEDS State is: ";
		}
		break;
		
		case 0x02:
		{
			Str = "PT1000 State is: ";
		}
		break;
		
		default:
			break;
	}
		
	printf("SRC:%2x DST:%2x CMD:%2x Check %s %x \r\n",
				CanRxCmdRingBuffer[CanRxCmdButtomCounter].SrcAddr,
				CanRxCmdRingBuffer[CanRxCmdButtomCounter].DstAddr,
				CanRxCmdRingBuffer[CanRxCmdButtomCounter].CanCmd,
				Str,
				*(uint16_t *)(&(CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[1])));
	
}

/******************************************************************************
  Function:Can_return_board_msg
  Description:
  Input:None
  Output:
  Return:
  Others:None
******************************************************************************/
void Can_return_board_msg( void )
{
	uint8_t i;
	uint8_t DeviceType = 0;
	uint16_t DevieCheckState = 0;
	CanTxMsg CanToCanTxMessage;
	
	Can_change_return_id( &CanToCanTxMessage, CAN_CMD_CHECK_BOARD );
	
	DeviceType = CanRxCmdRingBuffer[CanRxCmdButtomCounter].data[0];
	
#ifdef USE_CAN_NORMAL
	DevieCheckState = Board_Check(DeviceType);										
#endif
	
#ifdef USE_CAN_TEST	
	DevieCheckState = 0xaa55;
#endif
	
	CanToCanTxMessage.Data[0] = DeviceType;
	CanToCanTxMessage.Data[1] = *(uint8_t *)(&DevieCheckState);
	CanToCanTxMessage.Data[2] = *((uint8_t *)(&DevieCheckState)+1);

	for(i=0; i<5; i++)
	{
		CanToCanTxMessage.Data[3+i] = 0x00;
	}
	
	CAN_Transmit(CAN1, &CanToCanTxMessage);
}
