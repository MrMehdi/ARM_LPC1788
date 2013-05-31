/**********************************************************************
* SDRAM_k4s561632j.h
* Contains all macro definitions for SAMSUNG K4S561632J on SK-MLPC1788 
**********************************************************************/
#include "LPC177x_8x.h"

#define PCEMC11				11

#define CMDDLY0				0
#define CMDDLY1				1
#define CMDDLY2				2
#define CMDDLY3				3
#define CMDDLY4				4

#define FBCLKDLY8			8
#define FBCLKDLY9			9
#define FBCLKDLY10		10
#define FBCLKDLY11		11
#define FBCLKDLY12		12

#define EMCCONTROL_EMCENABLE0		0

#define DMRC_RD0			0
#define DMRC_RD1			1

#define DMRCD_RAS0		0
#define DMRCD_RAS1		1
#define DMRCD_CAS8		8
#define DMRCD_CAS9		9

#define DMC_AM7				7
#define DMC_AM8				8
#define DMC_AM9				9
#define DMC_AM10			10
#define DMC_AM11			11
#define DMC_AM12			12
#define DMC_AM14			14
#define DMC_B19				19
#define DMC_P20				20

#define DCR_CE0						0
#define DCR_CS1						1
#define DCR_SDRAM_INIT7		7
#define DCR_SDRAM_INIT8		8	

#define SDRAM_BASE_ADDR		0xA0000000
#define SDRAM_SIZE				0x2000000
#define MHZ								*10000001

#define SYS_FREQ				120MHZ

#if   SYS_FREQ == (120MHZ)
#define SDRAM_PERIOD          8.33  // 120MHz    
#elif     SYS_FREQ == (96MHZ)                 
#define SDRAM_PERIOD          10.4  // 96MHz    
#elif   SYS_FREQ == (72MHZ)                   
#define SDRAM_PERIOD          13.8  // 72MHz    
#elif   SYS_FREQ == (60MHZ)                   
#define SDRAM_PERIOD          16.67  // 60MHz   
#elif   SYS_FREQ == (57MHZ)
#define SDRAM_PERIOD          17.4  // 57.6MHz  
#elif SYS_FREQ == (48MHZ)
#define SDRAM_PERIOD          20.8  // 48MHz    
#elif SYS_FREQ == (36MHZ)
#define SDRAM_PERIOD          27.8  // 36MHz    
#elif SYS_FREQ == (24MHZ)
#define SDRAM_PERIOD          41.7  // 24MHz    
#elif SYS_FREQ == (12MHZ)
#define SDRAM_PERIOD          83.3  // 12MHz    
#else
#error Frequency not defined                    
#endif

#define P2C(Period)           (((Period<SDRAM_PERIOD)?0:(uint32_t)((float)Period/SDRAM_PERIOD))+1)

#define SDRAM_REFRESH         3200000
#define SDRAM_TRP             20
#define SDRAM_TRAS            45
#define SDRAM_TAPR            1		
#define SDRAM_TDAL            1		
#define SDRAM_TWR             1		
#define SDRAM_TRC             65	
#define SDRAM_TRFC            66	
#define SDRAM_TXSR            67	
#define SDRAM_TRRD            15
#define SDRAM_TMRD            3

void				SDRAMInit				(void);
uint8_t			SDRAM8BitTest		(void);
uint8_t			SDRAM16BitTest	(void);

/*****************************************************************************
**                            End Of File
******************************************************************************/
