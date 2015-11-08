/*****************************************************************************
 * 文件名  ：Touch.c
 * 描述    ：XPT2046底层驱动函数库         
 * 实验平台：STM32F103VET6
 * 库版本  ：ST3.5.0
 * 作者    ：吴志涛
******************************************************************************/
#include "stm32f10x.h"
//#include "includes.h"
#include "touch.h"
#include "TFT_driver.h"	

unsigned int TP_X,TP_Y;	   //当前触控坐标

void Touch_Init(void)
{ 
	RCC->APB2ENR|=1<<2;  
    RCC->APB2ENR|=1<<3;  
    RCC->APB2ENR|=1<<4;  
	RCC->APB2ENR|=1<<5; 

	GPIOB->CRL&=0XF0FFFFFF;//PB6设置成输入	  
	GPIOB->CRL|=0X08000000; 	
	GPIOB->CRL&=0X0FFFFFFF;
	 
	GPIOB->CRL|=0X30000000;//PB7 推挽输出  	 
    GPIOB->ODR|=1<<7;      //PB7输出高
											  
	GPIOA->CRL&=0X0F0FFFFF;
	GPIOA->CRL|=0X30300000;//PA5、7推挽输出
	GPIOA->ODR|=1<<5;      //PA5输出高 
	GPIOA->ODR|=1<<7;      //PA5输出高

	GPIOA->CRL&=0XF0FFFFFF;//PA6设置成输入	  
	GPIOA->CRL|=0X08000000; 
}
//******************************************************
void spistar(void)                                     //SPI开始
{
	XPT2046_CS_1;
	XPT2046_CLK_1;
	XPT2046_DI_1;
	XPT2046_CLK_1;
}
//**********************************************************
void WriteCharTo7843(unsigned char num)          //SPI写数据
{
	unsigned char count=0;
	XPT2046_CLK_0;
	for(count=0;count<8;count++)
	{
		if(num & (0x80 >> count))
			XPT2046_DI_1;
		else
		    XPT2046_DI_0;
		XPT2046_CLK_0; //delay_us(3);                //上升沿有效
		XPT2046_CLK_1; //delay_us(3);
	}
}
//**********************************************************
unsigned int ReadFromCharFrom7843(void)             //SPI 读数据
{
	unsigned char count=0;
	unsigned int Num=0;
	for(count=0;count<12;count++)
	{
		Num<<=1;
		XPT2046_CLK_1; //delay_us(3);                //下降沿有效
		XPT2046_CLK_0; //delay_us(3);
		if(XPT2046_DO) Num++;
	}
	return(Num);
}

void AD7843(void)              //外部中断0 用来接受键盘发来的数据
{
	XPT2046_CS_0;
	//delayms(1);                     //中断后延时以消除抖动，使得采样数据更准确
	//while(BUSY);                //如果BUSY信号不好使可以删除不用
	//delayms(1);
	WriteCharTo7843(0x90);        //送控制字 10010000 即用差分方式读X坐标 详细请见有关资料
	//while(BUSY);               //如果BUSY信号不好使可以删除不用
	//delayms(1);
	XPT2046_CLK_1;//delay_us(3);
	XPT2046_CLK_0;//delay_us(3);
	TP_Y=ReadFromCharFrom7843();


	WriteCharTo7843(0xD0);       //送控制字 11010000 即用差分方式读Y坐标 详细请见有关资料
	XPT2046_CLK_1; //delay_us(3);
	XPT2046_CLK_0; //delay_us(3);
	TP_X=ReadFromCharFrom7843();
	XPT2046_CS_1;
}

int  Get_Touch_x(void)
{
	int temp_x;
	spistar();
	XPT2046_CS_0;
	WriteCharTo7843(CMD_RDX);       //送控制字 11010000 即用差分方式读Y坐标 详细请见有关资料
	XPT2046_CLK_1; //delay_us(3);
	XPT2046_CLK_0; //delay_us(3);
	temp_x = ReadFromCharFrom7843();
	XPT2046_CS_1;
	return temp_x;	
}

int  Get_Touch_y(void)
{
	int temp_y;
	spistar();
	XPT2046_CS_0;
	WriteCharTo7843(CMD_RDY);       //送控制字 11010000 即用差分方式读Y坐标 详细请见有关资料
	XPT2046_CLK_1; //delay_us(3);
	XPT2046_CLK_0; //delay_us(3);
	temp_y = ReadFromCharFrom7843();
	XPT2046_CS_1;
	return temp_y;	
}
