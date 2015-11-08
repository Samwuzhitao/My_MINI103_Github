/*****************************************************************************
 * 文件名  ：KEY.c
 * 描述    ：按键底层驱动函数库         
 * 实验平台：STM32F103VET6
 * 库版本  ：ST3.5.0
 * 作者    ：吴志涛
******************************************************************************/
#include "stm32f10x.h"
#include "key.h"
/*******************************************
 * 函数名：KEY_Init
 * 描述  ：按键初始化函数
 * 按键1 : KEY1-->GPIOD12 上拉输入 
 * 按键2 ：KEY2-->GPIOC0  上拉输入
 * 注意  ：无
*********************************************/								    
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
	//初始化KEY1-->GPIOD12 KEY2-->GPIOC0  上拉输入
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOC,ENABLE);//使能PORTD,PORTC时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;//PD12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化GPIOD12

	//初始化KEY2-->GPIOC0  上拉输入
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入	  
	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC.0

}
/*******************************************
 * 函数名 ：KEY_Scan
 * 描述   ：按键初始化函数
 * 按键1  : KEY1-->GPIOD12 上拉输入 
 * 按键2  ：KEY2-->GPIOC0  上拉输入
 * return ：返回按键值
 * 说明	  ：1，KEY1按下
		    2，KEY2按下
 * 注意	  ：此函数有响应优先级,KEY1>KEY2
*********************************************/
u8 KEY_Scan(void)
{   
	int i;
	if(KEY1==0||KEY2==0)
	{
		//OSTimeDlyHMSM(0, 0, 0, 10);//去抖动 
		for(i=0;i<0xffffff;i++);
		if(KEY1==0)return 1;
		else if(KEY2==0)return 2;
	}   
 	return 0;// 无按键按下
}
