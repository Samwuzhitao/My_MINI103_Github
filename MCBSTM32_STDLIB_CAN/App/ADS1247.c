
#include "platform_config.h"
#include "platform_init.h"
#include "stm32f10x.h"  
#include "stm32f10x_it.h" 
#include "ADS1247.h"

#define ADS1247_WRITE_REG_DELAYMS 10

/******************************************************************************
  Function:ADS1247_ReadWriteData
  Description:
  Input:None
  Output:
  Return:
  Others:None
******************************************************************************/
uint8_t ADS1247_ReadWriteData( uint8_t data )
{
	while (SPI_I2S_GetFlagStatus(SPI, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI, data );
	while (SPI_I2S_GetFlagStatus(SPI, SPI_I2S_FLAG_RXNE) == RESET);
	return SPI_I2S_ReceiveData(SPI);
}

/******************************************************************************
  Function:ADS1247_Delay
  Description:
  Input:None
  Output:
  Return:
  Others:None
******************************************************************************/
void ADS1247_Delay(unsigned int nCount)	
{
  Delay(nCount);
}
/******************************************************************************
  Function:ADS1247_ReadRegister
  Description:
  Input:
		addr : Start register adddress (0 to 15)
		num  : number of registers to be read (number of bytes - 1)
  Output:
  Return:
  Others:None
******************************************************************************/
void ADS1247_ReadRegisters( uint8_t addr, uint8_t num, uint8_t data[] )
{
	uint8_t i;
	
	CS_0;
	
	ADS1247_ReadWriteData( addr | ADS1247_CMD_RREG );
	
	ADS1247_ReadWriteData( num );
	
	for(i=0; i<num+1; i++)
	{
		data[i] = ADS1247_ReadWriteData(ADS1247_CMD_NOP);
	}
	
	CS_1;
}

/******************************************************************************
  Function:ADS1247_ReadRegister
  Description:
  Input:
		addr : Start register adddress (0 to 15)
		num  : number of registers to be read (number of bytes - 1)
  Output:
  Return:
  Others:None
******************************************************************************/
uint8_t ADS1247_ReadRegister( uint8_t addr )
{
	uint8_t data;
	
	CS_0;
	
	ADS1247_ReadWriteData( addr | ADS1247_CMD_RREG );
	
	ADS1247_ReadWriteData( 0x00 );
	
	data = ADS1247_ReadWriteData( ADS1247_CMD_NOP );
	

	CS_1;
	
	return data;
}
/******************************************************************************
  Function:ADS1247_ReadRegister
  Description:
  Input:
		addr : Start register adddress (0 to 15)
		num  : number of registers to be read (number of bytes - 1)
  Output:
  Return:
  Others:None
******************************************************************************/
void ADS1247_WriteRegisters( uint8_t addr, uint8_t num, uint8_t data[] )
{
	uint8_t i;
	
	CS_0;
	
	ADS1247_ReadWriteData( addr | ADS1247_CMD_WREG );
	
	ADS1247_ReadWriteData( num );
	
	for(i=0; i<num+1; i++)
	{
		 ADS1247_ReadWriteData(data[i]);
	}
	
	CS_1;
}

/******************************************************************************
  Function:ADS1247_ReadRegister
  Description:
  Input:
		addr : Start register adddress (0 to 15)
		data : data 
  Output:
  Return:
  Others:None
******************************************************************************/
void ADS1247_WriteRegister( uint8_t addr, int8_t data )
{
	CS_0;
	
	ADS1247_ReadWriteData( addr | ADS1247_CMD_WREG );
	
	ADS1247_ReadWriteData( 0x00 );
	
	ADS1247_ReadWriteData( data );
	
	CS_1;
}
/******************************************************************************
  Function:ADS1247_ReadWriteData
  Description:
  Input:None
  Output:
  Return:
  Others:None
******************************************************************************/
void ADS1247_Init( void )
{
	// Reset ADC 
	ADS1247_ReadWriteData( ADS1247_CMD_RESET );
	ADS1247_Delay(60);
	
	// Positive = IN1 Negitive = IN2 
	ADS1247_WriteRegister( ADS1247_REG_MUX0, 0x0A );
	ADS1247_Delay(ADS1247_WRITE_REG_DELAYMS);
	
	// not Enable Bias voltage
	ADS1247_WriteRegister( ADS1247_REG_VBIAS, 0x00 );
	ADS1247_Delay(ADS1247_WRITE_REG_DELAYMS);
	
	// Set Internal OSC, (IDAC)Internal reference, (ADC)OnBoard reference 
	ADS1247_WriteRegister( ADS1247_REG_MUX1, 0x30 );
	ADS1247_Delay(ADS1247_WRITE_REG_DELAYMS);
	
	// Set PGA = 1   DOR = 320SPS
	ADS1247_WriteRegister( ADS1247_REG_SYS0, 0x06 );
	ADS1247_Delay(ADS1247_WRITE_REG_DELAYMS);
	
	// Set DOUT/(/D/R/D/Y) pin functons only as Data Out 
  // I = 200uA	
	ADS1247_WriteRegister( ADS1247_REG_IDAC0, 0x02 );
	ADS1247_Delay(ADS1247_WRITE_REG_DELAYMS);
	
	// Connected the AIN0 and AIN3 pin for the  source DAC
	ADS1247_WriteRegister( ADS1247_REG_IDAC1, 0x30 );
	ADS1247_Delay(ADS1247_WRITE_REG_DELAYMS);
}

/******************************************************************************
  Function:ADS1247_ReadWriteData
  Description:
  Input:None
  Output:
  Return:
  Others:None
******************************************************************************/
uint32_t ADS1247_ReadData( void )
{
	uint8_t i,Data[3];
	
	CS_0;

	ADS1247_ReadWriteData( ADS1247_CMD_RDATA );
	
	for(i=0; i<3; i++)
	{
		Data[i] = ADS1247_ReadWriteData(ADS1247_CMD_NOP);
	}
	
	CS_1;

	return (Data[0]<<16 | Data[1]<<8 | Data[2]);
}
