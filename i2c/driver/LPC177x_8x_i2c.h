/****************************************************************************
LPC177x_8x_i2c.h basic definitions
****************************************************************************/
#include "LPC177x_8x.h"

#define PCI2C0		7

#define 	CON_AA		2
#define		CON_SI		3
#define		CON_STO		4
#define 	CON_STA		5
#define 	CON_I2EN	6

#define I2C_STAT_BITMASK 0xf8

void		InitI2C0 (void);
void		StartI2C0 (void);
void		StopI2C0 (void);
void		SendByteI2C0 (const uint8_t data);
uint8_t	ReceiveByteI2C0_w_ACK (void);
uint8_t	ReceiveByteI2C0_wo_ACK (void);

/*****************************************************************************
End Of File
******************************************************************************/
