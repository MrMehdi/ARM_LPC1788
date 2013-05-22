#include "LPC177x_8x.h"
#include "LPC177x_8x_uart.h"
#include "sdram_k4s561632j.h"

int main(void)
{	
  volatile unsigned long int L, i, num_failed, num_success;
  volatile unsigned char * Pointer8;
  unsigned long csum, rcsum;
	volatile uint16_t *wr_ptr;
	
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
	UART0_dbg_msg ("Writing, 0x00000000 to 0x00B71B00 8-bit mode\n\r");
	Pointer8 = (unsigned char *)(SDRAM_BASE_ADDR + (480*272*4));
  csum=0;
  for(L=0;L<(12000000);L++)
  {
    *Pointer8 = (unsigned char)(L&0xff);
    csum += (L&0xff);
    Pointer8++;
  }
	UART0_dbg_msg ("Reading, 0x00000000 to 0x00B71B00 8-bit mode\n\r");
	Pointer8 = (unsigned char *)(SDRAM_BASE_ADDR + (480*272*4));
  rcsum=0;
  for(L=0;L<(12000000);L++)
  {
    i = *Pointer8;
    rcsum += (i&0xff);
    Pointer8++;
  } 
  if(csum != rcsum) {
											UART0_dbg_msg ("Write failed\n\r");
											num_failed++;
										}
							else	{
											UART0_dbg_msg ("Succssesfully writed\n\r");	
											num_success++;
										}
	UART0_dbg_msg ("csum ");
	UART0_dbg_hex32 (csum);
	UART0_dbg_msg ("rcsum ");
	UART0_dbg_hex32 (rcsum);
	
	UART0_dbg_msg ("Writing, 0x00000000 to 0x005B8D80 16-bit mode\n\r");
  wr_ptr = (uint16_t *)SDRAM_BASE_ADDR;									
  for (L=0; L<(6000000); L++)
  {
		*wr_ptr = (uint16_t )(L&0x0000ffff);
		csum += (L&0x0000ffff);
		wr_ptr++;
  }
	UART0_dbg_msg ("Reading, 0x00000000 to 0x005B8D80 16-bit mode\n\r");
	wr_ptr = (uint16_t *)SDRAM_BASE_ADDR;
	for (L=0; L<(6000000); L++)
	{
		i = *wr_ptr;
		rcsum += (i&0x0000ffff);
		wr_ptr++;
  }
  if(csum != rcsum) {
										UART0_dbg_msg ("Write failed\r\n");
										num_failed++;
										}
							else	{
										UART0_dbg_msg ("Succssesfully writed\r\n");
										num_success++;
										}
	UART0_dbg_msg ("csum - ");
	UART0_dbg_hex32 (csum);
	UART0_dbg_msg ("rcsum - ");
	UART0_dbg_hex32 (rcsum);
	UART0_dbg_msg ("num_failed - ");
	UART0_dbg_hex32 (num_failed);
	UART0_dbg_msg ("num_success - ");
	UART0_dbg_hex32 (num_success);
}
}
