#include "stm32f10x.h"
#include "LED.h"

void LED_init( void )
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE,ENABLE );
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_5 ;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
  GPIO_Init( GPIOE ,&GPIO_InitStructure ); 

}

void LED_On1( void )
{
	GPIO_SetBits( GPIOE, GPIO_Pin_6 );
	
}

void LED_Off1( void )
{
	GPIO_ResetBits( GPIOE, GPIO_Pin_6 );
	
}
void LED_On2( void )
{
	GPIO_SetBits( GPIOE, GPIO_Pin_5 );
	
}

void LED_Off2( void )
{
	GPIO_ResetBits( GPIOE, GPIO_Pin_5 );
	
}