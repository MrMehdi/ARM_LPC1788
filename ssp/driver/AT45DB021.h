/****************************************************************************
AT45DB021.h basic definitions
****************************************************************************/
#include "LPC177x_8x.h"

#define PAGE_SIZE 	264
#define PAGE_COUNT	1024

uint8_t AT45DB021_ReadStatus (void);
uint8_t AT45DB021_ReadBlock (uint8_t *data, uint32_t address, uint32_t length);
uint8_t AT45DB021_WriteBlock (uint8_t *data, uint32_t address, uint32_t length);
uint8_t AT45DB021_EraseBlock (uint32_t address, uint32_t length);
/*****************************************************************************
End Of File
******************************************************************************/
