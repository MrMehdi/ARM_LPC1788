#include "LPC177x_8x_uart.h"
#include "LPC177x_8x_ssp.h"
#include "AT45DB021.h"

int main(void)
{	uint8_t i;
	uint8_t temp[10] = {1,2,3,4,5,6,7,8,9,10};
	InitUART0 (); 
	UART0_dbg_msg (
	"********************************************************************************\n\r"
	" Internal SPI test on LPC1788\n\r"
	"\t - UART Comunication: 9600 bps\n\r"
	"\t - Write and read 10 bytes to AT45DB021\n\r"
	"********************************************************************************\n\r");	
	InitSSP1();	
	UART0_dbg_msg ("Writing 10 bytes {1,2,3,4,5,6,7,8,9,10} from 260 absolute address to AT45DB021\n\r");
  if (AT45DB021_WriteBlock(temp,260,10) == 0x01 ) UART0_dbg_msg ("Write successfull\n\r");
																					else 	{
																									UART0_dbg_msg ("Write failed\n\r");
																									while (1) ;
																								}
	UART0_dbg_msg ("Reading 10 bytes from 260 absolute address from AT45DB021\n\r");
  if (AT45DB021_ReadBlock(temp,260,10) == 0x01 ) 	{
																										UART0_dbg_msg ("Read successfull, data:\n\r");	
																											for (i=0;i<10;i++)
																												UART0_dbg_hex32(temp[i]);
																									}
																						else 	{
																										UART0_dbg_msg ("Read failed\n\r");
																										while (1) ;
																									}
																									
	UART0_dbg_msg ("Erasing 10 bytes from 260 absolute address from AT45DB021\n\r");
  if (AT45DB021_EraseBlock(260,10) == 0x01 ) 		UART0_dbg_msg ("Erase successfull\n\r");																					
																				else 	{
																								UART0_dbg_msg ("Erase failed\n\r");
																								while (1) ;
																							}																																														
	UART0_dbg_msg ("Reading 10 bytes from 260 absolute address from AT45DB021\n\r");
  if (AT45DB021_ReadBlock(temp,260,10) == 0x01 ) 	{
																										UART0_dbg_msg ("Read successfull, data:\n\r");	
																											for (i=0;i<10;i++)
																												UART0_dbg_hex32(temp[i]);
																									}
																						else 	{
																										UART0_dbg_msg ("Read failed\n\r");
																										while (1) ;
																									}																		
	while (1) ;
}
