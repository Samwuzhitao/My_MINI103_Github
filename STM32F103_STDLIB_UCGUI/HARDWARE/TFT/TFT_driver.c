/*****************************************************************************
 * 文件名  ：TFT_Driver.c
 * 描述    ：S6D04H0底层驱动函数库         
 * 实验平台：STM32F103VET6
 * 库版本  ：ST3.5.0
 * 作者    ：吴志涛
******************************************************************************/
#include "stm32f10x.h"
#include "TFT_driver.h"
#include "math.h"
#include "FSMC.h"
/***********************************************************************************************
			相关的FSMC对应的宏定义
**********************************************************************************************/
#define LCD_S6D04H0_CMD(index)       LCD_WR_REG(index)
#define LCD_S6D04H0_Parameter(val)	 LCD_WR_Data(val)
/**********************************************************************************************
			背景颜色全局变量
***********************************************************************************************/
u16 BACK_COLOR = 0;
/***********************************************************************************************
设置字体显示背景颜色
入口参数：无。
出口参数: 无
说明：设置字体显示背景颜色。
************************************************************************************************/
void LCD_Set_BackColor(u16 Color)
{
	BACK_COLOR = Color;
}	
/************************************************************************************************
开启屏幕显示
入口参数：无。
出口参数: 无
说明：开启屏幕显示。
**************************************************************************************************/
void TFT_Display_On(void)
{
	LCD_S6D04H0_CMD(0x29);	 //发送命令
}
/***********************************************************************************************
关闭屏幕显示
入口参数：无。
出口参数: 无
说明：关闭屏幕显示。
*************************************************************************************************/
void TFT_Display_Off(void)
{
	LCD_S6D04H0_CMD(0x28);	 //发送命令
}

/***********************************************************************************************
设置打点方向
入口参数：screenDir选择的方式。
出口参数: 无
说明：使用背景颜色清除TFT模块屏幕的全部显示内容。
**************************************************************************************************/
void TFT_SetScreenDir(unsigned char screenDir)
{
  LCD_S6D04H0_CMD(0X36);   //参考S6D04H0驱动IC手册.pdf 文档的 189页
  switch (screenDir)
  {
	  case 0x00: LCD_S6D04H0_Parameter(0X08);  //2->1->4->3，上反
	  case 0x01: LCD_S6D04H0_Parameter(0X28);  //2->4->1->3，右正
	  case 0x02: LCD_S6D04H0_Parameter(0X48);  //1->2->3->4，上正
	  case 0x03: LCD_S6D04H0_Parameter(0X68);  //1->3->2->4，左反
	  case 0x04: LCD_S6D04H0_Parameter(0X88);  //4->3->2->1，下正
	  case 0x05: LCD_S6D04H0_Parameter(0Xa8);  //4->2->3->1，右反
	  case 0x06: LCD_S6D04H0_Parameter(0Xc8);  //3->4->1->2，下反
	  case 0x07: LCD_S6D04H0_Parameter(0Xe8);  //3->1->4->2，左正 常用
	  default :  LCD_S6D04H0_Parameter(0X48);   //1->2->3->4，上正
  }
   
  
}
/**********************************************************************************************************
设置窗口
入口参数: x0 y0,为显示窗口左上角坐标；x1,y1为显示窗口右下角坐标。
出口参数: 无
说明：该函数设置TFT模块的显示窗口。
************************************************************************************************************/
void Address_set(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1)
{	
	//LCD_open_windows(x0,y0,x1-x0,y1-y0);
	LCD_S6D04H0_CMD(0X2A);    //设置X坐标地址	 //参考S6D04H0驱动IC手册.pdf 文档的 174页
	LCD_S6D04H0_Parameter(x0>>8);   //开始X
	LCD_S6D04H0_Parameter(x0);      //开始X
	LCD_S6D04H0_Parameter(x1>>8);   //结束X
	LCD_S6D04H0_Parameter(x1);      //结束X

	LCD_S6D04H0_CMD(0X2B);	//设置Y坐标地址	 //参考S6D04H0驱动IC手册.pdf 文档的 176页
	LCD_S6D04H0_Parameter(y0>>8);	  //开始Y
	LCD_S6D04H0_Parameter(y0);	  //开始Y
	LCD_S6D04H0_Parameter(y1>>8);   //结束Y
	LCD_S6D04H0_Parameter(y1);   //结束Y

	//LCD_S6D04H0_CMD(0x13);
	LCD_S6D04H0_CMD(0x29);	 //显示打开//参考S6D04H0驱动IC手册.pdf 文档的 173页
	LCD_S6D04H0_CMD(0x2c);
								 
}
/**********************************************************************************************************
清屏
入口参数： b_color是背景颜色。
	   x;0~319
	   Y:0~239
出口参数: 无
说明：使用背景颜色清除TFT模块屏幕的全部显示内容。
************************************************************************************************************/
void TFT_clearZone(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1,unsigned int b_color)
{
	unsigned long int i;
	Address_set(x0,y0,x1,y1);	 
	//Lcd_data_start();   
	for(i=0; i<(x1-x0+1)*(y1-y0+1); i++)		 		
	{
			LCD_WR_Data(b_color); 					    
	}

}

/***********************************************************************************************************
清屏
入口参数： b_color是背景颜色。
出口参数: 无
说明：使用背景颜色清除TFT模块屏幕的全部显示内容。
*************************************************************************************************************/
void TFT_clearscreen(unsigned int b_color)
{
	TFT_clearZone(0,0,320,240,b_color);
}
/************************************************************************************************************
画点
入口参数： (x，y)是点的坐标，color 是点的颜色。
出口参数: 无
说明：用指定的颜色在指定的坐标位置上画出一个点。
**************************************************************************************************************/
void LCD_Draw_Point(unsigned int x, unsigned int y, unsigned int color)
{  
	 Address_set(x,y,x,y); 
	LCD_WR_Data(color);
}
void LCD_Draw_BigPoint(unsigned int x, unsigned int y, unsigned int color)
{
  unsigned int i, j;
  for(i=0; i<3; i++)
  {
    for(j=0; j<3; j++) 
    LCD_Draw_Point(x+i, y+j, color);
  }
}

/**************************************************************************************************************** 
RGB颜色混合
入口参数：R（红色分量）0-255,G（绿色分量）0-255,B（蓝色分量）0-255
出口参数: 按R5-G6-B5格式混合后的16位颜色码。
说明：将电脑上常见的R8-G8-B8格式转换成8位单片机常用的R5-G6-B5格式。
*****************************************************************************************************************/
unsigned int RGB(unsigned char R,unsigned char G,unsigned char B)
{
	return((unsigned int)(R&0XF8)<<8|(unsigned int)(G&0XFC)<<3|(unsigned int)(B&0XF8)>>3);
}
/*****************************************************************************************************************
子程序入口: x1:直线起点横坐标
            y1:直线起点纵坐标
            x2:直线终点横坐标
            y2:直线终点纵坐标
子程序出口: none
子程序功能: 画直线
*******************************************************************************************************************/
void LCD_draw_line(unsigned int x1 , unsigned int y1 , unsigned int x2 , unsigned int y2 , unsigned int color)
{
	unsigned int x = x1 << 8,y = y1 << 8;     //高8位为坐标值，低8位为积分累加器
	int dx = x2 - x1, dy = y2 - y1;

	while( abs(dx) < 64 && abs(dy) < 64 && dx * dy != 0 ) 
	{
		dx*=6;
		dy*=6;
	} //调整插补速度	 //2

	while( (x >> 8) != x2 || (y >> 8) != y2)
	{
		LCD_Draw_Point(x>>8, y>>8 , color);
		x += dx;
		y += dy;
	}

	LCD_Draw_Point( x>>8 , y>>8 , color );

}
/*********************************************************************************************************************
子程序入口: left ：点1的x方向坐标
            top ：点1的y方向坐标
            right ：点2的x方向坐标
            bottom ：点2的y方向坐标
            color:颜色
子程序出口: none
子程序功能: 绘制矩形框
*********************************************************************************************************************/ 
void LCD_Draw_Rectangle( unsigned int left,unsigned int top,unsigned int right,unsigned int bottom,unsigned int color)
{
	LCD_draw_line(left,top,right,top,color);
	LCD_draw_line(left,top,left,bottom,color);
	LCD_draw_line(right,top,right,bottom,color);
	LCD_draw_line(left,bottom,right,bottom,color);
}
/*********************************************************************************************8***********************
子程序入口: x:圆点横坐标
            y:圆点纵坐标
            r:圆点半径
子程序出口: none
子程序功能: 画正圆
*********************************************************************************************************************/ 
void LCD_draw_round(unsigned int x , unsigned int y , unsigned int r , unsigned int color)
{
	float angle;
	unsigned int dx,dy;
	for(angle=0; angle < 3.14 / 4; angle+=0.03)//0.03
	{
		dx = r * sin(angle);
		dy = r * cos(angle);

		LCD_Draw_Point( x + dx, y + dy , color );
		LCD_Draw_Point( x - dx, y + dy , color );
		LCD_Draw_Point( x + dx, y - dy , color );
		LCD_Draw_Point( x - dx, y - dy , color );
		LCD_Draw_Point( x + dy, y + dx , color );
		LCD_Draw_Point( x - dy, y + dx , color );
		LCD_Draw_Point( x + dy, y - dx , color );
		LCD_Draw_Point( x - dy, y - dx , color );
	}
}
/****************************************************************************
* 名    称：void DrawPicture(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16 *pic)
* 功    能：在指定座标范围显示一副图片
* 入口参数：StartX     行起始座标
*           StartY     列起始座标
*           EndX       行结束座标
*           EndY       列结束座标
pic        图片头指针
* 出口参数：无
* 说    明：图片取模格式为水平扫描，16位颜色模式
* 调用方法：DrawPicture(0,0,100,100,(u16*)demo);
****************************************************************************/
void LCD_Draw_Picture(u16 StartX,u16 StartY,u16 EndX,u16 EndY,const unsigned char *pic)
{
    u16  i;
    Address_set(StartX,StartY,EndX,EndY);	    
    for (i=0;i<((EndX-StartX)*(EndY-StartY));i++) 
	LCD_WR_Data(*pic++);
}
/****************************************************************************
* 名    称：u16 GetPoint(u16 x,u16 y)
* 功    能：获取指定座标的颜色值
* 入口参数：x      行座标
*           y      列座标
* 出口参数：当前座标颜色值
* 说    明：
* 调用方法：i=GetPoint(10,10);
****************************************************************************/
unsigned int  LCD_Get_Point(unsigned int x, unsigned int y)
{ 

	u16 temp;
	Address_set(x,y,x,y);
	temp=LCD_RD_data();
    return (temp);
}

/****************************************************************************
子程序入口: X    :起点横坐标
            Y    :起点纵坐标
            c    :ASCII码
            color:字体颜色
子程序出口: none
子程序功能: 8*8 ASCII码显示函数
****************************************************************************/
#include"8x8.h"//8*8 ASCII码字模
void LCD_char88(unsigned int X, unsigned int Y, char c, unsigned int color)
{ 
	unsigned int k,i,j;  

	for( j = 0; j < 8; j++ ) //列
		for( i = 0; i < 8; i++ )  //行
		{ 
			k = i ;
			if( Font8x8[c][j]  & (0x80 >> k) ) //判断每行各点的是否着色	
				LCD_Draw_Point( X + i, j + Y , color);		
			else
				LCD_Draw_Point( X + i, j + Y , BACK_COLOR);	 	
		} 
}

/****************************************************************************
子程序入口: X    :起点横坐标
            Y    :起点纵坐标
            c    :ASCII码
            color:字体颜色
子程序出口: none
子程序功能: 8*16 ASCII码显示函数
****************************************************************************/
#include"8x16.h"//8*16 ASCII码字模
void LCD_char816( unsigned int X , unsigned int Y , char c , unsigned int color )
{ 
	unsigned int k,i,j;  

	for( j=0; j<16; j++ ) //列
		for( i=0; i<8; i++ )  //行
		{ 
			k = i ;
			if( Font8x16[c][j] & (0x80 >> k) ) //判断每行各点的是否着色		
				LCD_Draw_Point( X + i, j + Y , color);			
			else
				LCD_Draw_Point( X + i, j + Y , BACK_COLOR);
		} 
}
/****************************************************************************
子程序入口: X    :起点横坐标
            Y    :起点纵坐标
            num  :需要显示的数字
            color:字体颜色
子程序出口: none
子程序功能: 显示0~65536之间的数字
****************************************************************************/
void LCDShow_Number(unsigned int x,unsigned int y,int num,unsigned int forecolor)
{
 	unsigned char disNum[5],i,temp;
	disNum[0] = num/10000 ;
	disNum[1] = num%10000/1000;
	disNum[2] = num%1000/100;
	disNum[3] = num%100/10;
	disNum[4] = num%10;
	for(i=0;disNum[i]==0&&i<4;i++);
	temp=i;
	for(i=0;i<5;i++)
	{
		if(i<temp) 
			LCD_char816( x+8*i,y,' ',forecolor);
		else 
			LCD_char816( x+8*i,y,disNum[i]+'0',forecolor);
	}
	
}
/****************************************************************************
子程序入口: 无
子程序出口: none
子程序功能: 初始化TFT屏
****************************************************************************/
 void TFT_Init(void)
{
      
    LCD_GPIO_Config();
    LCD_FSMC_Config();		
    LCD_Rst();
		Lcd_init_conf();
		Set_direction(0);
		TFT_SetScreenDir(1);			     		
}  
