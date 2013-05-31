#include "LPC177x_8x_IOCON.h"
#include "LPC177x_8x_uart.h"
#include "LPC177x_8x_dac.h"

void InitDAC (const uint16_t val)
{  
	LPC_IOCON->P0_26 = (1<<PX_Y_IOCON_FUNC1)|(1<<PX_Y_IOCON_DACEN16);
	LPC_DAC->CR = (1<<DACR_BIAS16)|((val&0x03ff)<<6);
}

void SetDAC (const uint16_t val)
{  
	LPC_DAC->CR = (1<<DACR_BIAS16)|((val&0x03ff)<<6);
}
