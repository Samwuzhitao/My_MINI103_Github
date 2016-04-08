/**
  ******************************************************************************
  * @file    usbd_hid_core.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    22-July-2011
  * @brief   header file for the usbd_hid_core.c file.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/

#ifndef __USB_HID_CORE_H_
#define __USB_HID_CORE_H_

#include  "usbd_ioreq.h"

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @{
  */
  
/** @defgroup USBD_HID
  * @brief This file is the Header file for USBD_msc.c
  * @{
  */ 


/** @defgroup USBD_HID_Exported_Defines
  * @{
  */ 
#define USB_HID_CONFIG_DESC_SIZ       41
#define USB_HID_DESC_SIZ              9
#define HID_MOUSE_REPORT_DESC_SIZE    33

#define HID_DESCRIPTOR_TYPE           0x21
#define HID_REPORT_DESC               0x22


#define HID_REQ_SET_PROTOCOL          0x0B
#define HID_REQ_GET_PROTOCOL          0x03

#define HID_REQ_SET_IDLE              0x0A
#define HID_REQ_GET_IDLE              0x02

#define HID_REQ_SET_REPORT            0x09
#define HID_REQ_GET_REPORT            0x01


/* HID Request Codes */
#define HID_REQUEST_GET_REPORT          0x01
#define HID_REQUEST_GET_IDLE            0x02
#define HID_REQUEST_GET_PROTOCOL        0x03
#define HID_REQUEST_SET_REPORT          0x09
#define HID_REQUEST_SET_IDLE            0x0A
#define HID_REQUEST_SET_PROTOCOL        0x0B

/* HID Report Types */
#define HID_REPORT_INPUT                0x01
#define HID_REPORT_OUTPUT               0x02
#define HID_REPORT_FEATURE              0x03

/************************************** Configuration ******************************************/
#define USBD_HID_INREPORT_MAX_SZ    64
#define USBD_HID_OUTREPORT_MAX_SZ   64
#define USBD_HID_FEATREPORT_MAX_SZ  1


/************************************ Report Item Define ***************************************/
/* Error "Keys" */
#define HID_USAGE_KEYBOARD_NOEVENT              0x00
#define HID_USAGE_KEYBOARD_ROLLOVER             0x01
#define HID_USAGE_KEYBOARD_POSTFAIL             0x02
#define HID_USAGE_KEYBOARD_UNDEFINED            0x03

/* Letters */
#define HID_USAGE_KEYBOARD_aA                   0x04
#define HID_USAGE_KEYBOARD_zZ                   0x1D

/* Numbers */
#define HID_USAGE_KEYBOARD_ONE                  0x1E
#define HID_USAGE_KEYBOARD_ZERO                 0x27

#define HID_USAGE_KEYBOARD_RETURN               0x28
#define HID_USAGE_KEYBOARD_ESCAPE               0x29
#define HID_USAGE_KEYBOARD_DELETE               0x2A

/* Funtion Keys */
#define HID_USAGE_KEYBOARD_F1                   0x3A
#define HID_USAGE_KEYBOARD_F12                  0x45

#define HID_USAGE_KEYBOARD_PRINT_SCREEN         0x46

/* Modifier Keys */
#define HID_USAGE_KEYBOARD_LCTRL                0xE0
#define HID_USAGE_KEYBOARD_LSHFT                0xE1
#define HID_USAGE_KEYBOARD_LALT                 0xE2
#define HID_USAGE_KEYBOARD_LGUI                 0xE3
#define HID_USAGE_KEYBOARD_RCTRL                0xE4
#define HID_USAGE_KEYBOARD_RSHFT                0xE5
#define HID_USAGE_KEYBOARD_RALT                 0xE6
#define HID_USAGE_KEYBOARD_RGUI                 0xE7
#define HID_USAGE_KEYBOARD_SCROLL_LOCK          0x47
#define HID_USAGE_KEYBOARD_NUM_LOCK             0x53
#define HID_USAGE_KEYBOARD_CAPS_LOCK            0x39

/* Modifier Keys (values) */
#define HID_USAGE_KEYBOARD_MOD_LCTRL            0x01
#define HID_USAGE_KEYBOARD_MOD_LSHIFT           0x02
#define HID_USAGE_KEYBOARD_MOD_LALTL            0x04
#define HID_USAGE_KEYBOARD_MOD_LGUI             0x08
#define HID_USAGE_KEYBOARD_MOD_RCTRL            0x10
#define HID_USAGE_KEYBOARD_MOD_RSHIFT           0x20
#define HID_USAGE_KEYBOARD_MOD_RALTL            0x40
#define HID_USAGE_KEYBOARD_MOD_RGUI             0x80

/* ... */

/* LED Page (0x08) */
#define HID_USAGE_LED_NUM_LOCK                  0x01
#define HID_USAGE_LED_CAPS_LOCK                 0x02
#define HID_USAGE_LED_SCROLL_LOCK               0x03
#define HID_USAGE_LED_COMPOSE                   0x04
#define HID_USAGE_LED_KANA                      0x05
#define HID_USAGE_LED_POWER                     0x06
#define HID_USAGE_LED_SHIFT                     0x07
#define HID_USAGE_LED_DO_NOT_DISTURB            0x08
#define HID_USAGE_LED_MUTE                      0x09
#define HID_USAGE_LED_TONE_ENABLE               0x0A
#define HID_USAGE_LED_HIGH_CUT_FILTER           0x0B
#define HID_USAGE_LED_LOW_CUT_FILTER            0x0C
#define HID_USAGE_LED_EQUALIZER_ENABLE          0x0D
#define HID_USAGE_LED_SOUND_FIELD_ON            0x0E
#define HID_USAGE_LED_SURROUND_FIELD_ON         0x0F
#define HID_USAGE_LED_REPEAT                    0x10
#define HID_USAGE_LED_STEREO                    0x11
#define HID_USAGE_LED_SAMPLING_RATE_DETECT      0x12
#define HID_USAGE_LED_SPINNING                  0x13
#define HID_USAGE_LED_CAV                       0x14
#define HID_USAGE_LED_CLV                       0x15
#define HID_USAGE_LED_RECORDING_FORMAT_DET      0x16
#define HID_USAGE_LED_OFF_HOOK                  0x17
#define HID_USAGE_LED_RING                      0x18
#define HID_USAGE_LED_MESSAGE_WAITING           0x19
#define HID_USAGE_LED_DATA_MODE                 0x1A
#define HID_USAGE_LED_BATTERY_OPERATION         0x1B
#define HID_USAGE_LED_BATTERY_OK                0x1C
#define HID_USAGE_LED_BATTERY_LOW               0x1D
#define HID_USAGE_LED_SPEAKER                   0x1E
#define HID_USAGE_LED_HEAD_SET                  0x1F
#define HID_USAGE_LED_HOLD                      0x20
#define HID_USAGE_LED_MICROPHONE                0x21
#define HID_USAGE_LED_COVERAGE                  0x22
#define HID_USAGE_LED_NIGHT_MODE                0x23
#define HID_USAGE_LED_SEND_CALLS                0x24
#define HID_USAGE_LED_CALL_PICKUP               0x25
#define HID_USAGE_LED_CONFERENCE                0x26
#define HID_USAGE_LED_STAND_BY                  0x27
#define HID_USAGE_LED_CAMERA_ON                 0x28
#define HID_USAGE_LED_CAMERA_OFF                0x29
#define HID_USAGE_LED_ON_LINE                   0x2A
#define HID_USAGE_LED_OFF_LINE                  0x2B
#define HID_USAGE_LED_BUSY                      0x2C
#define HID_USAGE_LED_READY                     0x2D
#define HID_USAGE_LED_PAPER_OUT                 0x2E
#define HID_USAGE_LED_PAPER_JAM                 0x2F
#define HID_USAGE_LED_REMOTE                    0x30
#define HID_USAGE_LED_FORWARD                   0x31
#define HID_USAGE_LED_REVERSE                   0x32
#define HID_USAGE_LED_STOP                      0x33
#define HID_USAGE_LED_REWIND                    0x34
#define HID_USAGE_LED_FAST_FORWARD              0x35
#define HID_USAGE_LED_PLAY                      0x36
#define HID_USAGE_LED_PAUSE                     0x37
#define HID_USAGE_LED_RECORD                    0x38
#define HID_USAGE_LED_ERROR                     0x39
#define HID_USAGE_LED_SELECTED_INDICATOR        0x3A
#define HID_USAGE_LED_IN_USE_INDICATOR          0x3B
#define HID_USAGE_LED_MULTI_MODE_INDICATOR      0x3C
#define HID_USAGE_LED_INDICATOR_ON              0x3D
#define HID_USAGE_LED_INDICATOR_FLASH           0x3E
#define HID_USAGE_LED_INDICATOR_SLOW_BLINK      0x3F
#define HID_USAGE_LED_INDICATOR_FAST_BLINK      0x40
#define HID_USAGE_LED_INDICATOR_OFF             0x41
#define HID_USAGE_LED_FLASH_ON_TIME             0x42
#define HID_USAGE_LED_SLOW_BLINK_ON_TIME        0x43
#define HID_USAGE_LED_SLOW_BLINK_OFF_TIME       0x44
#define HID_USAGE_LED_FAST_BLINK_ON_TIME        0x45
#define HID_USAGE_LED_FAST_BLINK_OFF_TIME       0x46
#define HID_USAGE_LED_INDICATOR_COLOR           0x47
#define HID_USAGE_LED_RED                       0x48
#define HID_USAGE_LED_GREEN                     0x49
#define HID_USAGE_LED_AMBER                     0x4A
#define HID_USAGE_LED_GENERIC_INDICATOR         0x4B

/* Button Page (0x09) */
/*   There is no need to label these usages. */

/* Ordinal Page (0x0A) */
/*   There is no need to label these usages. */

/* Telephony Device Page (0x0B) */
#define HID_USAGE_TELEPHONY_PHONE               0x01
#define HID_USAGE_TELEPHONY_ANSWERING_MACHINE   0x02
#define HID_USAGE_TELEPHONY_MESSAGE_CONTROLS    0x03
#define HID_USAGE_TELEPHONY_HANDSET             0x04
#define HID_USAGE_TELEPHONY_HEADSET             0x05
#define HID_USAGE_TELEPHONY_KEYPAD              0x06
#define HID_USAGE_TELEPHONY_PROGRAMMABLE_BUTTON 0x07
/* ... */

/* Consumer Page (0x0C) */
#define HID_USAGE_CONSUMER_CONTROL              0x01
/* ... */

/* and others ... */


/* HID Report Item Macros */

/* Main Items */
#define HID_Input(x)           0x81,x
#define HID_Output(x)          0x91,x
#define HID_Feature(x)         0xB1,x
#define HID_Collection(x)      0xA1,x
#define HID_EndCollection      0xC0

/* Data (Input, Output, Feature) */
#define HID_Data               0<<0
#define HID_Constant           1<<0
#define HID_Array              0<<1
#define HID_Variable           1<<1
#define HID_Absolute           0<<2
#define HID_Relative           1<<2
#define HID_NoWrap             0<<3
#define HID_Wrap               1<<3
#define HID_Linear             0<<4
#define HID_NonLinear          1<<4
#define HID_PreferredState     0<<5
#define HID_NoPreferred        1<<5
#define HID_NoNullPosition     0<<6
#define HID_NullState          1<<6
#define HID_NonVolatile        0<<7
#define HID_Volatile           1<<7

/* Collection Data */
#define HID_Physical           0x00
#define HID_Application        0x01
#define HID_Logical            0x02
#define HID_Report             0x03
#define HID_NamedArray         0x04
#define HID_UsageSwitch        0x05
#define HID_UsageModifier      0x06

/* Global Items */
#define HID_UsagePage(x)       0x05,x
#define HID_UsagePageVendor(x) 0x06,x,0xFF
#define HID_LogicalMin(x)      0x15,x
#define HID_LogicalMinS(x)     0x16,(x&0xFF),((x>>8)&0xFF)
#define HID_LogicalMinL(x)     0x17,(x&0xFF),((x>>8)&0xFF),((x>>16)&0xFF),((x>>24)&0xFF)
#define HID_LogicalMax(x)      0x25,x
#define HID_LogicalMaxS(x)     0x26,(x&0xFF),((x>>8)&0xFF)
#define HID_LogicalMaxL(x)     0x27,(x&0xFF),((x>>8)&0xFF),((x>>16)&0xFF),((x>>24)&0xFF)
#define HID_PhysicalMin(x)     0x35,x
#define HID_PhysicalMinS(x)    0x36,(x&0xFF),((x>>8)&0xFF)
#define HID_PhysicalMinL(x)    0x37,(x&0xFF),((x>>8)&0xFF),((x>>16)&0xFF),((x>>24)&0xFF)
#define HID_PhysicalMax(x)     0x45,x
#define HID_PhysicalMaxS(x)    0x46,(x&0xFF),((x>>8)&0xFF)
#define HID_PhysicalMaxL(x)    0x47,(x&0xFF),((x>>8)&0xFF),((x>>16)&0xFF),((x>>24)&0xFF)
#define HID_UnitExponent(x)    0x55,x
#define HID_Unit(x)            0x65,x
#define HID_UnitS(x)           0x66,(x&0xFF),((x>>8)&0xFF)
#define HID_UnitL(x)           0x67,(x&0xFF),((x>>8)&0xFF),((x>>16)&0xFF),((x>>24)&0xFF)
#define HID_ReportSize(x)      0x75,x
#define HID_ReportSizeS(x)     0x76,(x&0xFF),((x>>8)&0xFF)
#define HID_ReportSizeL(x)     0x77,(x&0xFF),((x>>8)&0xFF),((x>>16)&0xFF),((x>>24)&0xFF)
#define HID_ReportID(x)        0x85,x
#define HID_ReportCount(x)     0x95,x
#define HID_ReportCountS(x)    0x96,(x&0xFF),((x>>8)&0xFF)
#define HID_ReportCountL(x)    0x97,(x&0xFF),((x>>8)&0xFF),((x>>16)&0xFF),((x>>24)&0xFF)
#define HID_Push               0xA4
#define HID_Pop                0xB4

/* Local Items */
#define HID_Usage(x)           0x09,x
#define HID_UsageMin(x)        0x19,x
#define HID_UsageMax(x)        0x29,x

/* USB HID Class API enumerated constants                                     */
enum {
  USBD_HID_REQ_EP_CTRL = 0,             /* Request from control endpoint      */
  USBD_HID_REQ_EP_INT,                  /* Request from interrupt endpoint    */
  USBD_HID_REQ_PERIOD_UPDATE            /* Request from periodic update       */
};

/**
  * @}
  */ 


/** @defgroup USBD_CORE_Exported_TypesDefinitions
  * @{
  */


/**
  * @}
  */ 



/** @defgroup USBD_CORE_Exported_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup USBD_CORE_Exported_Variables
  * @{
  */ 

extern USBD_Class_cb_TypeDef  USBD_HID_cb;
/**
  * @}
  */ 

/** @defgroup USB_CORE_Exported_Functions
  * @{
  */ 
uint8_t USBD_HID_SendReport (USB_OTG_CORE_HANDLE  *pdev, uint8_t *report, uint16_t len);
uint8_t USBD_HID_GetReport  (USB_OTG_CORE_HANDLE  *pdev, uint8_t *report, uint16_t len);
/**
  * @}
  */ 

#endif  // __USB_HID_CORE_H_
/**
  * @}
  */ 

/**
  * @}
  */ 
  
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
