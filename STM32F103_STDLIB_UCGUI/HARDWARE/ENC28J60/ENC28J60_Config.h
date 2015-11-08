#ifndef _ENC28J60_CONFIG_H
#define _ENC28J60_CONFIG_H

#define ENC28J60_USE_WORK_MODE               ENC28J60_FULL_DUPLEX_MODE ///< Full and Half-Duplex modes
#define ENC28J60_SPI_MODE                    ENC28J60_SPI_ ///

#define ENC28J60_CS                                         GPIO_Pin_4 ///< PA4
#define ENC28J60_CSL()		                    GPIOA->BRR = ENC28J60_CS ///< PA4 = 0
#define ENC28J60_CSH()		                   GPIOA->BSRR = ENC28J60_CS ///< PA4 = 1

#define ENC28J60_CLK                                        GPIO_Pin_5 ///< PA5
#define ENC28J60_MOSI                                       GPIO_Pin_6 ///< PA6
#define ENC28J60_MISO                                       GPIO_Pin_7 ///< PA7
#define ENC28J60_REST                                       GPIO_Pin_1 ///< PE1
#define ENC28J60_INT                                        GPIO_PIN_4 ///< PE4

short unsigned int gsuv_eth_buf_start

#endif
