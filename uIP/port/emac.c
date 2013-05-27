#include "emac.h"
#include "lpc177x_8x_emac.h"
#include <string.h>
#include <stdio.h>
#include "LPC177x_8x_IOCON.h"

/* Example group ----------------------------------------------------------- */
/** @defgroup EMAC_uIP	uIP
 * @ingroup EMAC_Examples
 * @{
 */

/* Init the LPC17xx ethernet */
BOOL_8 tapdev_init(void)
{
	/* EMAC configuration type */
	EMAC_CFG_Type Emac_Config;
	/* EMAC address */
	uint8_t EMACAddr[] = {EMAC_ADDR0, EMAC_ADDR1, EMAC_ADDR2, \
						EMAC_ADDR3, EMAC_ADDR4, EMAC_ADDR5};

#if AUTO_NEGOTIATION_ENA != 0
	Emac_Config.Mode = EMAC_MODE_AUTO;
#else
	#if (FIX_SPEED == SPEED_100)
		#if (FIX_DUPLEX == FULL_DUPLEX)
			Emac_Config.Mode = EMAC_MODE_100M_FULL;
		#elif (FIX_DUPLEX == HALF_DUPLEX)
			Emac_Config.Mode = EMAC_MODE_100M_HALF;
		#else
			#error Does not support this duplex option
		#endif
	#elif (FIX_SPEED == SPEED_10)
		#if (FIX_DUPLEX == FULL_DUPLEX)
				Emac_Config.Mode = EMAC_MODE_10M_FULL;
		#elif (FIX_DUPLEX == HALF_DUPLEX)
				Emac_Config.Mode = EMAC_MODE_10M_HALF;
		#else
			#error Does not support this duplex option
		#endif
	#else
		#error Does not support this speed option
	#endif
#endif

	/*
	 * Enable P1 Ethernet Pins:
	 * P1.0 - ENET_TXD0
	 * P1.1 - ENET_TXD1
	 * P1.4 - ENET_TX_EN
	 * P1.8 - ENET_CRS
	 * P1.9 - ENET_RXD0
	 * P1.10 - ENET_RXD1
	 * P1.14 - ENET_RX_ER
	 * P1.15 - ENET_REF_CLK
	 * P1.16 - ENET_MDC
	 * P1.17 - ENET_MDIO
	 */
	 
	 LPC_IOCON->P1_0  = 	(1<<PX_Y_IOCON_FUNC0);
	 LPC_IOCON->P1_1  = 	(1<<PX_Y_IOCON_FUNC0);	
	 LPC_IOCON->P1_4  = 	(1<<PX_Y_IOCON_FUNC0);
	 LPC_IOCON->P1_8  = 	(1<<PX_Y_IOCON_FUNC0);
	 LPC_IOCON->P1_9  = 	(1<<PX_Y_IOCON_FUNC0);
	 LPC_IOCON->P1_10  = 	(1<<PX_Y_IOCON_FUNC0);	
	 LPC_IOCON->P1_14  = 	(1<<PX_Y_IOCON_FUNC0);
	 LPC_IOCON->P1_15  = 	(1<<PX_Y_IOCON_FUNC0);
	 LPC_IOCON->P1_16  = 	(1<<PX_Y_IOCON_FUNC0);
	 LPC_IOCON->P1_17  = 	(1<<PX_Y_IOCON_FUNC0);	 

	Emac_Config.Mode = EMAC_MODE_AUTO;
	Emac_Config.pbEMAC_Addr = EMACAddr;
	// Initialize EMAC module with given parameter
	if (EMAC_Init(&Emac_Config) == ERROR){
		return (FALSE);
	}

	return (TRUE);
}

/* receive an Ethernet frame from MAC/DMA controller */
UNS_32 tapdev_read(void * pPacket)
{
	UNS_32 Size = EMAC_MAX_PACKET_SIZE;
	UNS_32 in_size;
	EMAC_PACKETBUF_Type RxPack;

	// Check Receive status
	if (EMAC_CheckReceiveIndex() == FALSE){
		return (0);
	}

	// Get size of receive data
	in_size = EMAC_GetReceiveDataSize() + 1;

	Size = MIN(Size,in_size);

	// Setup Rx packet
	RxPack.pbDataBuf = (uint32_t *)pPacket;
	RxPack.ulDataLen = Size;
	EMAC_ReadPacketBuffer(&RxPack);

	// update receive status
	EMAC_UpdateRxConsumeIndex();
	return(Size);
}

/* transmit an Ethernet frame to MAC/DMA controller */
BOOL_8 tapdev_send(void *pPacket, UNS_32 size)
{
	EMAC_PACKETBUF_Type TxPack;

	// Check size
	if(size == 0){
		return(TRUE);
	}

	// check Tx Slot is available
	if (EMAC_CheckTransmitIndex() == FALSE){
		return (FALSE);
	}

	size = MIN(size,EMAC_MAX_PACKET_SIZE);

	// Setup Tx Packet buffer
	TxPack.ulDataLen = size;
	TxPack.pbDataBuf = (uint32_t *)pPacket;
	EMAC_WritePacketBuffer(&TxPack);
	EMAC_UpdateTxProduceIndex();

	return(TRUE);
}

