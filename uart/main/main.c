#include "LPC177x_8x.h"
#include "LPC177x_8x_uart.h"

int main(void)
{	
unsigned char mode=0;
char user_answer; 
	
InitUART0();
UART0_dbg_msg("Main Menu,\r\nPress '1' for enter to SubMenu #1\r\nPress '2' for enter to SubMenu #2\n\r");
while(1)
{	
	while (mode==0)
	{
		user_answer = UART0GetChar();
		if (user_answer=='1') {
														mode=1;
														UART0_dbg_msg("SubMenu #1\r\nPress 'q' for exit to main menu\n\r");
													}
		if (user_answer=='2') {
														mode=2;
														UART0_dbg_msg("SubMenu #2\r\nPress 'q' for exit to main menu\n\r");
													}		
	}
	while (mode==1)
	{
		user_answer = UART0GetChar(); 
		if (user_answer=='q') {
														mode=0;
														UART0_dbg_msg("Main Menu,\r\nPress '1' for enter to SubMenu #1\r\nPress '2' for enter to SubMenu #2\n\r");
													}
	}
	while (mode==2) 
	{
		user_answer = UART0GetChar();
		if (user_answer=='q') {
														mode=0;
														UART0_dbg_msg("Main Menu,\r\nPress '1' for enter to SubMenu #1\r\nPress '2' for enter to SubMenu #2\n\r");
													}
	}
}
		
}
