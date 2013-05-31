/****************************************************************************
BMP085.h basic definitions
****************************************************************************/
#include "LPC177x_8x.h"

typedef struct 
{ short AC1;
 short AC2;
 short AC3;
 unsigned short AC4;
 unsigned short AC5;
 unsigned short AC6;
 short B1;
 short B2;
 short MB;
 short MC;
 short MD; }  BMP085_CAL_DATA_STRUCT;

void BMP085_read_CAL_data (BMP085_CAL_DATA_STRUCT *CAL_DATA);
void BMP085_read_sensor (const BMP085_CAL_DATA_STRUCT *CAL_DATA, long* temperature, long* pressure, uint8_t oss);
/*****************************************************************************
End Of File
******************************************************************************/
