#include "LPC177x_8x.h"
#include "LPC177x_8x_uart.h"
#include "LPC177x_8x_rtc.h"

//Init internal RTC
void InitRTC (void)
{ 
	//Ensure thar RTC is power on
	LPC_SC->PCONP |= (1<<PCONP_PCRTC9);
	//Enable clock on RTC
	LPC_RTC->CCR = (1<<CCR_CLKEN0);
	//Init date/time registers
	LPC_RTC->YEAR = 2013;
	LPC_RTC->MONTH = 01;
	LPC_RTC->DOM = 01;
	LPC_RTC->DOW = 0;
	LPC_RTC->DOY = 001;
	LPC_RTC->HOUR = 00;
	LPC_RTC->MIN = 00;
	LPC_RTC->SEC = 00;
  return; 
}

//Set DOY correspondint to current date
unsigned int SetRTCDOY (void)
{
	unsigned int i, days=0;
	for (i=1;i<LPC_RTC->MONTH;i++)
	{
		if (i==1) days+=31;
		else if ((i==2)&&((LPC_RTC->YEAR % 4) == 0)) days+=29;
		else if ((i==2)&&((LPC_RTC->YEAR % 4) != 0)) days+=28;
		else if (i==3) days+=31;
		else if (i==4) days+=30;
		else if (i==5) days+=31;
		else if (i==6) days+=30;
		else if (i==7) days+=31;
		else if (i==8) days+=31;
		else if (i==9) days+=30;
		else if (i==10) days+=31;
		else if (i==11) days+=30;
	}
	return (days+LPC_RTC->DOM);
}

//Set DOW correspondint to current date
unsigned int SetRTCDOW(void)
{
	unsigned int i,days=0;
	for (i=2007;i<LPC_RTC->YEAR;i++)
	 if ((i % 4) == 0) days+=366;
								else days+=365;
	return ((days+SetRTCDOY()-1) % 7);
}

//Output current time/date to UART0
void RTC_dbg (void)
{
		UART0_dbg_dec (LPC_RTC->HOUR,2);
		UART0SendChar(':');
		UART0_dbg_dec (LPC_RTC->MIN,2);
		UART0SendChar(':');
		UART0_dbg_dec (LPC_RTC->SEC,2);
		UART0SendChar(' ');
		
		UART0_dbg_dec (LPC_RTC->YEAR,4);
		UART0SendChar('/');
		UART0_dbg_dec (LPC_RTC->MONTH,2);
		UART0SendChar('/');
		UART0_dbg_dec (LPC_RTC->DOM,2);
		UART0SendChar(' ');
									
		switch(LPC_RTC->DOW) 
		{
    case 0 : 	{ UART0_dbg_msg ("Mon ");	break; }
    case 1 : 	{	UART0_dbg_msg ("Tue ");	break; }
    case 2 : 	{	UART0_dbg_msg ("Wed ");	break; }
    case 3 : 	{	UART0_dbg_msg ("Thu ");	break; }
    case 4 : 	{	UART0_dbg_msg ("Fri ");	break; }
    case 5 : 	{	UART0_dbg_msg ("Sat ");	break; }
    case 6 : 	{	UART0_dbg_msg ("Sun ");	break; }
		}
		UART0_dbg_dec (LPC_RTC->DOY,3);
		UART0_dbg_msg (" day of year\n\r");
}

//Set current date from UART0 string HH:MM:SS YYYY/MM/DD
unsigned char SetRTC (void)
{ unsigned long int val;
	//hours
	if (UART0_get_dec (&val,2)) return 1; 
	if ( val<24 ) LPC_RTC->HOUR = val;
	else return 1;	
	if (UART0GetChar()!= ':') return 1;
	//minutes
	if (UART0_get_dec (&val,2)) return 1; 
	if ( val<60 ) LPC_RTC->MIN = val;
	else return 1;
	if (UART0GetChar()!= ':') return 1;
	//seconds
	if (UART0_get_dec (&val,2)) return 1; 
	if ( val<60 ) LPC_RTC->SEC = val;
	else return 1;
	if (UART0GetChar()!= ' ') return 1;
	//year
	if (UART0_get_dec (&val,4)) return 1; 
	if ((val>2006)&&(val<2100)) LPC_RTC->YEAR = val;
	else return 1;
	if (UART0GetChar()!= '/') return 1;
	//month
	if (UART0_get_dec (&val,2)) return 1; 
	if ((val>0)&&(val<13)) LPC_RTC->MONTH = val;
	else return 1;
	if (UART0GetChar()!= '/') return 1;
	//DOM
	if (UART0_get_dec (&val,2)) return 1;  
	if (((val>0)&&(val<32))&&((LPC_RTC->MONTH==1)||(LPC_RTC->MONTH==3)||(LPC_RTC->MONTH==5)||(LPC_RTC->MONTH==7)||(LPC_RTC->MONTH==8)||(LPC_RTC->MONTH==10)||(LPC_RTC->MONTH==12))) LPC_RTC->DOM = val;
	else if (((val>0)&&(val<31))&&((LPC_RTC->MONTH==4)||(LPC_RTC->MONTH==5)||(LPC_RTC->MONTH==9)||(LPC_RTC->MONTH==11))) LPC_RTC->DOM = val;
	else if ((val>0)&&(val<29)&&(LPC_RTC->MONTH==2)&&((LPC_RTC->YEAR % 4) !=0)) LPC_RTC->DOM = val;
	else if ((val>0)&&(val<30)&&(LPC_RTC->MONTH==2)&&((LPC_RTC->YEAR % 4) ==0)) LPC_RTC->DOM = val;
	else return 1;
	//DOW,DOY
	LPC_RTC->DOW =	SetRTCDOW();	
	LPC_RTC->DOY =	SetRTCDOY(); 
	return 0;
}
