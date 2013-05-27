/****************************************************************************
LPC177x_8x_uart.h basic definitions
****************************************************************************/
#define LCR_WLS0					0
#define LCR_WLS1					1
#define LCR_DLAB					7

#define FCR_FIFOEN				0
#define FCR_RXFIFORES			1
#define FCR_TXFIFORES			2

#define LSR_RDR						0
#define LSR_THRE					5

void					InitUART0							(void);
void					UART0_clear_rx_buffer	(void);
void					UART0SendChar					(char x);
char					UART0GetChar					(void);
void					UART0_dbg_msg					(const void *str);
void					UART0_dbg_hex32				(unsigned long int x);
unsigned char	UART0_dbg_dec					(unsigned long int x, unsigned char num);
unsigned char	UART0_get_dec					(unsigned long int *res, unsigned char num);
/*****************************************************************************
End Of File
******************************************************************************/
