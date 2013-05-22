#include "LPC177x_8x.h"
#include "LPC177x_8x_uart.h"
#include "LPC177x_8x_rtc.h"

int main(void)
{	int second=0;
	
	InitUART0 ();
	InitRTC ();
	UART0_dbg_msg (
	"********************************************************************************\n\r"
	" Internal RTC test of LPC1788\n\r"
	"\t - UART Comunication: 9600 bps \n\r"
	" Write to debug console current date and time\n\r"
	"********************************************************************************\n\r");
	RTC_dbg ();
	UART0_dbg_msg ("Input date/time string in following format HH:MM:SS YYYY/MM/DD\n\r");
	while (SetRTC())
	{
		UART0_dbg_msg ("Incorrect statement or date/time, try again.\n\r");
		UART0_clear_rx_buffer();
	}
while(1)
{	
	if (second != LPC_RTC->SEC)
	{
		second=LPC_RTC->SEC;
		RTC_dbg ();
	}
}
		
}
