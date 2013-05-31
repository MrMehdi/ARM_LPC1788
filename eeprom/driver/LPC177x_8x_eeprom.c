#include "LPC177x_8x_eeprom.h"

void EEPROM_Init(void)
{
	//Power up EEPROM
	LPC_EEPROM->PWRDWN = 0x0;
	//Setting EEPROM CLKDIV (319dec=0x01A3hex) 120MHz/(319+1)=375kHz
	LPC_EEPROM->CLKDIV = 0x01A3;
	// Setting wait state 
	LPC_EEPROM->WSTATE = (WSATAE_PHASE3)|(WSTATE_PHASE2<<8)|(WSTATE_PHASE1<<16);
}

uint8_t EEPROM_Write(const uint16_t page_off, const uint16_t page_addr, const void* data, const EEPROM_Mode_Type mode, const uint32_t count)
{
	uint32_t i;
	uint16_t page_offset, page_address;
#if (mode == MODE_8_BIT)
        uint8_t *tmp = (uint8_t *)data;
#elif (mode == MODE_16_BIT)
        uint16_t *tmp = (uint16_t *)data;
#else
        uint32_t *tmp = (uint32_t *)data;
#endif
	page_offset = page_off;
	page_address=page_addr;
	//clear EEPROM and of RW and PROGRAM flags
	LPC_EEPROM->INT_CLR_STATUS = ((1 << EEPROM_ENDOF_RW)|(1 << EEPROM_ENDOF_PROG));
	//check page_offset
	if ((mode == MODE_16_BIT)&&((page_offset & 0x01)!=0) ) return 0;
	else if ((mode == MODE_32_BIT)&&((page_offset & 0x03)!=0)) return 0;
	//setup EEPROM address register
	LPC_EEPROM->ADDR = EEPROM_PAGE_OFFSET(page_offset);
	//clear EEPROM and of RW flag
	LPC_EEPROM->INT_CLR_STATUS = (1 << EEPROM_ENDOF_RW);
	for(i=0;i<count;i++)
	{
		//update data to page register
		if(mode == MODE_8_BIT){
			LPC_EEPROM->CMD = EEPROM_CMD_8_BIT_WRITE;
      LPC_EEPROM -> WDATA = *tmp;
      tmp++;
			page_offset +=1;
		}
		else if(mode == MODE_16_BIT){
			LPC_EEPROM->CMD = EEPROM_CMD_16_BIT_WRITE;
      LPC_EEPROM -> WDATA = *tmp;
      tmp++;
			page_offset +=2;
		}
		else{
			LPC_EEPROM->CMD = EEPROM_CMD_32_BIT_WRITE;
      LPC_EEPROM -> WDATA = *tmp;
      tmp++;
			page_offset +=4;
		}
		//if end of page achieved and its last data byte
		if((page_offset >= EEPROM_PAGE_SIZE)|(i==count-1)){
			//update to EEPROM memory
			LPC_EEPROM->INT_CLR_STATUS = (1<<EEPROM_ENDOF_PROG);
			LPC_EEPROM->ADDR = EEPROM_PAGE_ADRESS(page_address);
			LPC_EEPROM->CMD = EEPROM_CMD_ERASE_PRG_PAGE;
			//wait
			while(!((LPC_EEPROM->INT_STATUS >> EEPROM_ENDOF_PROG)&0x01));
		}
		if(page_offset >= EEPROM_PAGE_SIZE)
		{
			page_offset = 0;
			page_address +=1;
			LPC_EEPROM->ADDR  = EEPROM_PAGE_OFFSET(page_offset);
			if(page_address > EEPROM_PAGE_NUM - 1) page_address = 0;
		}
	}
 return 1;
}

uint8_t EEPROM_Read(const uint16_t page_off, const uint16_t page_addr, void* data, const EEPROM_Mode_Type mode, const uint32_t count)
{
	uint32_t i;
	uint16_t page_offset, page_address;
#if (mode == MODE_8_BIT)
        uint8_t *tmp = (uint8_t *)data;
#elif (mode == MODE_16_BIT)
        uint16_t *tmp = (uint16_t *)data;
#else
        uint32_t *tmp = (uint32_t *)data;
#endif
	page_offset = page_off;
	page_address=page_addr;
	//clear EEPROM and of RW and PROGRAM flags
	LPC_EEPROM->INT_CLR_STATUS = ((1 << EEPROM_ENDOF_RW)|(1 << EEPROM_ENDOF_PROG));
	//setup address register
	LPC_EEPROM->ADDR = EEPROM_PAGE_ADRESS(page_address)|EEPROM_PAGE_OFFSET(page_offset);
	//setup command register
	if(mode == MODE_8_BIT) LPC_EEPROM->CMD = EEPROM_CMD_8_BIT_READ|EEPROM_CMD_RDPREFETCH;
	else if(mode == MODE_16_BIT){
		LPC_EEPROM->CMD = EEPROM_CMD_16_BIT_READ|EEPROM_CMD_RDPREFETCH;
		//check page_offset
		if((page_offset &0x01)!=0) return 0;
	}
	else{
		LPC_EEPROM->CMD = EEPROM_CMD_32_BIT_READ|EEPROM_CMD_RDPREFETCH;
		//page_offset must be a multiple of 0x04
		if((page_offset & 0x03)!=0) return 0;
	}
	//read and store data in buffer
	for(i=0;i<count;i++)
	{
		 //clear end of RW flag
		 LPC_EEPROM->INT_CLR_STATUS = (1 << EEPROM_ENDOF_RW);
		 if(mode == MODE_8_BIT){
       *tmp = (uint8_t)(LPC_EEPROM -> RDATA);
       tmp++;
			 page_offset +=1;
		 }
		 else if (mode == MODE_16_BIT)
		 {
       *tmp =  (uint16_t)(LPC_EEPROM -> RDATA);
       tmp++;
			 page_offset +=2;
		 }
		 else{
       *tmp = (uint32_t)(LPC_EEPROM ->RDATA);
       tmp++;
			 page_offset +=4;
		 }
		 //wait
		 while(!((LPC_EEPROM->INT_STATUS >> EEPROM_ENDOF_RW)&0x01));
		 if(page_offset >= EEPROM_PAGE_SIZE) 
			 {
			 page_offset = 0;
			 page_address++;
			 LPC_EEPROM->ADDR = EEPROM_PAGE_ADRESS(page_address)|EEPROM_PAGE_OFFSET(page_offset);
			 if(mode == MODE_8_BIT)	LPC_EEPROM->CMD = EEPROM_CMD_8_BIT_READ|EEPROM_CMD_RDPREFETCH;
			 else if(mode == MODE_16_BIT) LPC_EEPROM->CMD = EEPROM_CMD_16_BIT_READ|EEPROM_CMD_RDPREFETCH;
			 else LPC_EEPROM->CMD = EEPROM_CMD_32_BIT_READ|EEPROM_CMD_RDPREFETCH;
			}
	}
 return 1;
}

void EEPROM_Erase(const uint32_t address)
{
	uint32_t i;
	//clear page register
	LPC_EEPROM->CMD = EEPROM_CMD_8_BIT_WRITE;
	for(i=0;i<EEPROM_PAGE_SIZE;i++)
	{
		//write 0xff
		LPC_EEPROM -> WDATA = 0xff;
		//wait
		while(!((LPC_EEPROM->INT_STATUS >> 26)&0x01));
	}
	
	LPC_EEPROM->INT_CLR_STATUS = (1<<EEPROM_ENDOF_PROG);
	LPC_EEPROM->ADDR = EEPROM_PAGE_ADRESS(address);
	LPC_EEPROM->CMD = EEPROM_CMD_ERASE_PRG_PAGE;
	//wait
	while(!((LPC_EEPROM->INT_STATUS >> EEPROM_ENDOF_PROG)&0x01));
}

