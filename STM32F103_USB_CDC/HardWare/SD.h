#ifndef __SD_H__
#define __SD_H__
#include "stm32f10x.h"

void My_SPI_init( void );

uint32_t SD_Init( void );

void SD_WriteMultiBlocks( unsigned int num );

void SD_ReadMultiBlocks( unsigned int num );

#endif
