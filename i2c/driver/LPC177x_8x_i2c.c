#include "LPC177x_8x_IOCON.h"
#include "LPC177x_8x_i2c.h"

void InitI2C0 (void)
{
	//Power on I2C0
	LPC_SC->PCONP |= (1<<PCI2C0);
	//Configure PINs
	LPC_IOCON->P0_27 = (1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P0_28 = (1<<PX_Y_IOCON_FUNC0);
	//Set I2C0 Clock Rate - 100kHz std mode
	LPC_I2C0->SCLL = 300;
	LPC_I2C0->SCLH = 300;
	//Enable I2C0, assert ACK
	LPC_I2C0->CONSET = (1<<CON_I2EN);
}

void StartI2C0 (void)
{
	//Clear SI
	LPC_I2C0->CONCLR = (1<<CON_SI);
	//Set START condition
	LPC_I2C0->CONSET = (1<<CON_STA);
	//Wait for complete
	while ( (LPC_I2C0->CONSET&(1<<CON_SI)) == 0x00) ;
	//Clear START condition
	LPC_I2C0->CONCLR = (1<<CON_STA);
}

void StopI2C0 (void)
{
	//Make sure start bit is not active 
	if ((LPC_I2C0->CONSET&(1<<CON_STA)) != 0x00) LPC_I2C0->CONCLR=CON_STA;
	//Clear SI
	LPC_I2C0->CONCLR = (1<<CON_SI);
	//Set STOP condition
	LPC_I2C0->CONSET = (1<<CON_STO);
}

void SendByteI2C0 (const uint8_t data)
{
	//Make sure start bit is not active 
	if ((LPC_I2C0->CONSET&(1<<CON_STA)) != 0x00) LPC_I2C0->CONCLR = (1<<CON_STA);
	//Send data
	LPC_I2C0->DAT = data&0xff;
	//Clear SI
	LPC_I2C0->CONCLR = (1<<CON_SI);
	//Wait
	while ((LPC_I2C0->CONSET & (1<<CON_SI)) == 0x00) ;
}

uint8_t ReceiveByteI2C0_w_ACK (void)
{
	//Clear SI and set AA
	LPC_I2C0->CONCLR = (1<<CON_SI);
	LPC_I2C0->CONSET = (1<<CON_AA);
	//Wait
	while ((LPC_I2C0->CONSET & (1<<CON_SI)) == 0x00) ;
	//Read byte
	return (uint8_t) (LPC_I2C0->DAT & 0xff);
}

uint8_t ReceiveByteI2C0_wo_ACK (void)
{
	//Clear SI & AA
	LPC_I2C0->CONCLR = (1<<CON_SI)|(1<<CON_AA);
	//Wait
	while ((LPC_I2C0->CONSET & (1<<CON_SI)) == 0x00) ;
	//Read byte
	return (uint8_t) (LPC_I2C0->DAT & 0xff);
}
