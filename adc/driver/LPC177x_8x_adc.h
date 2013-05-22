/****************************************************************************
LPC177x_8x_adc.h basic definitions
****************************************************************************/

#define PCONP_PCADC 	12

#define ADCR_CLKDIV8	8
#define ADCR_CLKDIV9	9
#define ADCR_CLKDIV10	10
#define ADCR_PDN21		21
#define ADCR_START24	24

#define ADGDR_DONE31	31

unsigned char InitADC (char channel);
unsigned int GetADC(void);
void ADC_dbg (unsigned int val);
/*****************************************************************************
End Of File
******************************************************************************/
