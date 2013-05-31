#include "ctype.h"
#include "LPC177x_8x_IOCON.h"
#include "LPC177x_8x_uart.h"

#define MAX_UNGETCH_BUF 10

volatile static char buf[MAX_UNGETCH_BUF];
volatile static uint8_t bufc=0;

void InitUART0 (void)
{  
	//init IO ports as UART0
	LPC_IOCON->P0_2  = 	(1<<PX_Y_IOCON_FUNC0)|(1<<PX_Y_IOCON_MODE4)|(1<<PX_Y_IOCON_HYS5);
	LPC_IOCON->P0_3	 = 	(1<<PX_Y_IOCON_FUNC0)|(1<<PX_Y_IOCON_MODE4)|(1<<PX_Y_IOCON_HYS5);
	//init UART0
	LPC_UART0->LCR = (1<<LCR_WLS0)|(1<<LCR_WLS1)|(1<<LCR_DLAB); 								/* 8 bits, no Parity, 1 Stop bit */
	LPC_UART0->DLM = 0x01;				// baudrate divider high register 9600bps, cpu clock 120MHz
	LPC_UART0->DLL = 0x8b;				// baudrate divider low register	9600bps, cpu clock 120MHz
	LPC_UART0->FDR = 0x80;				// fractional baudrate divider ==(1+0)
	LPC_UART0->LCR = (1<<LCR_WLS0)|(1<<LCR_WLS1);																/* DLAB = 0 */
	LPC_UART0->FCR = (1<<FCR_FIFOEN)|(1<<FCR_RXFIFORES)|(1<<FCR_TXFIFORES);		/* Enable and clear TX and RX FIFO. */
}

void UART0_clear_rx_buffer(void)
{
		LPC_UART0->FCR |= (1<<FCR_RXFIFORES);
}

void UART0SendChar (const char x)
{
	while (!(LPC_UART0->LSR&(1<<LSR_THRE))) ;
	LPC_UART0->THR = x;
}

char UART0GetChar (void)
{ 
	if (bufc!=0) 
		{
			bufc--;
			return buf[bufc];
		}
	else 
		{
			while (!(LPC_UART0->LSR&(1<<LSR_RDR))) ;
			return (LPC_UART0->RBR&0x000000ff);
		}
}

void UART0UnGetChar(const char val)
{
	buf[bufc]=val;
	bufc++;
}

//send string message via UART0
void UART0_dbg_msg (const void *str)
{
	char *s = (char *) str;
	while (*s)
		UART0SendChar (*s++);	
} 

//send hex number via UART0 in 0xHHHHHHHH format
void UART0_dbg_hex32 (const uint32_t x)
{ uint8_t i;
	uint32_t temp;

	UART0SendChar('0');
	UART0SendChar('x');
	for (i=0;i<8;i++)
		{			
			temp = x>>((8-i-1)*4);
			temp=temp&0x0000000f;
			if (temp<0x0a) UART0SendChar(0x30+temp);		//if number 0..9
								else UART0SendChar(0x37+temp);		//if letter A..F
		}
	UART0SendChar('\n');
	UART0SendChar('\r');
}

//send dec number via UART0 in D..D format, num - number digits in x
uint8_t UART0_dbg_dec (const uint32_t x, const uint8_t num)
{ 
	uint32_t var,temp,res;
	uint8_t i,k;
	var=x;
	//if number of digits exceed limits - call exception
	if ((num<1)||(num>10) ) return 0;		
	for (i=num;i>0;i--)
	{
		temp=1;
		for (k=i;k>1;k--)
			temp*=10;
		//calculate digit
		res=var/temp;					
		var=var-res*temp;
		UART0SendChar('0'+res);
	}
	UART0SendChar('\n');
	UART0SendChar('\r');
	return 1;
}

//get dec number via UART0 in D..D format, num - number digits in res
uint8_t UART0_get_dec (uint32_t *res, const uint8_t num)
{ uint8_t val,i;
	*res=0;
	
	while ( isspace(val=UART0GetChar())) ;
	 UART0UnGetChar(val);
	for (i=0;i<num;i++)
		{
			val=UART0GetChar();
			//if invalid digit - call exception	
			if ((val<'0')||(val>'9')) return 0;			
			else *res=*res*10+(val-0x30);				
		}
	return 1;
}

//get line from UART0
void UART0_get_line (char *s, const uint8_t len)
{ 
	uint8_t i=0;
	char c;
	while ( ((c=UART0GetChar()) != '\n') && (c!= '\r')&&(i<len) )
	{
		s[i]=c;
		i++;
	}
	s[i]='\0';
}
