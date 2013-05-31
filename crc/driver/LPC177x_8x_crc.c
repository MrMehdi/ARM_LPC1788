#include "LPC177x_8x_crc.h"

//current CRC type
volatile CRC_Type crc_cur_type;

//init internal CRC module
uint8_t CRC_Init(const CRC_Type CRCType)
{
	if(CRCType == CRC_POLY_CRCCCITT)
	{
		LPC_CRC->MODE = 0x00;
		LPC_CRC->SEED = 0xFFFF;
		crc_cur_type = CRC_POLY_CRCCCITT;
	}
	else if(CRCType == CRC_POLY_CRC16)
	{
		LPC_CRC->MODE = 0x15;
		LPC_CRC->SEED = 0x0000;
		crc_cur_type = CRC_POLY_CRC16;

	}
	else if(CRCType == CRC_POLY_CRC32)
	{
		LPC_CRC->MODE = 0x36;
		LPC_CRC->SEED = 0xFFFFFFFF;
		crc_cur_type = CRC_POLY_CRC32;
	}
	else return 0;
	return 1;
}

//reset CRC 
void CRC_Reset(void)
{
	if(crc_cur_type == CRC_POLY_CRCCCITT)			LPC_CRC->SEED = 0xFFFF;
	else if (crc_cur_type == CRC_POLY_CRC16)	LPC_CRC->SEED = 0x0000;
	else if (crc_cur_type == CRC_POLY_CRC32)	LPC_CRC->SEED = 0xFFFFFFFF;
}

//calculate CRC of data variable
uint32_t CRC_CalcDataChecksum(const uint32_t data, const CRC_WR_SIZE SizeType)
{
	if(SizeType == CRC_WR_8BIT)					LPC_CRC->WR_DATA_BYTE = (uint8_t)data;
	else if(SizeType == CRC_WR_16BIT)		LPC_CRC->WR_DATA_WORD = (uint16_t)data;
	else LPC_CRC->WR_DATA_DWORD = data;	
	return(LPC_CRC->SUM);
}

//calculate CRC of data block
uint32_t CRC_CalcBlockChecksum(const void *blockdata, const uint32_t blocksz, const CRC_WR_SIZE SizeType)
{			
	uint32_t blocksize;
	blocksize=blocksz;
	if(SizeType == CRC_WR_8BIT)
		{
			uint8_t * data;
			data = (uint8_t *) blockdata;
			while(blocksize >0)
				{
					LPC_CRC->WR_DATA_BYTE= *data;			
					data++;
					blocksize--;
				}
		}
	else if(SizeType == CRC_WR_16BIT)
		{
			uint16_t * data;
			data = (uint16_t *) blockdata;
			while(blocksize >0)
				{
					LPC_CRC->WR_DATA_WORD= *data;			
					data++;
					blocksize--;
				}
		}
	else
		{
			uint32_t * data;
			data = (uint32_t *) blockdata;
			while(blocksize >0)
				{
					LPC_CRC->WR_DATA_DWORD= *data;			
					data++;
					blocksize--;
				}		
		}
	return (LPC_CRC->SUM);
}
