//*****************************************************************************
//
//! \file    : Hw_ENC28J60.h
//! \brief   : Stand-Alone Ethernet Controller with SPI Interface ENC28J60.
//! \version : 1.1.1.0
//! \date    : 12/10/2014
//! \author  : Sam.wu
//! \note    :
//!            1.IEEE 802.3 Compatible Ethernet Controller
//!            2.Fully Compatible with 10/100/1000Base-T Networks
//!            3.Integrated MAC and 10Base-T PHY
//!            4.Supports One 10Base-T Port with Automatic Polarity Detection and Correction
//!            5.Supports Full and Half-Duplex modes
//!            6.Programmable Automatic Retransmit on Collision
//!            7.Programmable Padding and CRC Generation
//!            8.Programmable Automatic Rejection of Erroneous Packets
//!            9.SPI Interface with Clock Speeds Up to 20 MHz
//
//*****************************************************************************
#ifndef _HW_ENC28J60_H
#define _HW_ENC28J60_H
#include "stm32f10x.h"
//*****************************************************************************
//
//! \addtogroup ENC28J60_CONTROL_REGISTER Control Register
//! \note The Control registers provide the main interface between the host 
//!       controller and the on-chip Ethernet controller logic
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ENC28J60_REGISTER_ADRESS_MASK Register Adress Msak
//! \note bank number, and Ethernet/MAC/PHY indicator bits 
//! @{
//
//*****************************************************************************
#define ENC28J60_ALL_BANK_EIE_REG                                0x1B ///<
#define ENC28J60_ALL_BANK_EIR_REG                                0x1C ///<
#define ENC28J60_ALL_BANK_ESTAT_REG                              0x1D ///<
#define ENC28J60_ALL_BANK_ECON2_REG                              0x1E ///<
#define ENC28J60_ALL_BANK_ECON1_REG                              0x1F ///< ETHERNET CONTROL REGISTER 1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************
typedef struct
{
  uint8_t  BSEL:2;                   ///< bit:  0.. 1 Bank Select bits
  uint8_t  RXEN:1;                   ///< bit:      2 Receive Enable bit
  uint8_t  RXRTS:1;                  ///< bit:      3 Transmit Request to Send bit 
  uint8_t  CSUMEN:1;                 ///< bit:      4 DMA Checksum Enable bit
  uint8_t  DMAST:1;                  ///< bit:      5 DMA Start and Busy Status bit
  uint8_t  RXRST:1;                  ///< bit:      6 Receive Logic Reset bit
  uint8_t  TXRST:1;                  ///< bit:      7 Transmit Logic Reset bit	
}
ECON1_REG_Type;

typedef struct
{
	uint8_t  _reserved0:3;             ///< bit:  0.. 2 Unimplemented: Read as 0
  uint8_t  VRPS:1;                   ///< bit:      3 Voltage Regulator Power Save Enable bit
  uint8_t  _reserved1:1;             ///< bit:      4 Reserved: Maintain as 0
  uint8_t  PWRSV:1;                  ///< bit:      5 Power Save Enable bit
	uint8_t  PKTDEC:1;                 ///< bit:      6 Packet Decrement bit
	uint8_t  AUTOINC:1;                ///< bit:      7 Automatic Buffer Pointer Increment Enable bit
}
ECON2_REG_Type;



//*****************************************************************************
//
//! \addtogroup ENC28J60_CONTROL_REGISTER_ETH_REGISTER ETH Register 
//! \ref None 
//! @{
//
//*****************************************************************************
/************************** BANK0 REGISTER ******************************/
#define ENC28J60_BANK0_ERDPTL_REG                         (0x00|0x00) ///< Clock Output Configuration COCON[2:0]
#define ENC28J60_BANK0_ERDPTH_REG                         (0x01|0x00) ///< PHY MODULE LED CONTROL REGISTER
#define ENC28J60_BANK0_EWRPTL_REG                         (0x02|0x00) ///<
#define ENC28J60_BANK0_EWRPTH_REG                         (0x03|0x00) ///<
#define ENC28J60_BANK0_ETXSTL_REG                         (0x04|0x00) ///<
#define ENC28J60_BANK0_ETXSTH_REG                         (0x05|0x00) ///<
#define ENC28J60_BANK0_ETXNDL_REG                         (0x06|0x00) ///<
#define ENC28J60_BANK0_ETXNDH_REG                         (0x07|0x00) ///<
#define ENC28J60_BANK0_ERXSTL_REG                         (0x08|0x00) ///<
#define ENC28J60_BANK0_ERXSTH_REG                         (0x09|0x00) ///<
#define ENC28J60_BANK0_ERXNDL_REG                         (0x0A|0x00) ///<
#define ENC28J60_BANK0_ERXNDH_REG                         (0x0B|0x00) ///<
#define ENC28J60_BANK0_ERXRDPTL_REG                       (0x0C|0x00) ///<
#define ENC28J60_BANK0_ERXRDPTH_REG                       (0x0D|0x00) ///<
#define ENC28J60_BANK0_ERXWRPTL_REG                       (0x0E|0x00) ///<
#define ENC28J60_BANK0_ERXWRPTH_REG                       (0x0F|0x00) ///<
#define ENC28J60_BANK0_EDMASTL_REG                        (0x10|0x00) ///<
#define ENC28J60_BANK0_EDMASTH_REG                        (0x11|0x00) ///<
#define ENC28J60_BANK0_EDMANDL_REG                        (0x12|0x00) ///<
#define ENC28J60_BANK0_EDMANDH_REG                        (0x13|0x00) ///<
#define ENC28J60_BANK0_EDMADSTL_REG                       (0x14|0x00) ///<
#define ENC28J60_BANK0_EDMADSTH_REG                       (0x15|0x00) ///<
#define ENC28J60_BANK0_EDMACSL_REG                        (0x16|0x00) ///<
#define ENC28J60_BANK0_EDMACSH_REG                        (0x17|0x00) ///<
/************************** BANK1 REGISTER ******************************/
#define ENC28J60_BANK1_EHT0_REG                                  0x00 ///<
#define ENC28J60_BANK1_EHT1_REG                                  0x01 ///<
#define ENC28J60_BANK1_EHT2_REG                                  0x02 ///<
#define ENC28J60_BANK1_EHT3_REG                                  0x03 ///<
#define ENC28J60_BANK1_EHT4_REG                                  0x04 ///<
#define ENC28J60_BANK1_EHT5_REG                                  0x05 ///<
#define ENC28J60_BANK1_EHT6_REG                                  0x06 ///<
#define ENC28J60_BANK1_EHT7_REG                                  0x07 ///<
#define ENC28J60_BANK1_EPMM0_REG                                 0x08 ///<
#define ENC28J60_BANK1_EPMM1_REG                                 0x09 ///<
#define ENC28J60_BANK1_EPMM2_REG                                 0x0A ///<
#define ENC28J60_BANK1_EPMM3_REG                                 0x0B ///<
#define ENC28J60_BANK1_EPMM4_REG                                 0x0C ///<
#define ENC28J60_BANK1_EPMM5_REG                                 0x0D ///<
#define ENC28J60_BANK1_EPMM6_REG                                 0x0E ///<
#define ENC28J60_BANK1_EPMM7_REG                                 0x0F ///<
#define ENC28J60_BANK1_EPMCSL_REG                                0x10 ///<
#define ENC28J60_BANK1_EPMCLH_REG                                0x11 ///<
#define ENC28J60_BANK1_EPMOL_REG                                 0x14 ///<
#define ENC28J60_BANK1_EPMOH_REG                                 0x15 ///<
#define ENC28J60_BANK1_ERXFCON_REG                               0x18 ///<
#define ENC28J60_BANK1_EPKTCNT_REG                               0x19 ///<
/************************** BANK3 REGISTER ******************************/
#define ENC28J60_BANK3_EBSTSD_REG                                0x06 ///<
#define ENC28J60_BANK3_EBSTCON_REG                               0x07 ///<
#define ENC28J60_BANK3_EBSTCSL_REG                               0x08 ///<
#define ENC28J60_BANK3_EBSTCSH_REG                               0x09 ///<
#define ENC28J60_BANK3_EREVID_REG                                0x12 ///<
#define ENC28J60_BANK3_ECOCON_REG                                0x15 ///<
#define ENC28J60_BANK3_EFLOCON_REG                               0x17 ///<
#define ENC28J60_BANK3_EPAUSL_REG                                0x18 ///<
#define ENC28J60_BANK3_EPAUSH_REG                                0x19 ///<

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ENC28J60_CONTROL_REGISTER_MAC_REGISTER MAC Register 
//! \ref None 
//! @{
//
//*****************************************************************************
/************************** BANK2 REGISTER ******************************/
#define ENC28J60_BANK2_MACON1_REG                                0x00 ///<
#define ENC28J60_BANK2_MACON3_REG                                0x02 ///<
#define ENC28J60_BANK2_MACON4_REG                                0x03 ///<
#define ENC28J60_BANK2_MABBIPG_REG                               0x04 ///<
#define ENC28J60_BANK2_MAIPGL_REG                                0x06 ///<
#define ENC28J60_BANK2_MAIPGH_REG                                0x07 ///<
#define ENC28J60_BANK2_MACLCON1_REG                              0x08 ///<
#define ENC28J60_BANK2_MACLCON2_REG                              0x09 ///<
#define ENC28J60_BANK2_MAMXFLL_REG                               0x0A ///<
#define ENC28J60_BANK2_MAMXFLH_REG                               0x0B ///<
/************************** BANK3 REGISTER ******************************/
#define ENC28J60_BANK3_MAADR5_REG                                0x00 ///<
#define ENC28J60_BANK3_MAADR6_REG                                0x01 ///<
#define ENC28J60_BANK3_MAADR3_REG                                0x02 ///<
#define ENC28J60_BANK3_MAADR4_REG                                0x03 ///<
#define ENC28J60_BANK3_MAADR1_REG                                0x04 ///<
#define ENC28J60_BANK3_MAADR2_REG                                0x05 ///<

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ENC28J60_CONTROL_REGISTER_MII_REGISTER MII Register
//! \ref None 
//! @{
//
//*****************************************************************************
/************************** BANK2 REGISTER ******************************/
#define ENC28J60_BANK2_MICMD_REG                                 0x12 ///<
#define ENC28J60_BANK2_MIREGADR_REG                              0x14 ///<
#define ENC28J60_BANK2_MIWRL_REG                                 0x16 ///<
#define ENC28J60_BANK2_MIWRH_REG                                 0x17 ///<
#define ENC28J60_BANK2_MIEDL_REG                                 0x18 ///<
#define ENC28J60_BANK2_MIEDH_REG                                 0x19 ///<
/************************** BANK3 REGISTER ******************************/
#define ENC28J60_BANK3_MISTAT_REG                                0x0A ///<

//*****************************************************************************
//
//! @}
//
//*****************************************************************************
typedef struct
{
	uint8_t  MIIRD:1;                  ///< bit:      0 MII Read Enable bit
  uint8_t  MIISCAN:1;                ///< bit:      1 MII Scan Enable bit
  uint8_t  _reserved0:6;             ///< bit:  2.. 7 Unimplemented: Read as 0
}
MICMD_REG_Type;

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ENC28J60_REGISTER_ETH_BUFFER ETH BUFFER ADRESS 
//! \ref None 
//! @{
//
//*****************************************************************************
#define ENC28J60_ETH_TX_BUF_START                              0x0000 ///< Transmit Buffer Start(ETXSTH:ETXSTL)
#define ENC28J60_ETH_TX_BUF_END                                0x0000 ///< Transmit Buffer End(ETXNDH:ETXNDL)
#define ENC28J60_ETH_RX_BUF_START                              0x0000 ///< Receive Buffer Start(ERXSTH:ERXSTL)
#define ENC28J60_ETH_RX_BUF_END                                0x0000 ///< Receive Buffer End(ERXNDH:ERXNDL)
//#define ENC28J60_ETH_TX_BUF_POINTER                          0x0000 ///< Buffer Write Pointer(EWRPTH:EWRPTL)
//#define ENC28J60_ETH_RX_BUF_POINTER                          0x0000 ///< Buffer Read Pointer(ERDPTH:ERDPTL)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ENC28J60_REGISTER_MAP_PHY PHY Register 
//! \ref None 
//! @{
//
//*****************************************************************************
#define ENC28J60_PHCON1_REG                                      0x00 ///<
#define ENC28J60_PHSTAT1_REG                                     0x01 ///<
#define ENC28J60_PHID1_REG                                       0x02 ///<
#define ENC28J60_PHID2_REG                                       0x03 ///<
#define ENC28J60_PHCON2_REG                                      0x10 ///<
#define ENC28J60_PHSTAT2_REG                                     0x11 ///<
#define ENC28J60_PHIE_REG                                        0x12 ///<
#define ENC28J60_PHIR_REG                                        0x13 ///<
#define ENC28J60_PHLCON_REG                                      0x14 ///<

//*****************************************************************************
//
//! @}
//
//*****************************************************************************
typedef struct
{
	uint16_t  _reserved0:1;            ///< bit:      0 Unimplemented: Read as 0
  uint16_t  JBSTAT:1;                ///< bit:      1 PHY Latching Jabber Status bit
  uint16_t  LLSTAT:1;                ///< bit:      2 PHY Latching Link Status bit
	uint16_t  _reserved1:8;            ///< bit:  3..10 Unimplemented: Read as 0
	uint16_t  PHDPX:1;                 ///< bit:     11 PHY Half-Duplex Capable bit
	uint16_t  PFDPX:1;                 ///< bit:     12	PHY Full-Duplex Capable bit 
	uint16_t  _reserved2:3;            ///< bit: 13..15 Unimplemented: Read as 0		
}
PHSTAT1_REG_Type;

typedef struct
{
	uint16_t  _reserved0:5;            ///< bit:  0.. 4 Unimplemented: Read as 0
    uint16_t  PLRITY:1;                ///< bit:      5 Polarity Status bit
	uint16_t  _reserved1:3;            ///< bit:  6.. 8 Unimplemented: Read as 0
    uint16_t  DPXSTAT:1;               ///< bit:      9 PHY Duplex Status bit(1)
	uint16_t  LSTAT:1;                 ///< bit:     10 PHY Link Status bit (non-latching)
	uint16_t  COLSTAT:1;               ///< bit:     11 PHY Collision Status bit
	uint16_t  RXSTST:1;                ///< bit:     12	PHY Receive Status bit
	uint16_t  TXSTAT:1;                ///< bit:     13	PHY Transmit Status bit
	uint16_t  _reserved2:2;            ///< bit: 14..15 Unimplemented: Read as 0		
}
PHSTAT2_REG_Type;






typedef struct
{
	uint32_t  RBC:16;                  ///< bit:  0..15 Received Byte Count
  uint32_t  LEDE:1;                  ///< bit:     16 Long Event/Drop Event
  uint32_t  CEPS:1;                  ///< bit:     18 Carrier Event Previously Seen 
	uint32_t  CRCE:1;                  ///< bit:     20 CRC Error
	uint32_t  LCE:1;                   ///< bit:     21 Length Check Error
	uint32_t  LO0R:1;                  ///< bit:     22 Length Out of Range
  uint32_t  ROK:1;                   ///< bit:     23 Received Ok
  uint32_t  RMP:1;                   ///< bit:     24 Receive Multicast Packet
  uint32_t  RBP:1;                   ///< bit:     25 Receive Broadcast Packet	
  uint32_t  DB:1;                    ///< bit:     26 Dribble Nibble
  uint32_t  RCF:1;                   ///< bit:     27 Receive Control Frame
  uint32_t  RPCF:1;                  ///< bit:     28 Receive Pause Control Frame 
  uint32_t  RUO:1;                   ///< bit:     29	Receive Unknown Opcode
  uint32_t  RVTD:1;                  ///< bit:     30	Receive VLAN Type Detected   
	uint32_t  _reserved0:1;            ///< bit:     31 Unimplemented: Read as 0
}
RECEIVE_STATUS_VECTORS_Type;









typedef struct
{
	uint8_t  BUSY:1;                   ///< bit:      0 MII Management Busy bit
  uint8_t  SCAN:1;                   ///< bit:      1 MII Management Scan Operation bit
  uint8_t  NVALID:1;                 ///< bit:      2 MII Management Read Data Not Valid bit
	uint8_t  _reserved0:5;             ///< bit:  3.. 7 Unimplemented: Read as 0
}
MISTATUS_REG_Type;

typedef struct
{
	uint8_t  MARXEN:1;                 ///< bit:      0 MAC Receive Enable bit
  uint8_t  PASSALL:1;                ///< bit:      1 Pass All Received Frames Enable bit
  uint8_t  RXPAUS:1;                 ///< bit:      2 Pause Control Frame Reception Enable bit
	uint8_t  TXPAUS:1;                 ///< bit:      3 Pause Control Frame Transmission Enable bit
	uint8_t  _reserved0:4;             ///< bit:  4.. 7 Unimplemented: Read as 0	
}
MACCON1_REG_Type;

typedef struct
{
	uint8_t  FULDPX:1;                 ///< bit:      0 MAC Full-Duplex Enable bit
  uint8_t  FRMLNEN:1;                ///< bit:      1 Frame Length Checking Enable bit
  uint8_t  HFRMEN:1;                 ///< bit:      2 Huge Frame Enable bit
	uint8_t  PHDREN:1;                 ///< bit:      3 Proprietary Header Enable bit
	uint8_t  TXCRCEN:1;                ///< bit:      4 Transmit CRC Enable bit
	uint8_t  PADCFG:3;                 ///< bit:  5.. 7 Automatic Pad and CRC Configuration bits
}
MACCON3_REG_Type;

typedef struct
{
	uint8_t  _reserved0:4;             ///< bit:  0.. 3 Reserved: Maintain as 0
  uint8_t  NOBKOFF:1;                ///< bit:      4 No Backoff Enable bit (applies to half duplex only)
  uint8_t  BPEN:1;                   ///< bit:      5 No Backoff During Backpressure Enable bit (applies to half duplex only)
	uint8_t  DEFER:1;                  ///< bit:      6 Defer Transmission Enable bit (applies to half duplex only)
	uint8_t  _reserved1:1;             ///< bit:      7 Unimplemented: Read as 0
}
MACCON4_REG_Type;

#endif
