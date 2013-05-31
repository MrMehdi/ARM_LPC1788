/****************************************************************************
LPC177x_8x_crc.h basic definitions
****************************************************************************/
#include "LPC177x_8x.h"

typedef enum
{
	CRC_POLY_CRCCCITT = 0,		// CRC CCITT polynomial 
	CRC_POLY_CRC16,						// CRC-16 polynomial 
	CRC_POLY_CRC32						// CRC-32 polynomial 
}CRC_Type;

typedef enum
{
	CRC_WR_8BIT = 0,				// 8-bit write: 1-cycle operation 
	CRC_WR_16BIT,						// 16-bit write: 2-cycle operation 
	CRC_WR_32BIT						// 32-bit write: 4-cycle operation 
}CRC_WR_SIZE;

uint8_t CRC_Init(const CRC_Type CRCType);
void CRC_Reset(void);
uint32_t CRC_CalcDataChecksum(const uint32_t data, const CRC_WR_SIZE SizeType);
uint32_t CRC_CalcBlockChecksum(const void *blockdata, const uint32_t blocksz, const CRC_WR_SIZE SizeType);

/*****************************************************************************
End Of File
******************************************************************************/
