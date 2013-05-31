/****************************************************************************
LPC177x_8x_uart.h basic definitions
****************************************************************************/
#include "LPC177x_8x.h"

#define LCR_WLS0					0
#define LCR_WLS1					1
#define LCR_DLAB					7

#define FCR_FIFOEN				0
#define FCR_RXFIFORES			1
#define FCR_TXFIFORES			2

#define LSR_RDR						0
#define LSR_THRE					5

void 		InitUART0 (void);
void 		UART0_clear_rx_buffer(void);
void 		UART0SendChar (const char x);
char 		UART0GetChar (void);
void 		UART0UnGetChar(const char val);
void 		UART0_dbg_msg (const void *str);
void 		UART0_dbg_hex32 (const uint32_t x);
uint8_t	UART0_dbg_dec (const uint32_t x, const uint8_t num);
uint8_t	UART0_get_dec (uint32_t *res, const uint8_t num);
void		UART0_get_line (char *s, const uint8_t len);
/*****************************************************************************
End Of File
******************************************************************************/
