#include "LPC177x_8x.h"
#include "LPC177x_8x_IOCON.h"

void InitPorts (void)
{
	//setup IOCON registers
	LPC_IOCON->P2_8  = 	(1<<PX_Y_IOCON_MODE4)|(1<<PX_Y_IOCON_HYS5);
	LPC_IOCON->P2_11 = 	(1<<PX_Y_IOCON_MODE4)|(1<<PX_Y_IOCON_HYS5);
	//setup GPIO registers
	LPC_GPIO2->CLR = (1<<GPIO2_pin8);
	LPC_GPIO2->DIR = (1<<GPIO2_pin8)|(0<<GPIO2_pin11);
}

void bad_pause (uint32_t x)
{
	uint32_t i;
	for (i=0;i<x;i++) ; 
}
 
int main(void)
{	
uint8_t mode=0;
	
InitPorts();	
while(1)
{
	//if mode == 0 then turn OFF LED on P2_8
	while (mode==0)
	{
		if (((LPC_GPIO2->PIN)&(1<<GPIO2_pin11))==0) mode=1;
		LPC_GPIO2->CLR = (1<<GPIO2_pin8);
	}
	bad_pause(500000);
	//if mode == 1 then turn ON LED on P2_8
	while (mode==1)
	{
		if (((LPC_GPIO2->PIN)&(1<<GPIO2_pin11))==0) mode=0;
		LPC_GPIO2->SET = (1<<GPIO2_pin8);
	}
	bad_pause(500000); 
}
		
}
