#ifndef __LED_H
#define __LED_H	 
#include "stm32f10x.h"

#define LED_LED1_OFF()   GPIO_SetBits(GPIOE, GPIO_Pin_5 )  	     //LED1 Close
#define LED_LED1_ON()    GPIO_ResetBits(GPIOE, GPIO_Pin_5 )	     //LED1 Open

#define LED_LED2_OFF()   GPIO_SetBits(GPIOE, GPIO_Pin_6 )  	     //LED2 Close
#define LED_LED2_ON()    GPIO_ResetBits(GPIOE, GPIO_Pin_6 )	     //LED2 Open

void LED_Init(void);   //LED init
 				    
#endif
