#include "AT45DB021.h"
#include "LPC177x_8x_ssp.h"

uint8_t AT45DB021_ReadStatus (void)
{ 
	//Clear RX FIFO
	ClearSSP1RXFIFO();
	//Activate CS
	LPC_GPIO4->CLR |= (1<<GPIO4_SSEL1);
	//Send read status cmd
	SSP1_SendByte (0xD7);
	SSP1_SendByte (0x00);
	//Deactivate CS
	while ( (LPC_SSP1->SR&(1<<SSP1_SRBUSY)) != 0x00 ) ;
	LPC_GPIO4->SET |= (1<<GPIO4_SSEL1);
	//Read dummy byte
	SSP1_ReceiveByte();
	//Read status byte
	return SSP1_ReceiveByte();
}

uint8_t AT45DB021_ReadBlock (uint8_t *data, const uint32_t address, const uint32_t len)
{ 
	uint16_t page,byte;
	uint32_t length;
	length = len;
	//If incorrect intup data - exit
	if ((address+length)>(PAGE_SIZE*PAGE_COUNT)) return 0;
	//Calculate page and byte address
	page = address / PAGE_SIZE;
	byte = address - page*PAGE_SIZE;
	while (length>0) 
	{
		//READ BUFFER1 FROM MEMORY
		//Check that AT45DB021 is ready
		while ( (AT45DB021_ReadStatus()&0x80)==0x00) ;
		//Activate CS
		LPC_GPIO4->CLR |= (1<<GPIO4_SSEL1);
		//Send read memory to buffer 1 cmd
		SSP1_SendByte(0x53);
		SSP1_SendByte(page>>7);
		SSP1_SendByte(page<<1);
		SSP1_SendByte(0x00);
		//Deactivate CS
		while ( (LPC_SSP1->SR&(1<<SSP1_SRBUSY)) != 0x00 ) ;
		LPC_GPIO4->SET |= (1<<GPIO4_SSEL1);
		//READ BUFFER1
		//Check that AT45DB021 is ready
		while ( (AT45DB021_ReadStatus()&0x80)==0x00) ;
		//Activate CS
		LPC_GPIO4->CLR |= (1<<GPIO4_SSEL1);
		//Send write data to buffer1
		SSP1_SendByte(0xD4);
		SSP1_SendByte(0x00);
		SSP1_SendByte(byte>>8);
		SSP1_SendByte(byte);
		SSP1_SendByte(0x00);
		//Clear RX FIFO
		ClearSSP1RXFIFO();	
		//Read data from buffer1
		while ((length>0)&(byte<PAGE_SIZE))
			{
				SSP1_SendByte(0x00);
				*data = SSP1_ReceiveByte();
				data++;
				byte++;
				length--;
			}
		//Deactivate CS
		while ( (LPC_SSP1->SR&(1<<SSP1_SRBUSY)) != 0x00 ) ;
		LPC_GPIO4->SET |= (1<<GPIO4_SSEL1);
		//Values for new page (if needed)
		page++;
		byte=0;
	}
	return 1;
}

uint8_t AT45DB021_WriteBlock (const uint8_t *data, const uint32_t address, const uint32_t len)
{	uint16_t page,byte;
	uint32_t length;
	length =len;
	//If incorrect intup data - exit
	if ((address+length)>(PAGE_SIZE*PAGE_COUNT)) return 0;
	//Calculate page and byte address
	page = address / PAGE_SIZE;
	byte = address - page*PAGE_SIZE;
	while (length>0) 
	{
		//READ BUFFER1 FROM MEMORY
		//Check that AT45DB021 is ready
		while ( (AT45DB021_ReadStatus()&0x80)==0x00) ;
		//Activate CS
		LPC_GPIO4->CLR |= (1<<GPIO4_SSEL1);
		//Send read memory to buffer 1 cmd
		SSP1_SendByte(0x53);
		SSP1_SendByte(page>>7);
		SSP1_SendByte(page<<1);
		SSP1_SendByte(0x00);
		//Deactivate CS
		while ( (LPC_SSP1->SR&(1<<SSP1_SRBUSY)) != 0x00 ) ;
		LPC_GPIO4->SET |= (1<<GPIO4_SSEL1);
		//WRITE BUFFER1
		//Check that AT45DB021 is ready
		while ( (AT45DB021_ReadStatus()&0x80)==0x00) ;
		//Activate CS
		LPC_GPIO4->CLR |= (1<<GPIO4_SSEL1);
		//Send write data to buffer1
		SSP1_SendByte(0x84);
		SSP1_SendByte(0x00);
		SSP1_SendByte(byte>>8);
		SSP1_SendByte(byte);
		//Write data to buffer1
		while ((length>0)&(byte<PAGE_SIZE))
			{
				SSP1_SendByte(*data);
				data++;
				byte++;
				length--;
			}
		//Deactivate CS
		while ( (LPC_SSP1->SR&(1<<SSP1_SRBUSY)) != 0x00 ) ;
		LPC_GPIO4->SET |= (1<<GPIO4_SSEL1);
		//WRITE BUFFER1 TO MEMORY
		//Check that AT45DB021 is ready
		while ( (AT45DB021_ReadStatus()&0x80)==0x00) ;
		//Activate CS
		LPC_GPIO4->CLR |= (1<<GPIO4_SSEL1);
		//Write data from buffer1 to memory
		SSP1_SendByte(0x83);
		SSP1_SendByte(page>>7);
		SSP1_SendByte(page<<1);
		SSP1_SendByte(0x00);
		//Deactivate CS
		while ( (LPC_SSP1->SR&(1<<SSP1_SRBUSY)) != 0x00 ) ;
		LPC_GPIO4->SET |= (1<<GPIO4_SSEL1);
		//Values for new page (if needed)
		page++;
		byte=0;
	}
	return 1;
}

uint8_t AT45DB021_EraseBlock (const uint32_t address, const uint32_t len)
{	uint16_t page,byte;
	uint32_t length;
	length = len;
	//If incorrect intup data - exit
	if ((address+length)>(PAGE_SIZE*PAGE_COUNT)) return 0;
	//Calculate page and byte address
	page = address / PAGE_SIZE;
	byte = address - page*PAGE_SIZE;
	while (length>0) 
	{
		//READ BUFFER1 FROM MEMORY
		//Check that AT45DB021 is ready
		while ( (AT45DB021_ReadStatus()&0x80)==0x00) ;
		//Activate CS
		LPC_GPIO4->CLR |= (1<<GPIO4_SSEL1);
		//Send read memory to buffer 1 cmd
		SSP1_SendByte(0x53);
		SSP1_SendByte(page>>7);
		SSP1_SendByte(page<<1);
		SSP1_SendByte(0x00);
		//Deactivate CS
		while ( (LPC_SSP1->SR&(1<<SSP1_SRBUSY)) != 0x00 ) ;
		LPC_GPIO4->SET |= (1<<GPIO4_SSEL1);
		//WRITE BUFFER1
		//Check that AT45DB021 is ready
		while ( (AT45DB021_ReadStatus()&0x80)==0x00) ;
		//Activate CS
		LPC_GPIO4->CLR |= (1<<GPIO4_SSEL1);
		//Send write data to buffer1
		SSP1_SendByte(0x84);
		SSP1_SendByte(0x00);
		SSP1_SendByte(byte>>8);
		SSP1_SendByte(byte);
		//Write data to buffer1
		while ((length>0)&(byte<PAGE_SIZE))
			{
				SSP1_SendByte(0x00);
				byte++;
				length--;
			}
		//Deactivate CS
		while ( (LPC_SSP1->SR&(1<<SSP1_SRBUSY)) != 0x00 ) ;
		LPC_GPIO4->SET |= (1<<GPIO4_SSEL1);
		//WRITE BUFFER1 TO MEMORY
		//Check that AT45DB021 is ready
		while ( (AT45DB021_ReadStatus()&0x80)==0x00) ;
		//Activate CS
		LPC_GPIO4->CLR |= (1<<GPIO4_SSEL1);
		//Write data from buffer1 to memory
		SSP1_SendByte(0x83);
		SSP1_SendByte(page>>7);
		SSP1_SendByte(page<<1);
		SSP1_SendByte(0x00);
		//Deactivate CS
		while ( (LPC_SSP1->SR&(1<<SSP1_SRBUSY)) != 0x00 ) ;
		LPC_GPIO4->SET |= (1<<GPIO4_SSEL1);
		//Values for new page (if needed)
		page++;
		byte=0;
	}
	return 1;
}
