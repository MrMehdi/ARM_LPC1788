#include "LPC177x_8x_uart.h"
#include "LPC177x_8x_eeprom.h"

#define PAGE_OFFSET		0x00
#define PAGE_ADDR			0x00

int main(void)
{	uint8_t read_buffer[] ="";
	char write_buffer[]="HELLO EEPROM!!!";
	
	InitUART0 ();
	UART0_dbg_msg (
	"********************************************************************************\n\r"
	" Internal EEPROM test of LPC1788\n\r"
	"\t - UART Comunication: 9600 bps\n\r"
	" Writing and reading data from internal EEPROM and show results in debug console\n\r"
	"********************************************************************************\n\r");
	EEPROM_Init();	
	UART0_dbg_msg ("Write buffer to EEPROM\n\r"); 
	while (!EEPROM_Write(PAGE_OFFSET,PAGE_ADDR,(void*)write_buffer,MODE_8_BIT,sizeof(write_buffer)))
		UART0_dbg_msg ("EEPROM_Write exception\n\r");
	//Program data	
	UART0_dbg_msg ("Read data from EEPROM, data buffer contain\n\r");
	while (!EEPROM_Read(PAGE_OFFSET,PAGE_ADDR,(void*)read_buffer,MODE_8_BIT,sizeof(write_buffer)))
		UART0_dbg_msg ("EEPROM_Read exception\n\r");
	//display eeprom data
	UART0_dbg_msg (read_buffer);
	UART0_dbg_msg ("\n\rend of demo\n\r");
	UART0_dbg_msg ("Erase page with buffer in EEPROM\n\r"); 
	EEPROM_Erase(PAGE_ADDR);
	while(1);
}
