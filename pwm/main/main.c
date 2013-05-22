#include "LPC177x_8x_uart.h"
#include "LPC177x_8x_timer.h"
#include "LPC177x_8x_pwm.h"

int main(void)
{	uint8_t count=0;
	InitUART0 ();
	UART0_dbg_msg (
	"********************************************************************************\n\r"
	" Internal PWM0 test on LPC1788\n\r"
	"\t - UART Comunication: 9600 bps\n\r"
	"\t change PWM pulse width on P3_16\n\r"
	"********************************************************************************\n\r"); 
	InitPWM0(0xff,0x00,0x00);
	while (1)
	{
		SetPWM0 (0xff,0x00,count++);
		count++;
		delay_ms(10);
	} 
}
