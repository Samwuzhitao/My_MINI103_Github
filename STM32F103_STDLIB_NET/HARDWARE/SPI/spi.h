#ifndef __SPI_H
#define	__SPI_H
#include "stm32f10x.h"

// SPI总线速度设置 
#define SPI_SPEED_2   0
#define SPI_SPEED_4   1
#define SPI_SPEED_8   2
#define SPI_SPEED_16  3
#define SPI_SPEED_256 4


void SPIx_Init(void);
void SPIx_SetSpeed(u8 SpeedSet);
u8 SPIx_ReadWriteByte(u8 TxData);


#endif
