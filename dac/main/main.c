#include "LPC177x_8x.h"
#include "LPC177x_8x_uart.h"
#include "LPC177x_8x_rtc.h"
#include "LPC177x_8x_adc.h"
#include "LPC177x_8x_dac.h"

int main(void)
{
	uint8_t count, second=0;
	uint32_t val;
	InitUART0 ();
	InitRTC();	
	UART0_dbg_msg (
	"********************************************************************************\n\r"
	" Internal DAC test of LPC1788\n\r"
	"\t - UART Comunication: 9600 bps \n\r"
	" Write to debug console current voltage on AD[2]-AD[3]\n\r"
	"********************************************************************************\n\r");
	if (!InitADC (2))
		{
			UART0_dbg_msg ("InitADC exception, channel must be 0..7\n\r");
			while (1);
		}
	InitDAC (0x03FF);
	while (1) 
	{
		//input DAC value
		do
		{
		UART0_dbg_msg ("Input DAC value in range 0..1023, as a sample 0983\n\r");
		while (!UART0_get_dec (&val,4)) 
			UART0_dbg_msg ("DAC value is 10-bit number\n\r");
		if (val>1024) {
										UART0_dbg_msg ("DAC value isn't in range 0..1023\n\r");
										UART0_clear_rx_buffer();
									}
		} while (val>1024);
		count=0;
		//Set DAC value
		SetDAC(val);
		//Convert DAC value through ADC 5 times
		while(count<5)
		{	
		if (second != LPC_RTC->SEC)
			{
			second=LPC_RTC->SEC;
			ADC_dbg(GetADC());
			count++;
			}
		}
	}
}
