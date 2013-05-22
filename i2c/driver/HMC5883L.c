#include "LPC177x_8x_i2c.h"
#include "lpc177x_8x_timer.h"
#include "HMC5883L.h"

void HMC5883L_init (void)
{
	//set 8-average, 15Hz measurement rate
	StartI2C0();
	SendByteI2C0 (0x3C);
	SendByteI2C0 (0x00);
	SendByteI2C0 (0x70);		//8-average, 15Hz
	SendByteI2C0 (0xA0);		//Gain=5
	//SendByteI2C0 (0x00);
	StopI2C0();
}

void HMC5883L_read_sensor (short* X, short* Y, short* Z)
{ uint8_t tmp1,tmp2; 
	
	//Set single measurement mode, initiate measurement
	StartI2C0();
	SendByteI2C0 (0x3C);
	SendByteI2C0 (0x02);
	SendByteI2C0 (0x01);		//Single measurement mode
	StopI2C0();
	delay_ms(6);
	//Set address pointer to X value register
	StartI2C0();
	SendByteI2C0 (0x3C);
	SendByteI2C0 (0x03);
	StopI2C0();
	delay_ms(70);
	//Read 6 bytes from HMC5883L
	StartI2C0();
	SendByteI2C0 (0x3D);
	tmp1=ReceiveByteI2C0_w_ACK ();
	tmp2=ReceiveByteI2C0_w_ACK ();
	*X=((tmp1<<8)|tmp2);
	tmp1=ReceiveByteI2C0_w_ACK ();
	tmp2=ReceiveByteI2C0_w_ACK ();
	*Z=((tmp1<<8)|tmp2);
	tmp1=ReceiveByteI2C0_w_ACK ();
	//Last byte without ACK
	tmp2=ReceiveByteI2C0_wo_ACK ();
	*Y=((tmp1<<8)|tmp2);
	StopI2C0();
}
