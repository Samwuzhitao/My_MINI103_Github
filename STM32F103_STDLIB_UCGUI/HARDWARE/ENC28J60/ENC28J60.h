#ifndef _ENC28J60_H
#define _ENC28J60_H

//*****************************************************************************
//
//! \addtogroup ENC28J60_ETHERNET_WORK_MODE Enc28j60 Work Mode
//! @{
//
//*****************************************************************************
#define ENC28J60_FULL_DUPLEX_MODE                                   1 ///< Full-Duplex modes
#define ENC28J60_HALF_DUPLEX_MODE                                   0 ///< Half-Duplex modes

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ENC28J60_CLKOUT_OUTPUT_DEV CLKOUT Pin outpt Dev
//! \ref ENC28J60_ECOCON_REG
//! @{
//
//*****************************************************************************
#define ENC28J60_CLKOUT_OUTPUT_DIS                                  0 ///< CLKOUT disable  
#define ENC28J60_CLKOUT_OUTPUT_DIV_1                                1 ///< CLKOUT outputs main clock divided by 1 (25 MHz)
#define ENC28J60_CLKOUT_OUTPUT_DIV_2                                2 ///< CLKOUT outputs main clock divided by 2 (12.5 MHz)
#define ENC28J60_CLKOUT_OUTPUT_DIV_3                                3 ///< CLKOUT outputs main clock divided by 3 (8.333333 MHz)
#define ENC28J60_CLKOUT_OUTPUT_DIV_4                                4 ///< CLKOUT outputs main clock divided by 4 (6.25 MHz)
#define ENC28J60_CLKOUT_OUTPUT_DIV_8                                5 ///< CLKOUT outputs main clock divided by 8 (3.125 MHz)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup ENC28J60_PHY_MODULE_MODE PHY Module LED cintrol register
//! \ref ENC28J60_PLHCON_REG[11:8] LACFG3:LACFG0: LEDA Configuration bits 
//! @{
//
//*****************************************************************************
#define ENC28J60_LEDA_CONFIG_BIT_SHIFT                              8 ///< LEDA Configuration bits Shift
#define ENC28J60_LEDA_TRANSMIT_ACT_FLAG                             1 ///< Display transmit activity (stretchable)
#define ENC28J60_LEDA_RECEIVE_ACT_FLAG                              2 ///< Display receive activity (stretchable)
#define ENC28J60_LEDA_COLLISION_ACT_FLAG                            3 ///< Display collision activity (stretchable)
#define ENC28J60_LEDA_LINK_STATUS_FLAG                              4 ///< Display link status
#define ENC28J60_LEDA_DUPLEX_STATUS_FLAG                            5 ///< Display duplex status
#define ENC28J60_LEDA_TRANSMIT_RECEIVE_ACT_FLAG                     7 ///< Display transmit and receive activity (stretchable)
#define ENC28J60_LEDA_ON_FLAG                                       8 ///< On
#define ENC28J60_LEDA_OFF_FLAG                                      9 ///< OFF
#define ENC28J60_LEDA_BLINK_FAST_FLAG                              10 ///< Blink fast
#define ENC28J60_LEDA_BLINK_SLOW_FLAG                              11 ///< Blink slow
#define ENC28J60_LEDA_BLINK_STATUS_RECEIVE_ACT_FLAG                12 ///< Display link status and receive activity (always stretched)
#define ENC28J60_LEDA_BLINK_STATUS_RECEIVE_TRANSMIT_ACT_FLAG       13 ///< Display link status and transmit/receive activity (always stretched)
#define ENC28J60_LEDA_DUPLEX_STATUS_COLLISION_ACT_FLAG             14 ///<  Display duplex status and collision activity (always stretched)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ENC28J60_PHY_MODULE_MODE PHY Module LED cintrol register
//! \ref ENC28J60_PLHCON_REG[7:4] LBCFG3:LBCFG0: LEDB Configuration bits  
//! @{
//
//*****************************************************************************
#define ENC28J60_LEDB_CONFIG_BIT_SHIFT                              4 ///< LEDA Configuration bits Shift
#define ENC28J60_LEDB_TRANSMIT_ACT_FLAG                             1 ///< Display transmit activity (stretchable)
#define ENC28J60_LEDB_RECEIVE_ACT_FLAG                              2 ///< Display receive activity (stretchable)
#define ENC28J60_LEDB_COLLISION_ACT_FLAG                            3 ///< Display collision activity (stretchable)
#define ENC28J60_LEDB_LINK_STATUS_FLAG                              4 ///< Display link status
#define ENC28J60_LEDB_DUPLEX_STATUS_FLAG                            5 ///< Display duplex status
#define ENC28J60_LEDB_TRANSMIT_RECEIVE_ACT_FLAG                     7 ///< Display transmit and receive activity (stretchable)
#define ENC28J60_LEDB_ON_FLAG                                       8 ///< On
#define ENC28J60_LEDB_OFF_FLAG                                      9 ///< OFF
#define ENC28J60_LEDB_BLINK_FAST_FLAG                              10 ///< Blink fast
#define ENC28J60_LEDB_BLINK_SLOW_FLAG                              11 ///< Blink slow
#define ENC28J60_LEDB_BLINK_STATUS_RECEIVE_ACT_FLAG                12 ///< Display link status and receive activity (always stretched)
#define ENC28J60_LEDB_BLINK_STATUS_RECEIVE_TRANSMIT_ACT_FLAG       13 ///< Display link status and transmit/receive activity (always stretched)
#define ENC28J60_LEDB_DUPLEX_STATUS_COLLISION_ACT_FLAG             14 ///<  Display duplex status and collision activity (always stretched)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ENC28J60_PHY_MODULE_MODE PHY Module LED cintrol register
//! \ref ENC28J60_PLHCON_REG[3:2] LFRQ1:LFRQ0: LED Pulse Stretch Time Configuration bits (see Table 2-1)  
//! @{
//
//*****************************************************************************
#define ENC28J60_LED_PULSE_STRETCH_BIT_SHIFT                        2 ///< LED Pulse Stretch Time Configuration bits Shift
#define ENC28J60_LED_STRETCH_BY_TNSTRCH                             0 ///< Stretch LED events by TNSTRCH
#define ENC28J60_LED_STRETCH_BY_TMSTRCH                             1 ///< Stretch LED events by TMSTRCH
#define ENC28J60_LED_STRETCH_BY_TLSTRCG                             2 ///< Stretch LED events by TLSTRCH

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ENC28J60_PHY_MODULE_MODE PHY Module LED cintrol register
//! \ref ENC28J60_PLHCON_REG[1] LED Pulse Stretching Enable bit 
//! @{
//
//*****************************************************************************
#define ENC28J60_LED_PULSE_STRETCH_ENABLE_BIT_SHIFT                 1 ///< LED Pulse Stretching Enable bit Shift
#define ENC28J60_LED_STRETCH_ENABLE                                 0 ///< Stretchable LED events will only be displayed while they are occurring
#define ENC28J60_LED_STRETCH_DISABLE                                1 ///< Stretchable LED events will cause lengthened LED pulses based on LFRQ1:LFRQ0 configuration

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ENC28J60_COMMAND_CODES the command codes for all operations. 
//! \note TABLE 4-1 SPI INSTRUCTION SET FOR THE ENC28J60
//!      Instruction     |     Byte0         |       Byte1          
//!  Name and Mnemoninic |Opcode | Argument  |       Data
//!         RCR          | 0 0 0 | A A A A A |       N/A
//!         RBM          | 0 0 1 | 1 1 0 1 0 |       N/A
//!         WCR          | 0 1 0 | A A A A A | D D D D D D D D 
//!         WBM          | 0 1 1 | 1 1 0 1 0 | D D D D D D D D 
//!         BFS          | 1 0 0 | A A A A A | D D D D D D D D 
//!         BFC          | 1 0 1 | A A A A A | D D D D D D D D 
//!         SRC          | 1 1 1 | 1 1 1 1 1 |       N/A
//! Legend: A = control register ,D = dada Payload
//!                           
//! @{
//
//*****************************************************************************
#define ENC28J60_RCR_OPCODE                                      0x00 ///< Read Control Register(RCR)  
#define ENC28J60_WCR_OPCODE                                      0x40 ///< Write Control Register(WCR) 
#define ENC28J60_WBM_OPCODE                                      0x7A ///< Write Buffer Memory (WBM)
#define ENC28J60_RBM_OPCODE                                      0x3A ///< Read Buffer Memory(RBM)
#define ENC28J60_BFS_OPCODE                                      0x80 ///< Bit Field Set(BFS)
#define ENC28J60_BFC_OPCODE                                      0xA0 ///< Bit Field Clear(BFC)
#define ENC28J60_SRC_OPCODE                                      0xFF ///< System Reset Command (Soft Reset)(SRC)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************



#endif
