/****************************************************************************
LPC177x_8x_rtc.h basic definitions
****************************************************************************/
#define PCONP_PCRTC9 	9

#define CCR_CLKEN0		0

void InitRTC (void);
unsigned int SetRTCDOY (void);
unsigned int SetRTCDOW(void);
void RTC_dbg (void);
unsigned char SetRTC (void);

/*****************************************************************************
End Of File
******************************************************************************/
