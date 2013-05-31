#include "LPC177x_8x_ssp.h"
#include "LPC177x_8x_IOCON.h"

void SetSSP1BitMode (const uint8_t mode)
{
	LPC_SSP1->CR0 &= 0xfffffff0;
	LPC_SSP1->CR0 |= ((mode-1)&0x0f);
}

void SetSSP1ClockRate (const uint8_t SCR, const uint8_t CPSDVSR)
{
	LPC_SSP1->CR0 &= 0xffff00ff;
	LPC_SSP1->CR0 |= (SCR<<8);
	LPC_SSP1->CPSR = (CPSDVSR&0xfe);
}

void ClearSSP1RXFIFO (void)
{ uint8_t Dummy;
	//wait to finish transmit&receive
	while ( (LPC_SSP1->SR&(1<<SSP1_SRBUSY)) != 0x00 ) ;
	//Clear RX FIFO
	while ((LPC_SSP1->SR&(1<<SSP1_SRRNE))!= 0x00)
		Dummy = LPC_SSP1->DR;
}

void InitSSP1 (void)
{ 
	//power on SSP1;
	LPC_SC->PCONP |= (1<<PCONP_PCSSP1);
	//Initializa pins for SSP1
	LPC_IOCON->P4_20  |= 	(1<<PX_Y_IOCON_FUNC0)|(1<<PX_Y_IOCON_FUNC1);
	LPC_IOCON->P4_22  |= 	(1<<PX_Y_IOCON_FUNC0)|(1<<PX_Y_IOCON_FUNC1);
	LPC_IOCON->P4_23 	|= 	(1<<PX_Y_IOCON_FUNC0)|(1<<PX_Y_IOCON_FUNC1);
	LPC_IOCON->P4_21  |= 	0x00;
	LPC_GPIO4->SET |= (1<<GPIO4_SSEL1);
	LPC_GPIO4->DIR |= (1<<GPIO4_SSEL1);
	//Enable SSP1
	LPC_SSP1->CR1 = (1<<SSP1_CR1SSE1);
	//Set 8bit mode
	SetSSP1BitMode (8);
	//Set Clock rate 10MHz
	SetSSP1ClockRate (2,2);
	ClearSSP1RXFIFO();
}

void SSP1_SendByte (const uint8_t data) 
{
	while ( (LPC_SSP1->SR&(1<<SSP1_SRTNF)) == 0x00 ) ;
	LPC_SSP1->DR = data;
}

uint8_t SSP1_ReceiveByte (void)
{
	while ((LPC_SSP1->SR&(1<<SSP1_SRRNE))== 0x00) ;
	return ((uint8_t) (LPC_SSP1->DR));
}
