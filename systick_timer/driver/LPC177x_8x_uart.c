#include "LPC177x_8x.h"
#include "LPC177x_8x_IOCON.h"
#include "LPC177x_8x_uart.h"

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
  return; 
}

void UART0_clear_rx_buffer(void)
{
		LPC_UART0->FCR |= (1<<FCR_RXFIFORES);
}

void UART0SendChar (char x)
{
	while (!(LPC_UART0->LSR&(1<<LSR_THRE))) ;
	LPC_UART0->THR = x;
}

char UART0GetChar (void)
{ 
	while (!(LPC_UART0->LSR&(1<<LSR_RDR))) ;
	return (LPC_UART0->RBR&0x000000ff);
}

//send string message via UART0
void UART0_dbg_msg (const void *str)
{
	uint8_t *s = (uint8_t *) str;
	while (*s)
		UART0SendChar (*s++);	
} 

//send hex number via UART0 in 0xHHHHHHHH format
void UART0_dbg_hex32 (unsigned long int x)
{ unsigned char i;
	unsigned long int temp;

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
unsigned char UART0_dbg_dec (unsigned long int x, unsigned char num)
{ 
	long int temp,res;
	unsigned char i,k;
	//if number of digits exceed limits - call exception
	if ((num<1)||(num>10) ) return 1;		
	for (i=num;i>0;i--)
	{
		temp=1;
		for (k=i;k>1;k--)
			temp*=10;
		//calculate digit
		res=x/temp;					
		x=x-res*temp;
		UART0SendChar(0x30+res);
	}
	return 0;
}

//get dec number via UART0 in D..D format, num - number digits in res
unsigned char UART0_get_dec (unsigned long int *res, unsigned char num)
{ unsigned char val,i;
	*res=0;
	for (i=0;i<num;i++)
		{
			val=UART0GetChar();
			//if invalid digit - call exception	
			if ((val<0x30)||(val>0x39)) return 1;			
			else *res=*res*10+(val-0x30);				
		}
	return 0;
}
