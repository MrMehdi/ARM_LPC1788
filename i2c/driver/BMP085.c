#include "LPC177x_8x_i2c.h"
#include "lpc177x_8x_timer.h"
#include "BMP085.h"

void BMP085_read_CAL_data (BMP085_CAL_DATA_STRUCT *CAL_DATA)
{	uint8_t i,tmp1,tmp2;
		
		StartI2C0();
		//Read from 0xAA address, 22 bytes
		SendByteI2C0 (0xEE);
		SendByteI2C0 (0xAA);
		StartI2C0();
		SendByteI2C0 (0xEF);
		//Read 20 bytes
		for (i=0;i<10;i++)
			{
				tmp1=ReceiveByteI2C0_w_ACK ();
				tmp2=ReceiveByteI2C0_w_ACK ();
				switch (i)
					{
						case 	0		: {CAL_DATA->AC1 = (tmp1<<8)|(tmp2); break;}
						case 	1		: {CAL_DATA->AC2 = (tmp1<<8)|(tmp2); break;}
						case 	2		: {CAL_DATA->AC3 = (tmp1<<8)|(tmp2); break;}
						case 	3		: {CAL_DATA->AC4 = (tmp1<<8)|(tmp2); break;}
						case 	4		: {CAL_DATA->AC5 = (tmp1<<8)|(tmp2); break;}
						case 	5		: {CAL_DATA->AC6 = (tmp1<<8)|(tmp2); break;}
						case 	6		: {CAL_DATA->B1 = (tmp1<<8)|(tmp2); break;}
						case 	7		: {CAL_DATA->B2 = (tmp1<<8)|(tmp2); break;}
						case 	8		: {CAL_DATA->MB = (tmp1<<8)|(tmp2); break;}
						case 	9		: {CAL_DATA->MC = (tmp1<<8)|(tmp2); break;}
					}			
			}
		//read 2 last bytes
		tmp1=ReceiveByteI2C0_w_ACK ();
		//last byte witout ACK
		tmp2=ReceiveByteI2C0_wo_ACK ();	
		CAL_DATA->MD = (tmp1<<8)|(tmp2);
		StopI2C0();
}

void BMP085_read_sensor (const BMP085_CAL_DATA_STRUCT *CAL_DATA, long* temperature, long* pressure, uint8_t oss)
{	uint8_t tmp1,tmp2,tmp3;
	long x1,x2,x3,b3,b5,b6,ut,up,p;
	unsigned long b4,b7;
	//Start measuring temperature
	StartI2C0();
	SendByteI2C0 (0xEE);
	SendByteI2C0 (0xF4);
	SendByteI2C0 (0x2E);
	StopI2C0();
	//Wait 4.5ms for conversion and read uncompensated temperature
	delay_ms(5);
	StartI2C0();
	SendByteI2C0 (0xEE);
	SendByteI2C0 (0xF6);
	StartI2C0();
	SendByteI2C0 (0xEF);
	tmp1=ReceiveByteI2C0_w_ACK ();
	//last byte witout ACK
	tmp2=ReceiveByteI2C0_wo_ACK ();	
	StopI2C0();
	ut =  ((tmp1<<8)|(tmp2));
	//Calibrate temperature;
	x1 = (((ut-CAL_DATA->AC6)*CAL_DATA->AC5)>>15);
	x2 = (CAL_DATA->MC<<11)/(x1+CAL_DATA->MD);
	b5 = x1+x2;
	*temperature =  ((b5+8)>>4);
	
	//oss must be in 0..3 range
	oss&=0x03;
	//Start measuring pressure
	StartI2C0();
	SendByteI2C0 (0xEE);
	SendByteI2C0 (0xF4);
	//Send cmd to BMP085 and set pause after cmd according to oss mode
	switch (oss)
	{
		case 0 : { SendByteI2C0 (0x34); StopI2C0(); delay_ms(5); break;}		//Wait 4.5ms for conversion and read uncompensated pressure
		case 1 : { SendByteI2C0 (0x74); StopI2C0(); delay_ms(8); break;}		//Wait 7.5ms for conversion and read uncompensated pressure
		case 2 : { SendByteI2C0 (0xB4); StopI2C0(); delay_ms(14); break;}		//Wait 13.5ms for conversion and read uncompensated pressure
		case 3 : { SendByteI2C0 (0xF4); StopI2C0(); delay_ms(26); break;}		//Wait 25.5ms for conversion and read uncompensated pressure
	}
	//Start reading uncompensated pressure
	StartI2C0();
	SendByteI2C0 (0xEE);
	SendByteI2C0 (0xF6);
	StartI2C0();
	SendByteI2C0 (0xEF);
	tmp1=ReceiveByteI2C0_w_ACK ();
	tmp2=ReceiveByteI2C0_w_ACK ();
	//last byte witout ACK
	tmp3=ReceiveByteI2C0_wo_ACK ();	
	StopI2C0();
	up=((tmp1<<16)|(tmp2<<8)|tmp3)>>(8-oss);
	//Calibrate pressure
  b6 = b5 - 4000;
  x1 = (b6*b6) >> 12;
  x1 *= CAL_DATA->B2;
  x1 >>=11;
  x2 = (CAL_DATA->AC2*b6);
  x2 >>=11;
  x3 = x1 +x2;
  b3 = (((((long)CAL_DATA->AC1)*4 + x3)<<oss) + 2) >> 2;
  x1 = (CAL_DATA->AC3* b6) >> 13;
  x2 = (CAL_DATA->B1 * ((b6*b6) >> 12) ) >> 16;
  x3 = ((x1 + x2) + 2) >> 2;
  b4 = (CAL_DATA->AC4 * (unsigned long) (x3 + 32768)) >> 15;
  b7 = ((unsigned long)(up - b3) * (50000>>oss));
  if (b7 < 0x80000000) p = (b7 << 1) / b4;
						else       p = (b7 / b4) << 1;
  x1 = p >> 8;
  x1 *= x1;
  x1 = (x1 * 3038) >> 16;
  x2 = (p * -7357) >> 16;
  *pressure = p + ((x1 + x2 + 3791) >> 4);    //Calibrate pressure in Pa
}
