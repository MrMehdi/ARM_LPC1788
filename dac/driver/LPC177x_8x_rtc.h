/****************************************************************************
LPC177x_8x_rtc.h basic definitions
****************************************************************************/
#include "LPC177x_8x.h"

#define PCONP_PCRTC9 	9

#define CCR_CLKEN0		0

#define MAX_TIMESTAMP_LEN	20

void			InitRTC (void);
uint16_t	CalcRTCDOY (void);
uint16_t	CalcRTCDOY (void);
uint8_t		CalcRTCDOW(void);
uint8_t		itoan (const uint32_t x, const uint8_t len, char * s);
uint8_t		get_n_digits (const char *s, char* op, uint8_t *m, const uint8_t n);
char *		RTC_timestamp (char * s);
uint8_t		RTC_set_from_timestamp (const char* s);

/*****************************************************************************
End Of File
******************************************************************************/
