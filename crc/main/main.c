#include "LPC177x_8x_uart.h"
#include "LPC177x_8x_crc.h"

#define BLOCK_SIZE 10

int main(void)
{
	uint8_t BlockData[BLOCK_SIZE] = {0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39};
	InitUART0 ();
	UART0_dbg_msg (
	"********************************************************************************\n\r"
	" Internal CRC test of LPC1788\n\r"
	"\t - UART Comunication: 9600 bps\n\r"
	" Write to debug console data block CRC\n\r"
	" Data block (ASCII):\n\r ");
	UART0_dbg_msg (BlockData);
	UART0_dbg_msg ("\n\r********************************************************************************\n\r");
	
	if (CRC_Init(CRC_POLY_CRCCCITT))
		{
			UART0_dbg_msg ("CRC-CCITT Result: ");
			UART0_dbg_hex32 (CRC_CalcBlockChecksum(BlockData, BLOCK_SIZE, CRC_WR_8BIT));
		}
	else UART0_dbg_msg ("CRC_Init exceprion\n\r");

	if (CRC_Init(CRC_POLY_CRC16))
		{
			UART0_dbg_msg ("CRC-16 Result: ");
			UART0_dbg_hex32 (CRC_CalcBlockChecksum(BlockData, BLOCK_SIZE, CRC_WR_8BIT));			
		}
	else UART0_dbg_msg ("CRC_Init exceprion\n\r");
		
	if (CRC_Init(CRC_POLY_CRC32))
		{
			UART0_dbg_msg ("CRC-32 Result: ");
			UART0_dbg_hex32 (CRC_CalcBlockChecksum(BlockData, BLOCK_SIZE, CRC_WR_8BIT));			
		}
	else UART0_dbg_msg ("CRC_Init exceprion\n\r");
		
	while (1);
}
