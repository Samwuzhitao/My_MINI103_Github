/*****************************************************************************
 * 文件名  ：integer.h
 * 描述    ：SD卡底数据类型定义文件定义         
 * 实验平台：STM32F103VET6
 * 库版本  ：ST3.5.0
 * 作者    ：吴志涛
******************************************************************************/
#ifndef _INTEGER
#define _INTEGER

#ifdef _WIN32	/* FatFs development platform */

#include <windows.h>
#include <tchar.h>

#else			/* Embedded platform */

/* These types must be 16-bit, 32-bit or larger integer */
typedef int				INT;
typedef unsigned int	UINT;

/* These types must be 8-bit integer */
typedef char			CHAR;
typedef unsigned char	UCHAR;
typedef unsigned char	BYTE;

/* These types must be 16-bit integer */
typedef short			SHORT;
typedef unsigned short	USHORT;
typedef unsigned short	WORD;
typedef unsigned short	WCHAR;

/* These types must be 32-bit integer */
typedef long			LONG;
typedef unsigned long	ULONG;
typedef unsigned long	DWORD;

#endif

#endif
