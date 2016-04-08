/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "led.h"
#include "TFT_driver.h"

int main(void)
{
  LED_Init();
	TFT_Init();
	
	LED_LED1_ON();
	LED_LED2_ON();
	
	LCD_Set_BackColor(BLACK);
	TFT_clearscreen(BLACK);
	LCD_char816( 0 , 0 ,'c' , GREEN );
	LCDShow_Number(8,0,123,GREEN);
	
  while (1)
  {
    
  }
}

