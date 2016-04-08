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


/**
  * @brief  Configures CAN1 and CAN2.
  * @param  None
  * @retval None
  */
void CAN_Config(void)
{
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

void SPI_Config( void )
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
	
	/* Enable GPIO clock for SPI */
  RCC_APB2PeriphClockCmd(SPI_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);
  /* Enable SPI Periph clock */
  RCC_APB1PeriphClockCmd(SPI_CLK, ENABLE); 
	
  /* Configure SPI pins: SCK and MOSI ---------------------------------*/
  /* Configure SCK and MOSI pins as Alternate Function Push Pull */
  GPIO_InitStructure.GPIO_Pin = SPI_PIN_SCK | SPI_PIN_MOSI ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(SPI_GPIO, &GPIO_InitStructure);

  /* Configure MISO pin as Alternate Function Push Pull */
  GPIO_InitStructure.GPIO_Pin = SPI_PIN_MISO;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(SPI_GPIO, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = SPI_PIN_CS;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(SPI_GPIO, &GPIO_InitStructure);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI, &SPI_InitStructure);

  /* Enable SPIy */
  SPI_Cmd(SPI, ENABLE);
	
	  /* Enable the Rx buffer not empty interrupt */
  SPI_I2S_ITConfig(SPI, SPI_I2S_IT_RXNE, ENABLE);

  /* Enable the Tx buffer empty interrupt */
  SPI_I2S_ITConfig(SPI, SPI_I2S_IT_TXE, ENABLE);
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
