/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "MyBoard_BSP.h"
#include "GUI.h"
#include "DIALOG.h"
#include "GUIDEMO.h"

/* Private variables ---------------------------------------------------------*/
uint8_t GUI_Initialized   = 0;

extern WM_HWIN CreateMy_Board_GUI(void);
/**
 ******************************************************************************
 函数名称：My_Board_BSP_Init
 输入参数: 无
 输出参数：无
 描    述：实现开发板初始化
 *****************************************************************************/
int main(void)
{
	GUI_Initialized = 1;
	
	My_Board_BSP_Init();
	GUI_Init();
	
	CreateMy_Board_GUI();

}

