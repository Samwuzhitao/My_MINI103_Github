#ifndef __USART_H
#define	__USART_H

#include "stm32f10x.h"
#include <stdio.h>

void MyUSART_Init(void);
void USART_Config_Default(void);
int fputc(int ch, FILE *f);
void USART1_printf(USART_TypeDef* USARTx, uint8_t *Data,...);

#endif /* __USART1_H */
