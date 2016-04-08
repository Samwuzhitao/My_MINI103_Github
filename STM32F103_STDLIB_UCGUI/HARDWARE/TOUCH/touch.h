#ifndef __TOUCH_H__
#define __TOUCH_H__
#include "stm32f10x.h"

#define CMD_RDX	 0XD0
#define CMD_RDY	 0X90

#define XPT2046_CS_1   GPIOB ->ODR |= 1<< 7
#define XPT2046_CS_0   GPIOB ->ODR &= ~(1<< 7)
#define XPT2046_DI_1   GPIOA ->ODR |= 1<< 7
#define XPT2046_DI_0   GPIOA ->ODR &= ~(1<< 7)
#define XPT2046_CLK_1  GPIOA ->ODR |= 1<< 5
#define XPT2046_CLK_0  GPIOA ->ODR &= ~(1<< 5)

#define XPT2046_PEN    GPIOB ->IDR &= (1<< 6)
#define XPT2046_DO     GPIOA ->IDR &= (1<< 6)

extern unsigned int TP_X,TP_Y;	   //µ±Ç°´¥¿Ø×ø±ê

void Touch_Init(void);
void spistar(void);
void WriteCharTo7843(unsigned char num);
unsigned int ReadFromCharFrom7843(void);
int Get_Touch_x(void);
int Get_Touch_y(void);	 


#endif
