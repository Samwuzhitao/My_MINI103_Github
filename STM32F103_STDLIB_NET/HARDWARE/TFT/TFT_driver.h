#ifndef __TFT_DRIVER_H
#define __TFT_DRIVER_H

#include "stm32f10x.h"

/*¶¨Òå³£ÓÃÑÕÉ«µÄÑÕÉ«Âë*/
#define RED     0xf800	//ºì
#define MAGENTA 0xF81F //Ñóºì
#define YELLOW  0xffe0	//»Æ
#define GREEN   0x07e0	//ÂÌ
#define CYAN    0x07ff	//Çà
#define BLUE    0x001f	//À¶
#define PURPLE  0xf81f	//×Ï
#define BLACK   0x0000	//ºÚ
#define WHITE   0xffff	//°×
#define GRAY    0x7bef	//»Ò
#define GRAY_WHITE    0xc638	//°×ÑÌ
#define BROWN 	0XBC40 //×ØÉ«
#define BRRED 	0XFC07 //×ØºìÉ«
#define LGRAY 	0XC618 //Ç³»ÒÉ«(PANNEL),´°Ìå±³¾°É«

void LCD_Set_BackColor(u16 Color);
void TFT_Display_On(void);
void delayms(int count);
void TFT_Init(void);
void TFT_SetScreenDir(unsigned char screenDir);

void Address_set(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1);
void TFT_clearZone(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1,unsigned int b_color);

void TFT_clearscreen(unsigned int b_color);
void LCD_Draw_Point(unsigned int x, unsigned int y, unsigned int color);
void LCD_Draw_BigPoint(unsigned int x, unsigned int y, unsigned int color);
unsigned int RGB(unsigned char R,unsigned char G,unsigned char B);
void LCD_draw_line(unsigned int x1 , unsigned int y1 , unsigned int x2 , unsigned int y2 , unsigned int color);
void LCD_Draw_Rectangle( unsigned int left,unsigned int top,unsigned int right,unsigned int bottom,unsigned int color);
void LCD_draw_round(unsigned int x , unsigned int y , unsigned int r , unsigned int color);
void LCD_Draw_Picture(u16 StartX,u16 StartY,u16 EndX,u16 EndY,const unsigned char *pic);
unsigned int  LCD_Get_Point(unsigned int x, unsigned int y);


void LCD_char88(unsigned int X, unsigned int Y, char c, unsigned int color);
void LCD_char816( unsigned int X , unsigned int Y , char c , unsigned int color );
void LCDShow_Number(unsigned int x,unsigned int y,int num,unsigned int forecolor);

#endif
