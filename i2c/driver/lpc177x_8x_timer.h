/****************************************************************************
LPC177x_8x_systick.h basic definitions
****************************************************************************/
#include "LPC177x_8x.h"

#define PCONP_PCTIM0	1

#define TCR0_CEN0		0

#define MCR0_MR0I0	0
#define MCR0_MR0R1	1

#define IR0_MR0INT0	0

void TIMER0_Init(uint32_t prescaler, uint32_t match0);
void delay_us (uint16_t usecond);
void delay_ms (uint16_t msecond);
void delay_sec (uint16_t second);
/*****************************************************************************
End Of File
******************************************************************************/
