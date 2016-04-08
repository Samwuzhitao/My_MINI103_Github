/**
  ******************************************************************************
  * @file    APP/platform_config.h 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Evaluation board specific configuration file.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PLATFORM_CONFIG_H
#define __PLATFORM_CONFIG_H

#define USE_MCBSTM32

/* Define the STM32F10x hardware depending on the used evaluation board */
#ifdef USE_MCBSTM32

/* CAN Private define -------------------------------------------------------*/
	/* #define CAN_BAUDRATE  1000 */       /* 1MBps   */
	   #define CAN_BAUDRATE  500           /* 500kBps */
	/* #define CAN_BAUDRATE  250  */       /* 250kBps */
	/* #define CAN_BAUDRATE  125  */       /* 125kBps */
	/* #define CAN_BAUDRATE  100  */       /* 100kBps */ 
	/* #define CAN_BAUDRATE  50   */       /* 50kBps  */ 
	/* #define CAN_BAUDRATE  20   */       /* 20kBps  */ 
	/* #define CAN_BAUDRATE  10   */       /* 10kBps  */ 
	
	
/* USART Private define -------------------------------------------------------*/
	#define USART_BAUDRATE          115200  /* 115200 Bps */
  #define USART                   USART1
  #define USART_GPIO              GPIOA
  #define USART_CLK               RCC_APB2Periph_USART1
  #define USART_GPIO_CLK          RCC_APB2Periph_GPIOA
  #define USART_RxPin             GPIO_Pin_10
  #define USART_TxPin             GPIO_Pin_9
  #define USART_IRQn              USART1_IRQn
  #define USART_IRQHandler        USART1_IRQHandler

/* SPI Private define --------------------------------------------------------*/
  #define SPI                     SPI2
  #define SPI_CLK                 RCC_APB1Periph_SPI2
  #define SPI_GPIO                GPIOB
  #define SPI_GPIO_CLK            RCC_APB2Periph_GPIOB
	#define SPI_PIN_CS              GPIO_Pin_12
  #define SPI_PIN_SCK             GPIO_Pin_13
  #define SPI_PIN_MISO            GPIO_Pin_14
  #define SPI_PIN_MOSI            GPIO_Pin_15
	

/* LCD Private define -------------------------------------------------------*/
	/* If processor works on high frequency delay has to be increased, it can be 
		 increased by factor 2^N by this constant                                   */
	#define DELAY_2N     0

	/*------------------------- Text LCD size definitions ------------------------*/

	#define LineLen     16                  /* Width (in characters)              */
	#define NumLines     2                  /* Hight (in lines)                   */

	/*-------------------- LCD interface hardware definitions --------------------*/

	/* PINS: 
		 - DB4 = PC3
		 - DB5 = PC2
		 - DB6 = PC1
		 - DB7 = PC0
		 - E   = PC10
		 - RW  = PC11
		 - RS  = PC12                                                               */

	#define PIN_E                 (   1 << 10)
	#define PIN_RW                (   1 << 11)
	#define PIN_RS                (   1 << 12)
	#define PINS_CTRL             (0x07 << 10)
	#define PINS_DATA             (0x0F <<  0)
	#define PINS_ALL              (PINS_CTRL | PINS_DATA)

	/* Enable Clock for peripheral driving LCD pins                               */
	#define LCD_CLOCK_EN         (RCC->APB2ENR |= (1 << 4)); // enable clock for GPIOC

	/* pin E  setting to 0 or 1                                                   */
	#define LCD_E(x)              GPIOC->ODR = (GPIOC->ODR & ~PIN_E)  | (x ? PIN_E : 0);

	/* pin RW setting to 0 or 1                                                   */
	#define LCD_RW(x)             GPIOC->ODR = (GPIOC->ODR & ~PIN_RW) | (x ? PIN_RW : 0);

	/* pin RS setting to 0 or 1                                                   */
	#define LCD_RS(x)             GPIOC->ODR = (GPIOC->ODR & ~PIN_RS) | (x ? PIN_RS : 0);

	/* Reading DATA pins                                                          */
	#define LCD_DATA_IN           SWAP_DATA[(((GPIOC->IDR & PINS_DATA) >> 0) & 0x0F)]

	/* Writing value to DATA pins                                                 */
	#define LCD_DATA_OUT(x)       GPIOC->ODR = (GPIOC->ODR & ~PINS_DATA) | ((SWAP_DATA[x]) << 0);

	/* Setting all pins to output mode                                            */
	#define LCD_ALL_DIR_OUT       GPIOC->CRL = (GPIOC->CRL & 0xFFFF0000) | 0x00003333; \
																GPIOC->CRH = (GPIOC->CRH & 0xFFF000FF) | 0x00033300;
	 
	/* Setting DATA pins to input mode                                            */
	#define LCD_DATA_DIR_IN       GPIOC->CRL = (GPIOC->CRL & 0xFFFF0000) | 0x00004444;

	/* Setting DATA pins to output mode                                           */
	#define LCD_DATA_DIR_OUT      GPIOC->CRL = (GPIOC->CRL & 0xFFFF0000) | 0x00003333;


#endif /* USE_MCBSTM32 */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __PLATFORM_CONFIG_H */

/***************************** END OF FILE ************************************/
