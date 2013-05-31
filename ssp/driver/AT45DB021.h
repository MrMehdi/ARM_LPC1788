/****************************************************************************
AT45DB021.h basic definitions
****************************************************************************/
#include "LPC177x_8x.h"

#define PAGE_SIZE 	264
#define PAGE_COUNT	1024

uint8_t AT45DB021_ReadStatus (void);
uint8_t AT45DB021_ReadBlock (uint8_t *data, const uint32_t address, const uint32_t len);
uint8_t AT45DB021_WriteBlock (const uint8_t *data, const uint32_t address, const uint32_t len);
uint8_t AT45DB021_EraseBlock (const uint32_t address, const uint32_t len);
/*****************************************************************************
End Of File
******************************************************************************/
