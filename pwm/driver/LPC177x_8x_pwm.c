#include "LPC177x_8x_IOCON.h"
#include "LPC177x_8x_pwm.h"

//Init PWM0.1 cycle,prescaller, match
void InitPWM0 (const uint32_t MR0, const uint32_t PR, const uint32_t MR1)
{  
	LPC_SC->PCONP |= (1<<PCONP_PWM0);
	LPC_IOCON->P3_16 = (1<<PX_Y_IOCON_FUNC1)|(1<<PX_Y_IOCON_HYS5);
	LPC_PWM0->MR0 = MR0;
	LPC_PWM0->MR1 = MR1;
	LPC_PWM0->PR = PR;
	LPC_PWM0->LER |= (1<<PWM0_MAT0LATCHEN)|(1<<PWM0_MAT1LATCHEN);
	LPC_PWM0->PCR |= (1<<PWM0_PWMENA1);
	LPC_PWM0->MCR |= (1<<PWM0_MCR_PWMMR0R);
	LPC_PWM0->TCR |= (1<<PWM0_TCR_CE0)|(1<<PWM0_TCR_PWMEN3);
}

//Set PWM0.1 cycle,prescaller, match
void SetPWM0 (const uint32_t MR0, const uint32_t PR, const uint32_t MR1)
{
	LPC_PWM0->MR0 = MR0;
	LPC_PWM0->MR1 = MR1;
	LPC_PWM0->PR = PR;
	LPC_PWM0->LER |= (1<<PWM0_MAT0LATCHEN)|(1<<PWM0_MAT1LATCHEN);
	LPC_PWM0->TCR |= (1<<PWM0_TCR_CR1);
	LPC_PWM0->TCR &= ~(1<<PWM0_TCR_CR1);
}
