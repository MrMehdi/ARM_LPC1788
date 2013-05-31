#include "LPC177x_8x.h"
#include "LPC177x_8x_IOCON.h"
#include "sdram_k4s561632j.h"
#include "LPC177x_8x_crc.h"
#include "stdlib.h"

/*********************************************************************//*
 * Initialize external SDRAM memory Samsung k4s561632j on SK-MLPC1788 
 * 256Mbit(16M x 16)
 **********************************************************************/
 
void SDRAMInit(void)
{
	volatile uint32_t i;
	volatile unsigned long Dummy;
	//Init corresponding IO pins
	LPC_IOCON->P2_16 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P2_17 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P2_18 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P2_20 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P2_24 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P2_28 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P2_29 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P3_0 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P3_1 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P3_2 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P3_3 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P3_4 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P3_5 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P3_6 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P3_7 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P3_8 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P3_9 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P3_10 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P3_11 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P3_12 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P3_13 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P3_14 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P3_15 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P4_0 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P4_1 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P4_2 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P4_3 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P4_4 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P4_5 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P4_6 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P4_7 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P4_8 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P4_9 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P4_10 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P4_11 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P4_12 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P4_13 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P4_14 = 	(1<<PX_Y_IOCON_FUNC0);
	LPC_IOCON->P4_25 = 	(1<<PX_Y_IOCON_FUNC0);
	//EMC power on
	LPC_SC->PCONP   	|= (1<<PCEMC11);		
	//Init SDRAM controller
	//Set data read delay, command delayed, clock not delayed
	LPC_SC->EMCDLYCTL |= (1<<CMDDLY3)|(1<<CMDDLY4)|(1<<FBCLKDLY9)|(1<<FBCLKDLY11);
	// Enable EMC 
	LPC_EMC->Control = (1<<EMCCONTROL_EMCENABLE0);
	// Set data read delay mode, commad delayed, clock not delayed 
	LPC_EMC->DynamicReadConfig = (1<<DMRC_RD0);
	// Set RAS&CAS 
	LPC_EMC->DynamicRasCas0 = (1<<DMRCD_RAS0)|(1<<DMRCD_RAS1)|(1<<DMRCD_CAS8)|(1<<DMRCD_CAS9);
	// Set SDRAM timings
	LPC_EMC->DynamicRP = P2C(SDRAM_TRP);
	LPC_EMC->DynamicRAS = P2C(SDRAM_TRAS);
	LPC_EMC->DynamicSREX = P2C(SDRAM_TXSR);
	LPC_EMC->DynamicAPR = SDRAM_TAPR;
	LPC_EMC->DynamicDAL = SDRAM_TDAL+P2C(SDRAM_TRP);
	LPC_EMC->DynamicWR = SDRAM_TWR;
	LPC_EMC->DynamicRC = P2C(SDRAM_TRC);
	LPC_EMC->DynamicRFC = P2C(SDRAM_TRFC);
	LPC_EMC->DynamicXSR = P2C(SDRAM_TXSR);
	LPC_EMC->DynamicRRD = P2C(SDRAM_TRRD);
	LPC_EMC->DynamicMRD = SDRAM_TMRD;
	// 16-bit external bus, 256M (16Mx16), 4banks, row length 13, column length 9 
	LPC_EMC->DynamicConfig0 =   (1<<DMC_AM7)|(1<<DMC_AM9)|(1<<DMC_AM10);
	// JEDEC General SDRAM Initialization Sequence
	// Settle DELAY to allow power and clocks to stabilize ~200 us
	// SDRAM NOP + enable CLKOUT to run continiously
	LPC_EMC->DynamicControl = (1<<DCR_CE0)|(1<<DCR_CS1)|(1<<DCR_SDRAM_INIT7)|(1<<DCR_SDRAM_INIT8);
	for(i= 200*120; i;i--);
	// SDRAM PALL
	LPC_EMC->DynamicControl = (1<<DCR_CE0)|(1<<DCR_CS1)|(1<<DCR_SDRAM_INIT8);
	//Set refresh frequency for initialization, 8 refresh cycles
	LPC_EMC->DynamicRefresh = 2;
	for(i= 256; i; --i); // > 256=8*16*DynamicRefresh clk
	//Set refresh frequency for normal operation
	LPC_EMC->DynamicRefresh = P2C(SDRAM_REFRESH) >> 4;
	// SDRAM PALL command
	LPC_EMC->DynamicControl = (1<<DCR_CE0)|(1<<DCR_CS1)|(1<<DCR_SDRAM_INIT7);
	// Issue mode register, mode=0x33 (sequental burst size 8, CAS latency 3)
	// 0xA000 0000 + (0x33 << (2 + 9 + 1)) = 0xA000 0000 + 0x33000 = 0xA003 3000
	Dummy = *((volatile uint32_t *)(SDRAM_BASE_ADDR+(0x33<<12)));
	// SDRAM NORM mode
	LPC_EMC->DynamicControl = (1<<DCR_CS1);			
	//  Enable buffer, disable write protect
	LPC_EMC->DynamicConfig0 = (1<<DMC_AM7)|(1<<DMC_AM9)|(1<<DMC_AM10)|(1<<DMC_B19);
	for(i = 100000; i;i--);
}

uint8_t SDRAM8BitTest (void)
{
	uint16_t  crc1, crc2;
	uint8_t x;
	volatile uint8_t *wr_ptr;
  volatile unsigned long int l;
	//Init CRC engine
	CRC_Init(CRC_POLY_CRCCCITT);
	//Write random byte data to SDRAM from 0xA0000000 to 0xA2000000 address
  wr_ptr = (uint8_t *)SDRAM_BASE_ADDR;		
  for (l=0; l<0x02000000; l++)
		{
		x=(uint8_t)rand();
		*wr_ptr = x;					
		//calculate CRC1
		crc1=CRC_CalcDataChecksum (x,CRC_WR_8BIT);
		wr_ptr++;
		} 
	//Reset CRC engine
	CRC_Reset();
	//Calculate CRC2
	crc2=CRC_CalcBlockChecksum((void *)SDRAM_BASE_ADDR,0x02000000,CRC_WR_8BIT);	
	//Compare CRC1 and CRC2
  if(crc1 != crc2)	return 0;
							else	return 1;
}

uint8_t SDRAM16BitTest (void)
{
	uint16_t x, crc1, crc2;
	volatile uint16_t *wr_ptr;
  volatile unsigned long int l;
	//Init CRC engine
	CRC_Init(CRC_POLY_CRC16);
	//Write random word data to SDRAM from 0xA0000000 to 0xA2000000 address
  wr_ptr = (uint16_t *)SDRAM_BASE_ADDR;		
  for (l=0; l<0x01000000; l++)
		{
		x= (uint16_t) rand();
		*wr_ptr = x;					
		//calculate CRC1
		crc1=CRC_CalcDataChecksum (x,CRC_WR_16BIT);
		wr_ptr++;
		} 
	//Reset CRC engine
	CRC_Reset();
	//Calculate CRC2
	crc2=CRC_CalcBlockChecksum((void *)SDRAM_BASE_ADDR,0x01000000,CRC_WR_16BIT);	
	//Compare CRC1 and CRC2
  if(crc1 != crc2)	return 0;
							else	return 1;
}
