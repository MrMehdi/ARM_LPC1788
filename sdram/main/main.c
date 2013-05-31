#include "LPC177x_8x.h"
#include "LPC177x_8x_uart.h"
#include "sdram_k4s561632j.h"

int main(void)
{	
  uint32_t num_failed, num_success;
	InitUART0 ();
	UART0_dbg_msg (
	"********************************************************************************\n\r"
	" Test SDRAM K4S561632J with LPC1788 EMC \n\r"
	"\t - UART Comunication: 9600 bps \n\r"
	" Write and verify data with on-board SDRAM 8bit and 16bit mode\n\r"
	"********************************************************************************\n\r");
	SDRAMInit();
	num_failed=0;
	num_success=0;
while (1) 
{		
	UART0_dbg_msg ("Testing SDRAM, 0x00000000 to 0x02000000 8-bit mode\n\r");
  if(SDRAM8BitTest())	{
												UART0_dbg_msg ("Success\n\r");	
												num_success++;
											}
							else		{

												UART0_dbg_msg ("Failed\n\r");
												num_failed++;								
											}
	UART0_dbg_msg ("Testing SDRAM, 0x00000000 to 0x02000000 16-bit mode\n\r");
  if(SDRAM16BitTest()) {
													UART0_dbg_msg ("Success\n\r");
													num_success++;
												}
							else			{
													UART0_dbg_msg ("Failed\n\r");
													num_failed++;
												}
	UART0_dbg_msg ("num_failed - ");
	UART0_dbg_hex32 (num_failed);
	UART0_dbg_msg ("num_success - ");
	UART0_dbg_hex32 (num_success);
}
}
