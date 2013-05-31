/****************************************************************************
LPC177x_8x_adc.h basic definitions
****************************************************************************/
#include "LPC177x_8x.h"

#define PCONP_PCADC 	12

#define ADCR_CLKDIV8	8
#define ADCR_CLKDIV9	9
#define ADCR_CLKDIV10	10
#define ADCR_PDN21		21
#define ADCR_START24	24

#define ADGDR_DONE31	31

uint8_t		InitADC	(const uint8_t channel);
uint16_t	GetADC	(void);
void			ADC_dbg	(const uint16_t val);
/*****************************************************************************
End Of File
******************************************************************************/
