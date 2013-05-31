#include "LPC177x_8x.h"
#include "LPC177x_8x_uart.h"

int main(void)
{	
uint32_t val;
char s[100];

InitUART0();
	
UART0_dbg_msg (
"********************************************************************************\n\r"
" Internal UART0 test on LPC1788\n\r"
"\t - UART Comunication: 9600 bps\n\r"
"********************************************************************************\n\r"); 

UART0_dbg_hex32 (0x12345678);
UART0_dbg_dec (1234,5);

UART0_dbg_msg ("Input 4 digit dec\n\r");
if (UART0_get_dec (&val,4)) 
	{
		UART0_dbg_msg ("Captured dec\n\r");
		UART0_dbg_dec (val,5);
	}
else UART0_dbg_msg ("Error\n\r");
	
UART0_dbg_msg ("Input string, max 100 symbols\n\r");
UART0_get_line (s,100);
UART0_dbg_msg ("String:\n\r");
UART0_dbg_msg (s);
	
while (1)
	;
}
