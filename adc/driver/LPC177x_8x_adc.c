#include "LPC177x_8x.h"
#include "LPC177x_8x_IOCON.h"
#include "LPC177x_8x_uart.h"
#include "LPC177x_8x_adc.h"

unsigned char InitADC (char channel)
{  
	//Power up ADC through PCONP
	LPC_SC->PCONP |=(1<<PCONP_PCADC);
	//Set IOCON properly
	switch (channel)
	{
		case 0 : {LPC_IOCON->P0_23 = (1<<PX_Y_IOCON_FUNC0); break;};
		case 1 : {LPC_IOCON->P0_24 = (1<<PX_Y_IOCON_FUNC0); break;};
		case 2 : {LPC_IOCON->P0_25 = (1<<PX_Y_IOCON_FUNC0); break;};
		case 3 : {LPC_IOCON->P0_26 = (1<<PX_Y_IOCON_FUNC0); break;};
		case 4 : {LPC_IOCON->P1_30 = (1<<PX_Y_IOCON_FUNC0)|(1<<PX_Y_IOCON_FUNC1); break;};
		case 5 : {LPC_IOCON->P1_31 = (1<<PX_Y_IOCON_FUNC0)|(1<<PX_Y_IOCON_FUNC1); break;};	
		case 6 : {LPC_IOCON->P0_12 = (1<<PX_Y_IOCON_FUNC0)|(1<<PX_Y_IOCON_FUNC1); break;};
		case 7 : {LPC_IOCON->P0_13 = (1<<PX_Y_IOCON_FUNC0)|(1<<PX_Y_IOCON_FUNC1); break;};	
		default : return 1;
	}
	//Setup channel,clock and power up mode to ADC
	LPC_ADC->CR = (1<<channel)|(1<<ADCR_CLKDIV8)|(1<<ADCR_CLKDIV10)|(1<<ADCR_PDN21);
	return 0;
}

unsigned int GetADC(void)
{ unsigned long int val;
	//start conversion
	LPC_ADC->CR |= (1<<ADCR_START24);
	do 
	{
		val = LPC_ADC->GDR;
	} while ((val&(1<<ADGDR_DONE31))==0x00);		//wait to finish conversion
 return ((val>>4)&0x00000fff);		//trim result
}

void ADC_dbg (unsigned int val)
{ unsigned long int res;
	res=3300*val/4096;
	UART0_dbg_dec (res,4);
	UART0_dbg_msg (" mV on ADC\n\r");
}

