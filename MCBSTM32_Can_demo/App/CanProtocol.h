/**
  ******************************************************************************
  * @file    APP/CanProtocol.h
  * @author  Samwu
  * @version V1.0.0
  * @date    24-2-2016
  * @brief   Evaluation board specific configuration file.
  ******************************************************************************
  */ 
#ifndef __CANPROTOCOL_H
#define __CANPROTOCOL_H
/* Define to prevent recursive inclusion -------------------------------------*/
#include "platform_config.h"
#include "stm32f10x.h"                         // STM32F10x Library Definitions 

//#define  USE_CAN_STD_ID
#define  USE_CAN_EXT_ID


#ifdef USE_CAN_STD_ID
	#define CAN_ID_TYPE                         CAN_ID_STD
	#define DSTADDR                             0x02
	#define SRCADDR                             0x01
#endif

#ifdef USE_CAN_EXT_ID
	#define CAN_ID_TYPE                         CAN_ID_EXT
	#define DSTADDR                             0x44
	#define SRCADDR                             0x56
#endif

/* Private typedef -----------------------------------------------------------*/
/* Can receiving character relevant variables */
typedef union
{
	struct
	{
		uint32_t FunCode:3;         /*!< bit:  0..2  CMD Code                     */
		uint32_t SrcAddr:4;         /*!< bit:  3..6  source address               */
		uint32_t DstAddr:4;         /*!< bit:  7..11 destination address          */
		uint32_t RESERVED0:21;      /*!< bit: 11..31 Reserved                     */
	}CanProtocolId;
	uint32_t Id;
} CAN_STDIDTypedef;

typedef union
{
	struct
	{
		uint32_t FunCode:8;          /*!< bit:  0..7  CMD Code                     */
		uint32_t SrcAddr:8;          /*!< bit:  9..15  source address              */
		uint32_t DstAddr:8;          /*!< bit: 16..24 destination address          */		
		uint32_t RESERVED0:8;        /*!< bit: 25..31 Reserved                     */
	}CanProtocolId;
	uint32_t Id;
} CAN_EXTIDTypedef;

typedef union
{
	struct
	{
		uint8_t SrcAddr:8;         /*!< bit:  0..3  source address               */
		uint8_t DstAddr:8;         /*!< bit:  4..7  destination address          */              
	}CAN_ProtocolAddr;
	uint8_t CAN_Addr; 
} CAN_ADDRTypedef;

typedef union
{
	struct
	{
		uint16_t SrcAddr:8;         /*!< bit:  0..3  source address               */
		uint16_t DstAddr:8;         /*!< bit:  4..7  destination address          */              
	}CAN_ProtocolAddr;
	uint16_t CAN_Addr; 
} CAN_EXTADDRTypedef;

/* CMD */
#define CAN_CMD_READ_AD             0     /*     */
#define CAN_CMD_READ_EEPROM         1     /*     */
#define CAN_CMD_WRITE_EEPROM        2     /*     */
#define CAN_CMD_READ_SN_ID          3     /*     */
#define CAN_CMD_WRITE_SN_ID         4     /*     */
#define CAN_CMD_CHECK_TEDS          5     /*     */
#define CAN_CMD_CHECK_PT1000        6     /*     */

/* Private function prototypes -----------------------------------------------*/
void CAN_MessageGet( CanRxMsg *pMessage );
void Can_Process( void );
void Can_cmd_parse( void );
void Can_show_sn_msg( void );

#endif
