#include "lpc177x_8x_systick.h"

//Init SysTick timer
void SYSTICK_Init(void)
{
	SysTick->RELOAD = 0x00124F7F;
	SysTick->CTRL=(1<<STCTRL_ENABLE0)|(1<<STCTRL_CLKSOURCE2);
}

//On/Off SysTick timer
void SYSTICK_Cmd(const TICK_STATE NewState)
{
	if (NewState == ON) SysTick->CTRL|=(1<<STCTRL_ENABLE0);
								else	SysTick->CTRL&=~(1<<STCTRL_ENABLE0);
}

//Return current value of SysTick timer
uint32_t SYSTICK_GetCurrentValue(void)
{
	return (SysTick->CURR);
}

//Clear CF
void SYSTICK_ClearCounterFlag(void)
{
	SysTick->CTRL &= ~(1<<STCTRL_COUNTFLAG16);
}

//delay in seconds
void delay_sec (const uint8_t second)
{
	uint16_t count;
	count = second*100;
	
	SYSTICK_Init();
	while (count>0)
	{
		while ((SysTick->CTRL&(1<<STCTRL_COUNTFLAG16))==0x00) ;
		count--;
	}
}
