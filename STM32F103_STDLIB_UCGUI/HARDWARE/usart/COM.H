#if !defined  (_COM_H)
#define _COM_H
#include  "stm32f10x.h"

void sendchar (int ch);
void myprintf(char *buf);
void USART_Config(USART_TypeDef* USARTx,u32 baud);
char *itoa(int value, char *string, int radix);
void USART_OUT(USART_TypeDef* USARTx, uint8_t *Data,...);
int SendChar (int ch);

#endif

