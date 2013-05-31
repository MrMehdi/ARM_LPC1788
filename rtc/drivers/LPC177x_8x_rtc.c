#include "LPC177x_8x_uart.h"
#include "LPC177x_8x_rtc.h"

#include "string.h"
#include "ctype.h"
#include "stdlib.h"

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
}

//Set DOY correspondint to current date
uint16_t CalcRTCDOY (void)
{
	uint8_t i; 
	uint16_t days=0;
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
uint8_t CalcRTCDOW(void)
{
	uint16_t i,days=0;
	for (i=2007;i<LPC_RTC->YEAR;i++)
	 if ((i % 4) == 0) days+=366;
								else days+=365;
	return ((days+CalcRTCDOY()-1) % 7);
}

//convert x to string s, length of string - len
uint8_t itoan (const uint32_t x, const uint8_t len, char * s)
{ 
	uint32_t temp,val;
	uint8_t i,k,res;
	val=x;
	//if number of digits exceed limits - call exception
	if ((len<1)||(len>10) ) return 0;		
	for (i=len;i>0;i--)
	{
		temp=1;
		for (k=i;k>1;k--)
			temp*=10;
		//calculate digit
		res=val/temp;					
		val=val-res*temp;
		s[len-i]=('0'+res);
	}
	s[len]='\0';
	return 1;
}

//put n digits from string s to string op from *m position
uint8_t get_n_digits (const char *s, char* op, uint8_t *m, const uint8_t n)
{
	uint8_t l,k=0;
	uint8_t i, len;
	i= *m;
	l=n;
	len = strlen(s);
	while (isspace(s[i])&&(i<len)) i++;
	while (l>0)
	{
		if (isdigit(s[i]))
			{
				op[k]=s[i];
				k++;
			}
		else return 0;
		l--;
		i++;
	}
	op[k]='\0';
	*m=i;
	return 1;
}

//create timestamp string YYYY/MM/DD HH:MM:SS
char * RTC_timestamp (char * s)
{ 
	char temp[MAX_TIMESTAMP_LEN];
	s[0]='\0';
	itoan(LPC_RTC->YEAR,4,temp);
	strcat(s,temp);
	strcat(s,"/");
	itoan(LPC_RTC->MONTH,2,temp);
	strcat(s,temp);
	strcat(s,"/");
	itoan(LPC_RTC->DOM,2,temp);
	strcat(s,temp);
	strcat(s," ");
	itoan(LPC_RTC->HOUR,2,temp);
	strcat(s,temp);
	strcat(s,":");
	itoan(LPC_RTC->MIN,2,temp);
	strcat(s,temp);
	strcat(s,":");
	itoan(LPC_RTC->SEC,2,temp);
	strcat(s,temp);
	return s;
}

//set RTC from timestamp string string YYYY/MM/DD HH:MM:SS
uint8_t RTC_set_from_timestamp (const char* s)
{
	char temp[4];
	uint16_t var;
	uint8_t len,n=0;
	uint8_t days[12]={32,30,32,31,32,31,32,32,31,32,31,32};
	
	len = strlen(s);
	if (get_n_digits(s,temp,&n,4)) 
		{
			var=atoi(temp);
			if ((var>2012)&&(var<2100)) LPC_RTC->YEAR = var;
			else return 0;
		}
	while (isspace(s[n])&&(n<len)) 
		n++;
	if ((s[n] != '/')&&(s[n]!='\\')) return 0;
	n++;
		
	if (get_n_digits(s,temp,&n,2))
		{
			var = atoi(temp);
			if ((var>0)&&(var<13)) LPC_RTC->MONTH = var;
			else return 0;
		}
	while (isspace(s[n])&&(n<len)) 
		n++;
	if ((s[n] != '/')&&(s[n]!='\\')) return 0;
	n++;
	
	if (get_n_digits(s,temp,&n,2))
		{
			var = atoi(temp);
			if ((var>0)&&(var<days[LPC_RTC->MONTH-1])) 
			{
				if ((LPC_RTC->MONTH==2)&&(((LPC_RTC->YEAR % 4) !=0)&&(var==29))) return 0;
				else LPC_RTC->DOM = var;
			}
			else return 0;
		}
	while (isspace(s[n])&&(n<len)) 
		n++;
	
	if (get_n_digits(s,temp,&n,2))
		{
			var = atoi(temp);
			if (var<24) LPC_RTC->HOUR = var;
			else return 0;
		}
	while (isspace(s[n])&&(n<len)) 
		n++;
	if (s[n] != ':') return 0;
	n++;
	
	if (get_n_digits(s,temp,&n,2))
		{
			var = atoi(temp);
			if (var<60) LPC_RTC->MIN = var;
			else return 0;
		}
	while (isspace(s[n])&&(n<len)) 
		n++;
	if (s[n] != ':') return 0;
	n++;
	
	if (get_n_digits(s,temp,&n,2))
		{
			var = atoi(temp);
			if (var<60) LPC_RTC->SEC = var;
			else return 0;
		}
	while (n<len) 
		if (!isspace(s[n])) return 0;
		else n++;
	
	LPC_RTC->DOY = CalcRTCDOY();
	LPC_RTC->DOW = CalcRTCDOW();
	return 1;
}
