#include "lpc177x_8x_timer.h"

//Init Timer0 with prescaller and match0 values
void TIMER0_Init(uint32_t prescaler, uint32_t match0)
{
	//Enbale Timer0
	LPC_SC->PCONP|=(1<<PCONP_PCTIM0);
	LPC_TIM0->PR = prescaler;
	//Enable timer reset and interrupt flag when timer match MR0
	LPC_TIM0->MCR = (1<<MCR0_MR0I0)|(1<<MCR0_MR0R1);
	LPC_TIM0->MR0 = match0;
	//Start counting Timer
	LPC_TIM0->TCR = (1<<TCR0_CEN0);
}

//Delay in microseconds
void delay_us (uint16_t usecond)
{ 
	TIMER0_Init(1,29);
	while (usecond>0)
	{
		while ((LPC_TIM0->IR&(1<<IR0_MR0INT0))==0x00) ;
		LPC_TIM0->IR|=1<<IR0_MR0INT0;
		usecond--;
	}
}

//Delay in miliseconds
void delay_ms (uint16_t msecond)
{
	TIMER0_Init(1,29999);
	while (msecond>0)
	{
		while ((LPC_TIM0->IR&(1<<IR0_MR0INT0))==0x00) ;
		LPC_TIM0->IR|=1<<IR0_MR0INT0;
		msecond--;
	}
}

//Delay in seconds
void delay_sec (uint16_t second)
{
	TIMER0_Init(1,29999999);
	while (second>0)
	{
		while ((LPC_TIM0->IR&(1<<IR0_MR0INT0))==0x00) ;
		LPC_TIM0->IR|=1<<IR0_MR0INT0;
		second--;
	}
}
