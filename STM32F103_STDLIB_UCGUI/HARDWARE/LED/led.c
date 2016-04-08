/*****************************************************************************
 * 文件名  ：LED.c
 * 描述    ：LED底层驱动函数库         
 * 实验平台：STM32F103VET6
 * 库版本  ：ST3.5.0
 * 作者    ：吴志涛
******************************************************************************/
#include "stm32f10x.h"
#include "led.h"

/*******************************************
 * 函数名：LED_Init
 * 描述  ：初始化PE5和PE6为输出口.并使能这两个口的时钟
 * 输入  : 无 
 * 输出  ：无
 * 举例  ：无
 * 注意  ：无
*********************************************/
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE); //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;	 //LED0-->PB.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOE, &GPIO_InitStructure);					       //根据设定参数初始化GPIOB.5
 GPIO_SetBits(GPIOE,GPIO_Pin_5|GPIO_Pin_6);						 //PB.5 输出高
}
 
/*******************************************
 * 函数名：LED_Delay
 * 描述  ：在LED初始化时做适当的延时
 * 输入  : 无 
 * 输出  ：无
 * 举例  ：无
 * 注意  ：无
*********************************************/ 
void LED_Delay(int count)  // /* X1ms */
{
  int i,j;
  for(i=0;i<count;i++)
    for(j=0;j<100;j++);
}
