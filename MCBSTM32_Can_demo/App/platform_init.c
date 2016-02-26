/**
  ******************************************************************************
  * @file    APP/platform_init.c
  * @author  Samwu
  * @version V1.0.0
  * @date    23-2-2016
  * @brief   Evaluation board specific configuration file.
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#include "platform_config.h"
#include "platform_init.h"
#include "stm32f10x.h"                         // STM32F10x Library Definitions  
#include "LCD.h"                               // LCD function prototypes
#include "stdio.h"
#include "CanProtocol.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private variables ---------------------------------------------------------*/
/* can peripheral variables */
CAN_InitTypeDef        CAN_InitStructure;
CAN_FilterInitTypeDef  CAN_FilterInitStructure;
CanTxMsg TxMessage;

/* usart peripheral variables */
USART_InitTypeDef USART_InitStructure;

#ifdef USE_CAN_STD_ID
extern CAN_STDIDTypedef CAN_ID;
#endif

#ifdef USE_CAN_EXT_ID
extern CAN_EXTIDTypedef CAN_ID;
#endif

/**
  * @brief  Configures CAN1 and CAN2.
  * @param  None
  * @retval None
  */
void CAN_Config(void)
{
	#ifdef USE_CAN_STD_ID
	CAN_STDIDTypedef MyCAN_ID;
	#endif

	#ifdef USE_CAN_EXT_ID
	CAN_EXTIDTypedef MyCAN_ID;
	#endif
	
  GPIO_InitTypeDef  GPIO_InitStructure;

  /* Configure CAN1 IOs **********************************************/
  /* GPIOB and AFIO clocks enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);
     
  /* Configure CAN1 RX pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Configure CAN1 TX pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Remap CAN1 GPIOs */
  GPIO_PinRemapConfig(GPIO_Remap1_CAN1 , ENABLE);

  /* Configure CAN1 **************************************************/  
  /* CAN1 Periph clocks enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1 , ENABLE);  
  
  /* CAN1 register init */
  CAN_DeInit(CAN1);

  /* CAN1 cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = DISABLE;
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = DISABLE;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = ENABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;  
  CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;
 
#if CAN_BAUDRATE == 1000 /* 1MBps */
  CAN_InitStructure.CAN_Prescaler =6;
#elif CAN_BAUDRATE == 500 /* 500KBps */
  CAN_InitStructure.CAN_Prescaler =12;
#elif CAN_BAUDRATE == 250 /* 250KBps */
  CAN_InitStructure.CAN_Prescaler =24;
#elif CAN_BAUDRATE == 125 /* 125KBps */
  CAN_InitStructure.CAN_Prescaler =48;
#elif  CAN_BAUDRATE == 100 /* 100KBps */
  CAN_InitStructure.CAN_Prescaler =60;
#elif  CAN_BAUDRATE == 50 /* 50KBps */
  CAN_InitStructure.CAN_Prescaler =120;
#elif  CAN_BAUDRATE == 20 /* 20KBps */
  CAN_InitStructure.CAN_Prescaler =300;
#elif  CAN_BAUDRATE == 10 /* 10KBps */
  CAN_InitStructure.CAN_Prescaler =600;
#else
   #error "Please select first the CAN Baudrate in Private defines in main.c "
#endif  /* CAN_BAUDRATE == 1000 */

  
  /*Initializes the CAN1  */
  CAN_Init(CAN1, &CAN_InitStructure);

  /* CAN1 filter init */
  CAN_FilterInitStructure.CAN_FilterNumber = 1;
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x6420;
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
  
	MyCAN_ID.CanProtocolId.DstAddr = DSTADDR;
	MyCAN_ID.CanProtocolId.SrcAddr = SRCADDR;
	MyCAN_ID.CanProtocolId.FunCode = 0x03;
	
  /* Transmit */
	if( CAN_ID_TYPE == CAN_ID_STD )
	{
		TxMessage.StdId = MyCAN_ID.Id;
	}
	else
	{
		TxMessage.ExtId = MyCAN_ID.Id;
	}
  TxMessage.RTR = CAN_RTR_DATA;
  TxMessage.IDE = CAN_ID_TYPE;
  TxMessage.DLC = 8;  
}

/**
  * @brief  Initializes a Rx Message.
  * @param  CanRxMsg *RxMessage.
  * @retval None
  */
void Init_RxMes(CanRxMsg *RxMessage)
{
  uint8_t i = 0;

  RxMessage->StdId = 0;
  RxMessage->ExtId = 0;
  RxMessage->IDE = CAN_ID_TYPE;
  RxMessage->DLC = 0;
  RxMessage->FMI = 0;
  for (i = 0; i < 8; i++)
  {
    RxMessage->Data[i] = 0;
  }
}


void UART_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  /* Configure UART1 IOs **********************************************/
  RCC_APB2PeriphClockCmd(USART_GPIO_CLK, ENABLE);
  RCC_APB2PeriphClockCmd(USART_CLK,ENABLE);

  /* Configure UART1 TX pin */
  GPIO_InitStructure.GPIO_Pin = USART_TxPin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(USART_GPIO, &GPIO_InitStructure);
	
	/* Configure UART1 RX pin */
  GPIO_InitStructure.GPIO_Pin = USART_RxPin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(USART_GPIO, &GPIO_InitStructure);
	
  /* USARTx configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = USART_BAUDRATE;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	  
	USART_Init(USART, &USART_InitStructure);
	
	USART_ITConfig(USART, USART_IT_RXNE, ENABLE);
	//USART_ITConfig(USART, USART_IT_TXE, ENABLE);
		
	USART_Cmd(USART1, ENABLE);
}


int fputc(int ch,FILE *f)  
{  
  USART_SendData(USART1,(uint8_t)ch);  
  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)== RESET );  
  return ch;  
}


/**
  * @brief  Configures the NVIC for CAN.
  * @param  None
  * @retval None
  */
void NVIC_Config(void)
{
  NVIC_InitTypeDef  NVIC_InitStructure;

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
 
  NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);  
  
  NVIC_InitStructure.NVIC_IRQChannel = USART_IRQn;			    
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	  
  NVIC_Init(&NVIC_InitStructure);
}


/***************************** END OF FILE ************************************/
