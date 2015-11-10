#include "stm32f2xx_hal.h"
#include "stm322xg_eval.h"
#include "usbd_cdc_interface.h"
#include "stdio.h"
#include <stdarg.h>

UART_HandleTypeDef UartHandle;

void My_Uart_init()
{
	UartHandle.Instance        = USARTx;

  UartHandle.Init.BaudRate   = 115200;
  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits   = UART_STOPBITS_1;
  UartHandle.Init.Parity     = UART_PARITY_ODD;
  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode       = UART_MODE_TX_RX;
	  
	if (HAL_UART_Init(&UartHandle) != HAL_OK)
  {
    /* Initialization Error */
    while(1)
		{}
  }


}

int fputc(int ch, FILE *f)
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
  HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}
