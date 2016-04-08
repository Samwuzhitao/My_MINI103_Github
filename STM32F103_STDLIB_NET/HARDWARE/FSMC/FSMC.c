/*****************************************************************************
 * 文件名  ：FSMC.c
 * 描述    ：FSMC底层驱动函数库         
 * 实验平台：STM32F103VET6
 * 库版本  ：ST3.5.0
 * 作者    ：吴志涛
******************************************************************************/
#include "FSMC.h"
#include "core_cm3.h"
/***********************************************************************************************
								相关的FSMC对应的宏定义
**********************************************************************************************/
/*选定LCD指定寄存器*/
#define LCD_WR_REG(index)       ((*(__IO u16 *) (Bank1_LCD_C)) = ((u16)index))
/*将LCD中的index寄存器设置为val值*/
#define LCD_WR_CMD(index,val)  do{(*(__IO u16 *) (Bank1_LCD_C)) = ((u16)index);	(*(__IO u16 *) (Bank1_LCD_D)) = ((u16)(val));}while(0)
/*往LCD GRAM写入数据*/
#define LCD_WR_Data(val)        ((*(__IO u16 *) (Bank1_LCD_D)) = ((u16)(val)))	
#define LCD_S6D04H0_CMD(index)       LCD_WR_REG(index)
#define LCD_S6D04H0_Parameter(val)	 LCD_WR_Data(val)
								  
/**********************************************************************************************
								相关全局变量
***********************************************************************************************/
/*****************************************************************************
横竖屏标志位 :display_direction
取值：	     0：GRAM指针扫描方向为横屏模式
	        1：GRAM指针扫描方向为竖屏模式
说明：      该标志位的作用方便用户识别当前究竟是处于哪种模式
*******************************************************************************/  
volatile u8 display_direction = 0;
/*****************************************************************************
FSMC初始化结构体 :display_direction
*******************************************************************************/ 	 
FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
/*******************************************
 * 函数名：FSMC_Delay
 * 描述  ：在FSMC初始化时做适当的延时
 * 输入  : 无 
 * 输出  ：无
 * 举例  ：无
 * 注意  ：无
*********************************************/ 
void FSMC_Delay(int count)  // /* X1ms */
{
  int i,j;
  for(i=0;i<count;i++)
    for(j=0;j<100;j++);
}
/*******************************************
 * 函数名：LCD_GPIO_Config
 * 描述  ：根据FSMC配置LCD的I/O
 * 输入  : 无 
 * 输出  ：无
 * 举例  ：无
 * 注意  ：无
*********************************************/  
void LCD_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /* 使能FSMC时钟*/
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
    
    /* 使能FSMC对应相应管脚时钟*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE |RCC_APB2Periph_AFIO, ENABLE);
    /* 配置LCD复位控制管脚*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ; 	 
    GPIO_Init(GPIOE, &GPIO_InitStructure);  		   
    
    /* 配置FSMC相对应的数据线,FSMC-D0~D15: PD 14 15 0 1,PE 7 8 9 10 11 12 13 14 15,PD 8 9 10*/	
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF_PP;
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9 | 
                                  GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
                                  GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
                                  GPIO_Pin_15;
    GPIO_Init(GPIOE, &GPIO_InitStructure); 
    
    /* 配置FSMC相对应的控制线
	 * PD4-FSMC_NOE  :LCD-RD
     * PD5-FSMC_NWE  :LCD-WR
	 * PD7-FSMC_NE1  :LCD-CS
     * PD11-FSMC_A16 :LCD-DC
	 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);  
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);  
     
	 
	  
	GPIO_ResetBits(GPIOE, GPIO_Pin_0);
    GPIO_ResetBits(GPIOE, GPIO_Pin_1);			//RESET=0
    GPIO_SetBits(GPIOD, GPIO_Pin_4);		    //RD=1
    GPIO_SetBits(GPIOD, GPIO_Pin_5);			//WR=1
	GPIO_SetBits(GPIOD, GPIO_Pin_11); 
}

/*******************************************
 * 函数名：LCD_FSMC_Config
 * 描述  ：LCD  FSMC 模式配置
 * 输入  : 无 
 * 输出  ：无
 * 举例  ：无
 * 注意  ：无
*********************************************/ 
void LCD_FSMC_Config(void)
{
	FSMC_NORSRAMTimingInitTypeDef  readTiming;
	FSMC_NORSRAMTimingInitTypeDef  WriteTiming;
	 
	WriteTiming.FSMC_AddressSetupTime = 0x02;	 //地址建立时间
    WriteTiming.FSMC_AddressHoldTime = 0x00;	 //地址保持时间
    WriteTiming.FSMC_DataSetupTime = 0x05;		 //数据建立时间
    WriteTiming.FSMC_BusTurnAroundDuration = 0x00;
    WriteTiming.FSMC_CLKDivision = 0x00;
    WriteTiming.FSMC_DataLatency = 0x00;
    WriteTiming.FSMC_AccessMode = FSMC_AccessMode_B;	 // 一般使用模式B来控制LCD
	   
    readTiming.FSMC_AddressSetupTime = 0x02;	 //地址建立时间
    readTiming.FSMC_AddressHoldTime = 0x00;	 //地址保持时间
    readTiming.FSMC_DataSetupTime = 0x05;		 //数据建立时间
    readTiming.FSMC_BusTurnAroundDuration = 0x00;
    readTiming.FSMC_CLKDivision = 0x02;
    readTiming.FSMC_DataLatency = 0x00;
    readTiming.FSMC_AccessMode = FSMC_AccessMode_B;	 // 一般使用模式B来控制LCD
    
    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
    FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readTiming;
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &WriteTiming; 
   
    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);   
    /* 使能 FSMC Bank1_SRAM Bank */
    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE); 

}

/**********************************
 * 函数名：LCD_Rst
 * 描述  ：LCD 软件复位
 * 输入  : 无 
 * 输出  ：无
 * 举例  ：无
 * 注意  ：无
*************************************/
void LCD_Rst(void)
{			
	GPIO_ResetBits(GPIOE, GPIO_Pin_1);	 //低电平复位
    FSMC_Delay(100); 					   
    GPIO_SetBits(GPIOE, GPIO_Pin_1 );		 	 
    FSMC_Delay(120); 	
}

/********************************
 * 函数名：LCD_RD_REG
 * 描述  ：读 S6D04H0 RAM 数据
 * 输入  : 无 
 * 输出  ：读取的数据,16bit *
 * 举例  ：无
 * 注意  ：无
*************************************/
u16 LCD_RD_data(void)
{
//	u16 R=0, B=0 ;
//	LCD_S6D04H0_CMD(0x2e);	           /*LCD GRAM READ COMMAND--DATASHEET PAGE116*/
//	(*(__IO u16 *) (Bank1_LCD_D)); //FSMC_Delay(1); /*FIRST READ OUT DUMMY DATA*/
//	R =(*(__IO u16 *) (Bank1_LCD_D)); //FSMC_Delay(1);/*READ OUT RED DATA  */
//	B =(*(__IO u16 *) (Bank1_LCD_D)); //FSMC_Delay(1); /*READ OUT BLUE DATA*/
//    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);   /* 使能 FSMC Bank1_SRAM Bank */
//	return ((B&0xf800)|((R&0x00fc)<<3)|((R&0xf800)>>10)) ;
	u16 D1=0, D2=0;
	LCD_S6D04H0_CMD(0x2e);	          /*LCD GRAM READ COMMAND--DATASHEET PAGE116*/			//RS=1
	(*(__IO u16 *) (Bank1_LCD_D)); //delay_us(1); /*FIRST READ OUT DUMMY DATA*/	
	(*(__IO u16 *) (Bank1_LCD_D)); //delay_us(1);/*READ OUT RED DATA  */	
	D1 =(*(__IO u16 *) (Bank1_LCD_D)); //delay_us(1); /*READ OUT BLUE DATA*/
	D2 =(*(__IO u16 *) (Bank1_LCD_D));

    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);

	return ((D1&0xf800)|((D2&0xfc00)>>5)|((D1&0x00f8)>>3));
}

/**********************************
 * 函数名：Set_direction
 * 描述  ：设置S6D04H0GRAM指针扫描方向
 * 输入  : 0： 横向扫描
 		   1： 纵向扫描
 * 输出  ：无
 * 举例  ：无
 * 注意  ：无
*************************************/
void Set_direction(u8 option)
{

    switch(option)
    {
    case 0:
	{	    /*横屏*/
        LCD_S6D04H0_CMD(0x36); 
		LCD_S6D04H0_Parameter(0x68);    //横屏
		LCD_S6D04H0_CMD(0X2A); 
		LCD_S6D04H0_Parameter(0x00);	//start 
		LCD_S6D04H0_Parameter(0x00);
		LCD_S6D04H0_Parameter(0x01);	//end
		LCD_S6D04H0_Parameter(0x3F);
		
		LCD_S6D04H0_CMD(0X2B); 
		LCD_S6D04H0_Parameter(0x00);   //start
		LCD_S6D04H0_Parameter(0x00);
		LCD_S6D04H0_Parameter(0x00);   //end
		LCD_S6D04H0_Parameter(0xEF);
        display_direction = 0;		
        }break;
    case 1:
        {		/*竖屏*/
        LCD_S6D04H0_CMD(0x36); 
	    LCD_S6D04H0_Parameter(0x48);	//竖屏 
	    LCD_S6D04H0_CMD(0X2A); 
		LCD_S6D04H0_Parameter(0x00);
		LCD_S6D04H0_Parameter(0x00);
		LCD_S6D04H0_Parameter(0x00);
		LCD_S6D04H0_Parameter(0xEF);	
		
		LCD_S6D04H0_CMD(0X2B); 
		LCD_S6D04H0_Parameter(0x00);
		LCD_S6D04H0_Parameter(0x00);
		LCD_S6D04H0_Parameter(0x01);
		LCD_S6D04H0_Parameter(0x3F);
        display_direction = 1;
        }break;
        
    }

}




/**********************************
 * 函数名：LCD_open_windows
 * 描述  ：开窗(以x,y为坐标起点，长为len,高为wid)
 * 输入  : -x    窗户起点
           -y	   窗户起点
           -len  窗户长 
           -wid 窗户宽
 * 输出  ：无
 * 举例  ：无
 * 注意  ：无
*************************************/
void LCD_open_windows(u16 x,u16 y,u16 len,u16 wid)
{                    

    if(display_direction == 0)		/*如果是横屏选项*/
    {

		LCD_S6D04H0_CMD(0X2A); 
		LCD_S6D04H0_Parameter(x>>8);	//start 
		LCD_S6D04H0_Parameter(x-((x>>8)<<8));
		LCD_S6D04H0_Parameter((x+len-1)>>8);	//end
		LCD_S6D04H0_Parameter((x+len-1)-(((x+len-1)>>8)<<8));
		
		LCD_S6D04H0_CMD(0X2B); 
		LCD_S6D04H0_Parameter(y>>8);   //start
		LCD_S6D04H0_Parameter(y-((y>>8)<<8));
		LCD_S6D04H0_Parameter((y+wid-1)>>8);   //end
		LCD_S6D04H0_Parameter((y+wid-1)-(((y+wid-1)>>8)<<8));
     
    }
    else
    {
		LCD_S6D04H0_CMD(0X2B); 
		LCD_S6D04H0_Parameter(x>>8);
		LCD_S6D04H0_Parameter(x-((x>>8)<<8));
		LCD_S6D04H0_Parameter((x+len-1)>>8);
		LCD_S6D04H0_Parameter((x+len-1)-(((x+len-1)>>8)<<8));

	    LCD_S6D04H0_CMD(0X2A); 
		LCD_S6D04H0_Parameter(y>>8);
		LCD_S6D04H0_Parameter(y-((y>>8)<<8));
		LCD_S6D04H0_Parameter((y+wid-1)>>8);
		LCD_S6D04H0_Parameter((y+wid-1)-(((y+wid-1)>>8)<<8));	
        
    }

      LCD_S6D04H0_CMD(0x2c);     
}


/**********************************
 * 函数名：Lcd_data_start
 * 描述  ：启动S6D04H0显示
 * 输入  : 无
 * 输出  ：无
 * 举例  ：无
 * 注意  ：无
*************************************/
void Lcd_data_start(void)
{
     LCD_WR_REG(0x2C);//开始写
}
/**********************************
 * 函数名：Lcd_init_conf
 * 描述  ：S6D04H0 LCD寄存器初始配置
 * 输入  : 无
 * 输出  ：无
 * 举例  ：无
 * 注意  ：无
*************************************/
void Lcd_init_conf(void)
{
	/**********************	以下初始化代码 每个命令下带有不同数量的参数**************************/
  
  LCD_S6D04H0_CMD(0XF0);  //参考S6D04H0驱动IC手册.pdf 文档的 220页	 //LCD_S6D04H0_CMD函数 发送命令  LCD_S6D04H0_Parameter函数 传递该命令下的参数
  LCD_S6D04H0_Parameter(0X5A);          
  LCD_S6D04H0_Parameter(0X5A);          
  
  //APON CONTROL                         
  LCD_S6D04H0_CMD(0XF3);  //参考S6D04H0驱动IC手册.pdf 文档的 227页
  LCD_S6D04H0_Parameter(0X00); 
  LCD_S6D04H0_Parameter(0X00);      
  LCD_S6D04H0_Parameter(0X00);   
  LCD_S6D04H0_Parameter(0X00);           
  
  //SLEEP OUT
  LCD_S6D04H0_CMD(0X11);  //参考S6D04H0驱动IC手册.pdf 文档的 165页       
  FSMC_Delay(10); 
  
  //POWER CONTROL	   VC = "0111"
  LCD_S6D04H0_CMD(0XF4);   //参考S6D04H0驱动IC手册.pdf 文档的 228页
  LCD_S6D04H0_Parameter(0X07); 
  LCD_S6D04H0_Parameter(0X00); 
  LCD_S6D04H0_Parameter(0X00); 
  LCD_S6D04H0_Parameter(0X00);  
  LCD_S6D04H0_Parameter(0X21);             
  LCD_S6D04H0_Parameter(0X47);       
  LCD_S6D04H0_Parameter(0X01);       
  LCD_S6D04H0_Parameter(0X02);     
  LCD_S6D04H0_Parameter(0X3F); 
  LCD_S6D04H0_Parameter(0X66);   
  LCD_S6D04H0_Parameter(0X05); 
  
  //POWER CONTROL	   VC = "0111"
  LCD_S6D04H0_CMD(0XF4); //参考S6D04H0驱动IC手册.pdf 文档的 228页   带有20个参数
  LCD_S6D04H0_Parameter(0X07); 
  LCD_S6D04H0_Parameter(0X00); 
  LCD_S6D04H0_Parameter(0X00); 
  LCD_S6D04H0_Parameter(0X00);  
  LCD_S6D04H0_Parameter(0X21);             
  LCD_S6D04H0_Parameter(0X47);       
  LCD_S6D04H0_Parameter(0X04);  
  LCD_S6D04H0_Parameter(0X02);       
  LCD_S6D04H0_Parameter(0X2A);  
  LCD_S6D04H0_Parameter(0X7d);       
  LCD_S6D04H0_Parameter(0X05);  
  
  LCD_S6D04H0_CMD(0XF2);  //参考S6D04H0驱动IC手册.pdf 文档的 221页
  LCD_S6D04H0_Parameter(0X28);             
  LCD_S6D04H0_Parameter(0X60);       
  LCD_S6D04H0_Parameter(0X03);  
  LCD_S6D04H0_Parameter(0X04);       
  LCD_S6D04H0_Parameter(0X04);  
  LCD_S6D04H0_Parameter(0X00);       
  LCD_S6D04H0_Parameter(0X00);
  LCD_S6D04H0_Parameter(0X15);             
  LCD_S6D04H0_Parameter(0X48);       
  LCD_S6D04H0_Parameter(0X00);  
  LCD_S6D04H0_Parameter(0X07);       
  LCD_S6D04H0_Parameter(0X01);  
  
  LCD_S6D04H0_CMD(0XF5);  //参考S6D04H0驱动IC手册.pdf 文档的 235页
  LCD_S6D04H0_Parameter(0X00);             
  LCD_S6D04H0_Parameter(0X1d);       
  LCD_S6D04H0_Parameter(0X4f);  
  LCD_S6D04H0_Parameter(0X00);       
  LCD_S6D04H0_Parameter(0X00); 
  LCD_S6D04H0_Parameter(0X06);  
  
  
  //POWER CONTROL	
  LCD_S6D04H0_CMD(0XF3); 	 //参考S6D04H0驱动IC手册.pdf 文档的 227页
  LCD_S6D04H0_Parameter(0X00);      
  LCD_S6D04H0_Parameter(0X03); 
  LCD_S6D04H0_Parameter(0X00);          
  LCD_S6D04H0_Parameter(0X00);         
  LCD_S6D04H0_Parameter(0X00);      
  FSMC_Delay(5);  
  
  //POWER CONTROL	
  LCD_S6D04H0_CMD(0XF3); 	//参考S6D04H0驱动IC手册.pdf 文档的 227页
  LCD_S6D04H0_Parameter(0X00);                 
  LCD_S6D04H0_Parameter(0X0F); 
  LCD_S6D04H0_Parameter(0X09); 
  LCD_S6D04H0_Parameter(0X00);
  LCD_S6D04H0_Parameter(0X00);
  FSMC_Delay(5);  
  
  LCD_S6D04H0_CMD(0XF3); 	//参考S6D04H0驱动IC手册.pdf 文档的 227页
  LCD_S6D04H0_Parameter(0X00);                  
  LCD_S6D04H0_Parameter(0X0F); 
  LCD_S6D04H0_Parameter(0X01); 
  FSMC_Delay(10);
  
  //POWER CONTROL	
  LCD_S6D04H0_CMD(0XF3);   //参考S6D04H0驱动IC手册.pdf 文档的 227页
  LCD_S6D04H0_Parameter(0X00);                  
  LCD_S6D04H0_Parameter(0X1F); 
  FSMC_Delay(20);
  
  LCD_S6D04H0_CMD(0XF3);  //参考S6D04H0驱动IC手册.pdf 文档的 227页
  LCD_S6D04H0_Parameter(0X00);                  
  LCD_S6D04H0_Parameter(0X3F);    
  
  FSMC_Delay(10);
  LCD_S6D04H0_CMD(0XF3); 	//参考S6D04H0驱动IC手册.pdf 文档的 227页
  LCD_S6D04H0_Parameter(0X00);                  
  LCD_S6D04H0_Parameter(0X3F);
  LCD_S6D04H0_Parameter(0X03);
  
  
  LCD_S6D04H0_CMD(0XF3);    //参考S6D04H0驱动IC手册.pdf 文档的 227页
  LCD_S6D04H0_Parameter(0X00);              
  LCD_S6D04H0_Parameter(0X7F); 
  FSMC_Delay(30);          
  
  LCD_S6D04H0_CMD(0XF3);  //参考S6D04H0驱动IC手册.pdf 文档的 227页
  LCD_S6D04H0_Parameter(0X00);                  
  LCD_S6D04H0_Parameter(0XFF);
  
  FSMC_Delay(20);
  
  LCD_S6D04H0_CMD(0XF3);   //参考S6D04H0驱动IC手册.pdf 文档的 227页
  LCD_S6D04H0_Parameter(0X00);                 
  LCD_S6D04H0_Parameter(0XFF);   
  LCD_S6D04H0_Parameter(0X1F); 
  LCD_S6D04H0_Parameter(0X00);   
  LCD_S6D04H0_Parameter(0X02); 
  FSMC_Delay(20);
  LCD_S6D04H0_CMD(0XF3);  //参考S6D04H0驱动IC手册.pdf 文档的 227页
  LCD_S6D04H0_Parameter(0X01); 
  
  LCD_S6D04H0_CMD(0XF0); 
  LCD_S6D04H0_Parameter(0Xa5); 
  LCD_S6D04H0_Parameter(0Xa5); 
 
  LCD_S6D04H0_CMD(0X36);   //参考S6D04H0驱动IC手册.pdf 文档的 189页
  LCD_S6D04H0_Parameter(0X48); 
  
  LCD_S6D04H0_CMD(0X3a);   //参考S6D04H0驱动IC手册.pdf 文档的 195页
  LCD_S6D04H0_Parameter(0X55);   //16bit (66 18bit)
 
  FSMC_Delay(120); 
  
  LCD_S6D04H0_CMD(0x29);	 //显示打开		 //参考S6D04H0驱动IC手册.pdf 文档的 173页
  LCD_S6D04H0_CMD(0x2c);	//写数据到RAM中	
}

