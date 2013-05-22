#include "LPC177x_8x_uart.h"
#include "LPC177x_8x_timer.h"

int main(void)
{ uint8_t count=0;
	InitUART0 ();
	UART0_dbg_msg (
	"********************************************************************************\n\r"
	" Internal Timer0 timer test on LPC1788\n\r"
	"\t - UART Comunication: 9600 bps\n\r"
	" Generate 1s delay between counting in to debug console\n\r"
	"********************************************************************************\n\r"); 
	while (1)
	{
		delay_ms (1000);
		count++;
		UART0_dbg_hex32(count);
	}
}
