#include "stm32f10x.h"
#include "SD.h"


void My_SPI_init( void )
{
  	GPIO_InitTypeDef  GPIO_InitStructure;
	 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PA端口时钟

 
}

uint32_t SD_Init( void )
{

}

void SD_WriteMultiBlocks( unsigned int num )
{

}

void SD_ReadMultiBlocks( unsigned int num )
{

}