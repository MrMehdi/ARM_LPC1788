/****************************************************************************
LPC177x_8x_pwm.h basic definitions
****************************************************************************/
#include "LPC177x_8x.h"

#define PCONP_PWM0 5

#define PWM0_TCR_CE0 		0	
#define PWM0_TCR_CR1		1
#define PWM0_TCR_PWMEN3 3

#define PWM0_MCR_PWMMR0R	1

#define PWM0_MAT0LATCHEN	0
#define PWM0_MAT1LATCHEN	1

#define PWM0_PWMENA1			9

void InitPWM0	(const uint32_t MR0, const uint32_t PR, const uint32_t MR1);
void SetPWM0	(const uint32_t MR0, const uint32_t PR, const uint32_t MR1);
/*****************************************************************************
End Of File
******************************************************************************/
