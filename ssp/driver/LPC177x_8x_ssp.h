/****************************************************************************
LPC177x_8x_ssp.h basic definitions
****************************************************************************/
#include "LPC177x_8x.h"

#define PCONP_PCSSP1	10

#define SSP1_CR1SSE1			1

#define GPIO4_SSEL1		21

#define	SSP1_SRTNF			1
#define	SSP1_SRRNE			2
#define SSP1_SRBUSY		 	4

void SetSSP1BitMode (const uint8_t mode);
void SetSSP1ClockRate (const uint8_t SCR, const uint8_t CPSDVSR);
void ClearSSP1RXFIFO (void);
void InitSSP1 (void);
void SSP1_SendByte (const uint8_t data);
uint8_t SSP1_ReceiveByte (void);

/*****************************************************************************
End Of File
******************************************************************************/
