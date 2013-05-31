#include "LPC177x_8x_uart.h"
#include "LPC177x_8x_i2c.h"
#include "lpc177x_8x_timer.h"

#include "BMP085.h"
#include "HMC5883L.h"

#include "math.h"

#define _PI 3.141592653589793238464

int main(void)
{	BMP085_CAL_DATA_STRUCT BMP085_CAL_DATA;
	long temperature,pressure;
	short i,RawMag[3],CalMag[3],Offset[3],MaxMag[3],MinMag[3];
	double Scale[3];
	double angle;
	
	InitUART0 (); 
	UART0_dbg_msg (
	"********************************************************************************\n\r"
	" Internal I2C test on LPC1788\n\r"
	"\t - UART Comunication: 9600 bps\n\r"
	"********************************************************************************\n\r");	
	InitI2C0();
	BMP085_read_CAL_data(&BMP085_CAL_DATA);	
	HMC5883L_init ();
	
	MinMag[0]=MinMag[1]=MinMag[2]=0;
	MaxMag[0]=MaxMag[1]=MaxMag[2]=0;
	
	while (1) 
	{ 
		BMP085_read_sensor(&BMP085_CAL_DATA,&temperature,&pressure,3);
		UART0_dbg_dec((uint32_t)temperature,3);
		UART0_dbg_msg (" = temperature in 0.1C; ");
		UART0_dbg_dec((uint32_t)pressure,6);
		UART0_dbg_msg (" = pressure in Pa, oss=3 ");	
		
		HMC5883L_read_sensor(&RawMag[0],&RawMag[1],&RawMag[2]);
						
		for (i=0;i<3;i++)
			{
				if (MinMag[i]>RawMag[i]) MinMag[i]=RawMag[i];
				if (MaxMag[i]<RawMag[i]) MaxMag[i]=RawMag[i];
				
				Offset[i] = -(MinMag[i]+MaxMag[i] )/2;
				Scale [i] = (double) (MaxMag[0]+Offset[0])/(MaxMag[i]+Offset[i]);
				
				CalMag[i] = (RawMag[i]+Offset[i])*Scale[i];
			} 
			
		if ((CalMag[0]>0)&&(CalMag[1]>0)) angle = 240+180*atan((double) CalMag[0]/CalMag[1])/_PI;
		if ((CalMag[0]>0)&&(CalMag[1]<0)) angle = 180*atan((double) -CalMag[1]/CalMag[0])/_PI; 
		if ((CalMag[0]<0)&&(CalMag[1]>0)) angle = 180+180*atan((double) -CalMag[1]/CalMag[0])/_PI;
		if ((CalMag[0]<0)&&(CalMag[1]<0)) angle = 90+ 180*atan((double) CalMag[0]/CalMag[1])/_PI;
			
		UART0_dbg_msg ("X=");
		if (RawMag[0]<0) {UART0SendChar('-'); RawMag[0]=-RawMag[0];}
		UART0_dbg_dec(RawMag[0],4);
		UART0_dbg_msg (" Y=");
		if (RawMag[1]<0) {UART0SendChar('-'); RawMag[1]=-RawMag[1];}
		UART0_dbg_dec(RawMag[1],4);
		UART0_dbg_msg (" Z=");
		if (RawMag[2]<0) {UART0SendChar('-'); RawMag[2]=-RawMag[2];}
		UART0_dbg_dec(RawMag[2],4);
		
		UART0_dbg_msg (" sqrt=");
		UART0_dbg_dec (sqrt(RawMag[0]*RawMag[0]+RawMag[1]*RawMag[1]+RawMag[2]*RawMag[2]),6);
		
		UART0_dbg_msg (" | X=");
		if (CalMag[0]<0) {UART0SendChar('-'); CalMag[0]=-CalMag[0];}
		UART0_dbg_dec(CalMag[0],4);
		UART0_dbg_msg (" Y=");
		if (CalMag[1]<0) {UART0SendChar('-'); CalMag[1]=-CalMag[1];}
		UART0_dbg_dec(CalMag[1],4);
		UART0_dbg_msg (" Z=");
		if (CalMag[2]<0) {UART0SendChar('-'); CalMag[2]=-CalMag[2];}
		UART0_dbg_dec(CalMag[2],4);
		
		UART0_dbg_msg (" sqrt=");
		UART0_dbg_dec (sqrt(CalMag[0]*CalMag[0]+CalMag[1]*CalMag[1]+CalMag[2]*CalMag[2]),6);
		
		UART0_dbg_msg (" angle=");	
		UART0_dbg_dec ((long)angle,5);
		
		UART0_dbg_msg ("\n\r");
	}
}
