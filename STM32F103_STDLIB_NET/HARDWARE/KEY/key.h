#ifndef __KEY_H
#define __KEY_H	 
#include "stm32f10x.h"


//#define KEY1 PDin(12)	//PD12
//#define KEY2 PCin(0)	//PC0 	 

#define KEY1 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12)	//PD12
#define KEY2 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)	//PC0 	 
	 
void KEY_Init(void);//IO初始化
u8 KEY_Scan(void);  //按键扫描函数					    
#endif
