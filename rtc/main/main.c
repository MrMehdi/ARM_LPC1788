#include "LPC177x_8x.h"
#include "LPC177x_8x_uart.h"
#include "LPC177x_8x_rtc.h"

int main(void)
{
	char s[MAX_TIMESTAMP_LEN]="";
	char s2[100]="";
	int second=0;
	
	InitUART0 ();
	InitRTC (); 
	UART0_dbg_msg (
	"********************************************************************************\n\r"
	" Internal RTC test of LPC1788\n\r"
	"\t - UART Comunication: 9600 bps \n\r"
	" Write to debug console current date and time\n\r"
	"********************************************************************************\n\r"); 
	
	UART0_dbg_msg ("Input date/time is following format YYYY/MM/DD HH:MM:SS:\n\r");
	UART0_get_line (s2,100);
	if (!RTC_set_from_timestamp(s2) ) UART0_dbg_msg ("Error, uncorrect timestamp\n\r");
	
	while (1)
		if (second != LPC_RTC->SEC)
		{
			second=LPC_RTC->SEC;
			
			UART0_dbg_msg (RTC_timestamp(s));
			UART0_dbg_msg ("\n\r");
		}
}
