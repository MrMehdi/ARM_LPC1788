/****************************************************************************
LPC177x_8x_systick.h basic definitions
****************************************************************************/
#include "LPC177x_8x.h"

typedef enum
{
	ON = 0,				
	OF
} TICK_STATE;

#define STCTRL_ENABLE0				0
#define STCTRL_CLKSOURCE2			2
#define STCTRL_COUNTFLAG16		16

void			SYSTICK_Init(void);
void			SYSTICK_Cmd(const TICK_STATE NewState);
uint32_t	SYSTICK_GetCurrentValue(void);
void			SYSTICK_ClearCounterFlag(void);
void			delay_sec (const uint8_t second);
/*****************************************************************************
End Of File
******************************************************************************/
