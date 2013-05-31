#include "LPC177x_8x.h"
#include "LPC177x_8x_uart.h"
#include "LPC177x_8x_rtc.h"
#include "LPC177x_8x_adc.h"

int main(void)
{	uint8_t second=0;
	InitUART0 ();
	InitRTC();	
	UART0_dbg_msg (
	"********************************************************************************\n\r"
	" Internal ADC test of LPC1788\n\r"
	"\t - UART Comunication: 9600 bps \n\r"
	" Write to debug console current voltage on AD[2]\n\r"
	"********************************************************************************\n\r");
	if(!InitADC (3))
		{
			UART0_dbg_msg ("InitADC exception, channel must be 0..7\n\r");
			while (1);
		}
	while(1)
	{	
	if (second != LPC_RTC->SEC)
		{
		second=LPC_RTC->SEC;
		ADC_dbg(GetADC());
		}
	}
}
