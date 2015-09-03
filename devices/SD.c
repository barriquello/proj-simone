
/* Includes */
#include "SD.h"
#include "BRTOS.h"
#include "drivers.h"

#if PLATAFORMA == COLDUINO
#pragma warn_implicitconv off
#else
uint8_t dummy;
#endif



static volatile DSTATUS   Stat             = STA_NOINIT;	/* Disk status */
static volatile int Timer                      = 0;           /* Read/Write timer */
#ifdef USE_OS
  static volatile INT16U    Timer1;	                      /* 100Hz decrement timer */
  static volatile INT8U     Timer2;
#else
  static volatile INT8U     Timer1, Timer2;	              /* 100Hz decrement timer */
#endif
static          BYTE      CardType;			                  /* Card type flags */
//static volatile BYTE      SPIData          = 0;


DWORD get_fattime (void)
{
  OS_RTC rtc; 
  
  GetCalendar(&rtc);
  
  return    ((DWORD)(rtc.Year - 1980) << 25)
          | ((DWORD)rtc.Month << 21)
          | ((DWORD)rtc.Day   << 16)
          | ((DWORD)rtc.Hour  << 11)
          | ((DWORD)rtc.Min << 5)
          | ((DWORD)rtc.Sec << 1);
}

/*-----------------------------------------------------------------------*/
/* Transmit a byte to MMC via SPI  (Platform dependent)                  */
/*-----------------------------------------------------------------------*/

void xmit_spi(INT8U dat)
{
	SPI1_SendChar(dat);
}



/*-----------------------------------------------------------------------*/
/* Receive a byte from MMC via SPI  (Platform dependent)                 */
/*-----------------------------------------------------------------------*/

static BYTE rcvr_spi (void)
{
	BYTE SPIData = SPI1_GetChar();
	return SPIData;
}

/* Alternative macro to receive data fast */
//#define rcvr_spi_m(dst)	xmit_spi(0xFF); *(dst)=SPIData
#define rcvr_spi_m(dst)		*(dst)=SPI1_GetChar();



/*-----------------------------------------------------------------------*/
/* Wait for card ready                                                   */
/*-----------------------------------------------------------------------*/

static
int wait_ready (void)	    /* 1:OK, 0:Timeout */
{
	#ifdef USE_OS
	  INT16U Timer3 = 500;	// Wait for ready in timeout of 500ms
	#else
	  Timer2 = 50;	        // Wait for ready in timeout of 500ms
	#endif
	
	do
	{
		if (rcvr_spi() == 0xFF)
		{
		  return 1;
		}
		
	#ifdef USE_OS
		Timer3--;
		DelayTask(1);
	} while (Timer3);
		#else
	} while (Timer2);
	#endif
			
	return 0;
}



/*-----------------------------------------------------------------------*/
/* Deselect the card and release SPI bus                                 */
/*-----------------------------------------------------------------------*/

static
void deselect (void)
{
	CS_HIGH();
	(void)rcvr_spi();
}



/*-----------------------------------------------------------------------*/
/* Select the card and wait for ready                                    */
/*-----------------------------------------------------------------------*/

static
int select (void)	/* 1:Successful, 0:Timeout */
{
	CS_LOW();
	if (!wait_ready()) {
		deselect();
		return 0;
	}
	return 1;
}



/*-----------------------------------------------------------------------*/
/* Power Control  (Platform dependent)                                   */
/*-----------------------------------------------------------------------*/
/* When the target system does not support socket power control, there   */
/* is nothing to do in these functions and chk_power always returns 1.   */

static
int power_status(void)		/* Socket power state: 0=off, 1=on */
{
	//return (PORTE & 0x80) ? 0 : 1;
	return 1;
}


static
void power_on (void)
{
	//PORTE &= ~0x80;				/* Socket power on */
    
  // Wait power up stabilization
  DelayTask(500);    
  
#if SD_CARD_PORT  
  SD_CS = 1;
  _SD_CS= 1;   
#endif  
}


static
void power_off (void)
{
	/* Disable SPI function */
	/* Disable drivers */
	// Deve ser implementado
	Stat |= STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Receive a data packet from MMC                                        */
/*-----------------------------------------------------------------------*/

static
int rcvr_datablock (
	BYTE *buff,			/* Data buffer to store received data */
	UINT btr			/* Byte count (must be multiple of 4) */
)
{
	BYTE token;


	#ifdef USE_OS
	  Timer2 = 20;
	#else
	  Timer1 = 20;
	#endif
	do 
	{							/* Wait for data packet in timeout of 200ms */
		token = rcvr_spi();
#ifdef USE_OS
	} while ((token == 0xFF) && Timer2);
#else
	} while ((token == 0xFF) && Timer1);
#endif
	if(token != 0xFE) return 0;		/* If not valid data token, retutn with error */

	do {							/* Receive the data block into buffer */
		rcvr_spi_m(buff++);
		rcvr_spi_m(buff++);
		rcvr_spi_m(buff++);
		rcvr_spi_m(buff++);
	} while (btr -= 4);
	rcvr_spi();						/* Discard CRC */
	rcvr_spi();

	return 1;						/* Return with success */
}



/*-----------------------------------------------------------------------*/
/* Send a data packet to MMC                                             */
/*-----------------------------------------------------------------------*/

static
int xmit_datablock (
	const BYTE *buff,	/* 512 byte data block to be transmitted */
	BYTE token			/* Data/Stop token */
)
{
	BYTE resp, wc;


	if (!wait_ready()) return 0;

	xmit_spi(token);					/* Xmit data token */
	if (token != 0xFD) {	/* Is data token */
		wc = 0;
		do {							/* Xmit the 512 byte data block to MMC */
			xmit_spi(*buff++);
			xmit_spi(*buff++);
		} while (--wc);
		xmit_spi(0xFF);					/* CRC (Dummy) */
		xmit_spi(0xFF);
		resp = rcvr_spi();				/* Reveive data response */
		if ((resp & 0x1F) != 0x05)		/* If not accepted, return with error */
			return 0;
	}

	return 1;
}



/*-----------------------------------------------------------------------*/
/* Send a command packet to MMC                                          */
/*-----------------------------------------------------------------------*/

static
BYTE send_cmd (		/* Returns R1 resp (bit7==1:Send failed) */
	BYTE cmd,		/* Command index */
	DWORD arg		/* Argument */
)
{
	BYTE n, res;


	if (cmd & 0x80) {	/* ACMD<n> is the command sequense of CMD55-CMD<n> */
		cmd &= 0x7F;
		res = send_cmd(CMD55, 0);
		if (res > 1) return res;
	}

	/* Select the card and wait for ready */  	
  if (cmd == CMD0)
  {
    CS_LOW();
  }else
  {
    deselect();
    if (!select()) return 0xFF;
  }

	/* Send command packet */
	xmit_spi((BYTE)(0x40 | cmd));				/* Start + Command index */
	xmit_spi((BYTE)(arg >> 24));		/* Argument[31..24] */
	xmit_spi((BYTE)(arg >> 16));		/* Argument[23..16] */
	xmit_spi((BYTE)(arg >> 8));			/* Argument[15..8] */
	xmit_spi((BYTE)arg);				/* Argument[7..0] */
	n = 0x01;							/* Dummy CRC + Stop */
	if (cmd == CMD0) n = 0x95;			/* Valid CRC for CMD0(0) */
	if (cmd == CMD8) n = 0x87;			/* Valid CRC for CMD8(0x1AA) */
	xmit_spi(n);

	/* Receive command response */
	if (cmd == CMD12) rcvr_spi();		/* Skip a stuff byte when stop reading */
	
	if (cmd == CMD0)
	{
		n = SD_WAIT_CYCLES;								// Wait for a valid response in timeout of 10 attempts
  	do
  		res = rcvr_spi();
  	while ((res != 1) && --n);
  	DelayTask(2);
	}else
	{  
	  n = SD_WAIT_CYCLES;								// Wait for a valid response in timeout of 10 attempts
  	do
  		res = rcvr_spi();
  	while ((res & 0x80) && --n);
	}	

	return res;			/* Return with the response value */
}



/*--------------------------------------------------------------------------
   Public Functions
---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/* Get Card Type                                                         */
/*-----------------------------------------------------------------------*/

INT8U GetCardType(void)
{
  return CardType;
}

/*-----------------------------------------------------------------------*/
/* Get Card Stat                                                         */
/*-----------------------------------------------------------------------*/

INT8U GetCardStat(void)
{
  return Stat;
}

/*-----------------------------------------------------------------------*/
/* Get Card Stat Init                                                       */
/*-----------------------------------------------------------------------*/

INT8U GetCardInit(void)
{
  return ((Stat & STA_NOINIT) != STA_NOINIT);
}

/*-----------------------------------------------------------------------*/
/* Set Card Stat                                                         */
/*-----------------------------------------------------------------------*/

void SetCardStat(INT8U state)
{
  Stat = state;
}


/*-----------------------------------------------------------------------*/
/* Initialize Disk Drive                                                 */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE drv		/* Physical drive nmuber (0) */
)
{
	BYTE n, cmd, ty, ocr[4];


	if (drv) return STA_NOINIT;			/* Supports only single drive */
	if (Stat & STA_NODISK) return Stat;	/* No card in the socket */

	power_on();							/* Force socket power on */
	FCLK_SLOW();
	
  /* Start SD card Init */
  SD_CS=ENABLE;
  SD_CLKDelay(20);            // Send 80 clocks 
  SD_CS=DISABLE;

  SD_CLKDelay(16);  

	ty = 0;
	if (send_cmd(CMD0, 0) == 1) {			                    /* Enter Idle state */
		#ifdef USE_OS
		  Timer1 = 1000;						                        /* Initialization timeout of 1000 msec */
		#else
		  Timer1 = 100;						                          /* Initialization timeout of 1000 msec */
		#endif
		if (send_cmd(CMD8, 0x1AA) == 1)	                    /* SDv2? */
		{
			for (n = 0; n < 4; n++) ocr[n] = rcvr_spi();		  /* Get trailing return value of R7 resp */
			if (ocr[2] == 0x01 && ocr[3] == 0xAA) {				    /* The card can work at vdd range of 2.7-3.6V */
				while (Timer1 && send_cmd(ACMD41, 1UL << 30))   /* Wait for leaving idle state (ACMD41 with HCS bit) */
				{
          #ifdef USE_OS
				    DelayTask(1);
				    Timer1--;
				  #endif
				};
				if (Timer1 && send_cmd(CMD58, 0) == 0)                /* Check CCS bit in the OCR */
				{
					for (n = 0; n < 4; n++) ocr[n] = rcvr_spi();
					ty = (ocr[0] & 0x40) ? CT_SD2 | CT_BLOCK : CT_SD2;	/* SDv2 */
				}
			}
		} else                                                    /* SDv1 or MMCv3 */
		{							
			if (send_cmd(ACMD41, 0) <= 1)
			{
				ty = CT_SD1; cmd = ACMD41;	                          /* SDv1 */
			} else 
			{
				ty = CT_MMC; cmd = CMD1;	                            /* MMCv3 */
			}
			while (Timer1 && send_cmd(cmd, 0))                      /* Wait for leaving idle state */
			{
					#ifdef USE_OS
					  DelayTask(1);
				    Timer1--;
				  #endif
			};
			if (!Timer1 || send_cmd(CMD16, 512) != 0)               /* Set R/W block length to 512 */
			{
				ty = 0;
			}
		}
	}
	
	CardType = ty;
	deselect();

	if (ty) 
	{			                    /* Initialization succeded */
		Stat &= ~STA_NOINIT;		/* Clear STA_NOINIT */
		FCLK_FAST();	
	} else 
	{			                    /* Initialization failed */
		power_off();			
	}

	return Stat;
}



/*-----------------------------------------------------------------------*/
/* Get Disk Status                                                       */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE drv		/* Physical drive nmuber (0) */
)
{
	if (drv) return STA_NOINIT;		/* Supports only single drive */
	return Stat;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE drv,			/* Physical drive nmuber (0) */
	BYTE *buff,			/* Pointer to the data buffer to store read data */
	DWORD sector,		/* Start sector number (LBA) */
	BYTE count			/* Sector count (1..255) */
)
{
	if (drv || !count) return RES_PARERR;
	if (Stat & STA_NOINIT) return RES_NOTRDY;

	if (!(CardType & CT_BLOCK)) sector *= 512;	/* Convert to byte address if needed */

	if (count == 1) {	/* Single block read */
		if ((send_cmd(CMD17, sector) == 0)	/* READ_SINGLE_BLOCK */
			&& rcvr_datablock(buff, 512))
			count = 0;
	}
	else {				/* Multiple block read */
		if (send_cmd(CMD18, sector) == 0) {	/* READ_MULTIPLE_BLOCK */
			do {
				if (!rcvr_datablock(buff, 512)) break;
				buff += 512;
			} while (--count);
			send_cmd(CMD12, 0);				/* STOP_TRANSMISSION */
		}
	}
	deselect();

	return count ? RES_ERROR : RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

DRESULT disk_write (
	BYTE drv,			/* Physical drive nmuber (0) */
	const BYTE *buff,	/* Pointer to the data to be written */
	DWORD sector,		/* Start sector number (LBA) */
	BYTE count			/* Sector count (1..255) */
)
{
	if (drv || !count) return RES_PARERR;
	if (Stat & STA_NOINIT) return RES_NOTRDY;
	if (Stat & STA_PROTECT) return RES_WRPRT;

	if (!(CardType & CT_BLOCK)) sector *= 512;	/* Convert to byte address if needed */

	if (count == 1) {	/* Single block write */
		if ((send_cmd(CMD24, sector) == 0)	/* WRITE_BLOCK */
			&& xmit_datablock(buff, 0xFE))
			count = 0;
	}
	else {				/* Multiple block write */
		if (CardType & CT_SDC) send_cmd(ACMD23, count);
		if (send_cmd(CMD25, sector) == 0) {	/* WRITE_MULTIPLE_BLOCK */
			do {
				if (!xmit_datablock(buff, 0xFC)) break;
				buff += 512;
			} while (--count);
			if (!xmit_datablock(0, 0xFD))	/* STOP_TRAN token */
				count = 1;
		}
	}
	deselect();

	return count ? RES_ERROR : RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive nmuber (0) */
	BYTE ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	BYTE n, csd[16], *ptr = buff;
	WORD csize;


	if (drv) return RES_PARERR;

	res = RES_ERROR;

	if (ctrl == CTRL_POWER) {
		switch (ptr[0]) {
		case 0:		/* Sub control code (POWER_OFF) */
			power_off();		/* Power off */
			res = RES_OK;
			break;
		case 1:		/* Sub control code (POWER_GET) */
			ptr[1] = (BYTE)power_status();
			res = RES_OK;
			break;
		default :
			res = RES_PARERR;
		}
	}
	else {
		if (Stat & STA_NOINIT) return RES_NOTRDY;

		switch (ctrl) {
		case CTRL_SYNC :		/* Make sure that no pending write process. Do not remove this or written sector might not left updated. */
			if (select()) {
				deselect();
				res = RES_OK;
			}
			break;

		case GET_SECTOR_COUNT :	/* Get number of sectors on the disk (DWORD) */
			if ((send_cmd(CMD9, 0) == 0) && rcvr_datablock(csd, 16)) {
				if ((csd[0] >> 6) == 1) {	/* SDC ver 2.00 */
					csize = csd[9] + ((WORD)csd[8] << 8) + 1;
					*(DWORD*)buff = (DWORD)csize << 10;
				} else {					/* SDC ver 1.XX or MMC*/
					n = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
					csize = (csd[8] >> 6) + ((WORD)csd[7] << 2) + ((WORD)(csd[6] & 3) << 10) + 1;
					*(DWORD*)buff = (DWORD)csize << (n - 9);
				}
				res = RES_OK;
			}
			break;

		case GET_SECTOR_SIZE :	/* Get R/W sector size (WORD) */
			*(WORD*)buff = 512;
			res = RES_OK;
			break;

		case GET_BLOCK_SIZE :	/* Get erase block size in unit of sector (DWORD) */
			if (CardType & CT_SD2) {	/* SDv2? */
				if (send_cmd(ACMD13, 0) == 0) {	/* Read SD status */
					rcvr_spi();
					if (rcvr_datablock(csd, 16)) {				/* Read partial block */
						for (n = 64 - 16; n; n--) rcvr_spi();	/* Purge trailing data */
						*(DWORD*)buff = 16UL << (csd[10] >> 4);
						res = RES_OK;
					}
				}
			} else {					/* SDv1 or MMCv3 */
				if ((send_cmd(CMD9, 0) == 0) && rcvr_datablock(csd, 16)) {	/* Read CSD */
					if (CardType & CT_SD1) {	/* SDv1 */
						*(DWORD*)buff = (((csd[10] & 63) << 1) + ((WORD)(csd[11] & 128) >> 7) + 1) << ((csd[13] >> 6) - 1);
					} else {					/* MMCv3 */
						*(DWORD*)buff = ((WORD)((csd[10] & 124) >> 2) + 1) * (((csd[11] & 3) << 3) + ((csd[11] & 224) >> 5) + 1);
					}
					res = RES_OK;
				}
			}
			break;

		case MMC_GET_TYPE :		/* Get card type flags (1 byte) */
			*ptr = CardType;
			res = RES_OK;
			break;

		case MMC_GET_CSD :		/* Receive CSD as a data block (16 bytes) */
			if (send_cmd(CMD9, 0) == 0		/* READ_CSD */
				&& rcvr_datablock(ptr, 16))
				res = RES_OK;
			break;

		case MMC_GET_CID :		/* Receive CID as a data block (16 bytes) */
			if (send_cmd(CMD10, 0) == 0		/* READ_CID */
				&& rcvr_datablock(ptr, 16))
				res = RES_OK;
			break;

		case MMC_GET_OCR :		/* Receive OCR as an R3 resp (4 bytes) */
			if (send_cmd(CMD58, 0) == 0) {	/* READ_OCR */
				for (n = 4; n; n--) *ptr++ = rcvr_spi();
				res = RES_OK;
			}
			break;

		case MMC_GET_SDSTAT :	/* Receive SD statsu as a data block (64 bytes) */
			if (send_cmd(ACMD13, 0) == 0) {	/* SD_STATUS */
				rcvr_spi();
				if (rcvr_datablock(ptr, 64))
					res = RES_OK;
			}
			break;

		default:
			res = RES_PARERR;
		}

		deselect();
	}

	return res;
}



/*-----------------------------------------------------------------------*/
/* Device Timer Interrupt Procedure                                      */
/*-----------------------------------------------------------------------*/
/* This function must be called in period of 10ms                        */

void disk_timerproc (void)
{
	BYTE s;
	
	#ifndef USE_OS
  	if (Timer1) Timer1--;
  	if (Timer2) Timer2--;
  	#else
    if (Timer2) Timer2--;
	#endif
	
	Timer++;
	s = Stat;

	#ifdef SOCKWP
	if (SOCKWP)				      /* Write protected */
	{
		s |= STA_PROTECT;
	}
	else					          /* Write enabled */
	{
	  s &= ~STA_PROTECT;
	}
	#else
	  s &= ~STA_PROTECT;
	#endif

	if (SOCKINS)			      /* Card inserted */
		s &= ~STA_NODISK;
	else					          /* Socket empty */
		s |= (STA_NODISK | STA_NOINIT);

	Stat = s;				        /* Update MMC status */
}


/*****************************************************************************/
void SD_CLKDelay(INT8U u8Frames) 
{
    while(u8Frames--)
        xmit_spi(0xFF);
}


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////      Return Calendar Function                    /////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

void GetFatTimer(INT32U *time)
{
  UserEnterCritical();
  *time = Timer;
  UserExitCritical();
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////      Set Calendar Function                       /////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

void SetFatTimer(INT32U time)
{
  UserEnterCritical();
  Timer = time;
  UserExitCritical();
}


#if PLATAFORMA == COLDUINO

// Used for MSD class
#include "user_config.h"
#if (USB_CLASS_TYPE == BRTOS_USB_MSD)

/* Gobal Variables */
uint_8  vSD_CSD[16];        // SD card CSD vaule
uint_8  vSD_Bnum;           // Block number
uint_32 vSD_LBA;            // BLock address

T32_8 u32MaxBlocks;
T16_8 u16BlockSize;

T32_8 gu8SD_Argument;
uint_8 gu8SD_CID[16];


#define SD_SendCommand(x,y) send_cmd(x, gu8SD_Argument.lword)

/************************************************/
void SD_Write_Block(PTR_LBA_APP_STRUCT lba_data_ptr)
{
    uint_32 u32Counter;

    SD_CS=ENABLE;

    gu8SD_Argument.lword = lba_data_ptr->offset; 

    if(SD_SendCommand(CMD24|0x40,SD_OK))
    {
        SD_CS=DISABLE;
        return;   // Command IDLE fail
    }
    
    xmit_spi(0xFE);
    
    for(u32Counter=0;u32Counter<lba_data_ptr->size;u32Counter++)  
    {
    	xmit_spi(*(lba_data_ptr->buff_ptr + u32Counter));
    }

    xmit_spi(0xFF);    // checksum Bytes not needed
    xmit_spi(0xFF);

    
    if((rcvr_spi() & 0x0F) != 0x05)
    {
        SD_CS=DISABLE;
        return;     // Command fail
    }

    while(rcvr_spi()==0x00)
    {
        __RESET_WATCHDOG();
    }      // Dummy SPI cycle

    SD_CS=DISABLE;
    return;
}


/************************************************/
void SD_Read_Block(PTR_LBA_APP_STRUCT lba_data_ptr)
{
    uint_8 u8Temp=0;
    uint_32 u32Counter;

    SD_CS=ENABLE;

    gu8SD_Argument.lword = lba_data_ptr->offset; 

    if(SD_SendCommand(CMD17|0x40,SD_OK))
    {
        SD_CS=DISABLE;
        return; // Command IDLE fail
    }
    
    while(u8Temp!=0xFE)  
    {      
        u8Temp = rcvr_spi(); 
    }
    
    for(u32Counter=0;u32Counter<lba_data_ptr->size;u32Counter++)  
    {
        *(lba_data_ptr->buff_ptr + u32Counter) = rcvr_spi(); 
    }
        
    (void)rcvr_spi();  // Dummy SPI cycle
    (void)rcvr_spi();  // Dummy SPI cycle

    SD_CS=DISABLE;

    (void)rcvr_spi();  // Dummy SPI cycle
    
    return;
}


/*********************************************************
* Name: SD_ReadCSD
* Desc: Read CSD vaule of SD card
* Parameter: None
* Return: Status of read -- Fail:04  Success:00
**********************************************************/

uint_8 SD_ReadCSD(void)
{
    uint_8 i;
    
    SD_CS=ENABLE;

    if(SD_SendCommand(CMD9|0x40,SD_OK))
    {
        SD_CS=DISABLE;
        return(4);      
    }
    
    while(i!=0xFE)
        i=rcvr_spi();
    
    for(i=0;i<16;i++)
        vSD_CSD[i]=rcvr_spi();

    (void)rcvr_spi();  
    (void)rcvr_spi();  

    SD_CS=DISABLE;
    
    (void)rcvr_spi();  
    
    return(0);
}

/*********************************************************
* Name: SD_Card_Info
* Desc: Storage information of SD Card
* Parameter: None
* Return: None
**********************************************************/  
void SD_Card_Info(uint_32_ptr max_blocks_ptr, uint_32_ptr block_size_ptr) 
{
    uint_16 u16Temp;

   (void)SD_ReadCSD();
		
    // Block Size
    u16BlockSize.u16= (uint_16)(1<<(vSD_CSD[5] & 0x0F));

    // Max Blocks
    u16Temp= (uint_16)((vSD_CSD[10]&0x80)>>7);
    u16Temp+=(vSD_CSD[9]&0x03)<<1;
    u32MaxBlocks.lword= (uint_16)(vSD_CSD[6]&0x03);
    u32MaxBlocks.lword=u32MaxBlocks.lword<<8;
    u32MaxBlocks.lword+=vSD_CSD[7];
    u32MaxBlocks.lword=u32MaxBlocks.lword<<2;
    u32MaxBlocks.lword+=(vSD_CSD[8]&0xC0)>>6;
    u32MaxBlocks.lword++;
    u32MaxBlocks.lword=u32MaxBlocks.lword<<(u16Temp+2);
    
    // Patch for SD Cards of 2 GB
    if(u16BlockSize.u16 > 512)
    {
        u16BlockSize.u16=512;
        u32MaxBlocks.lword=u32MaxBlocks.lword<<1;
    }
    
    *max_blocks_ptr = u32MaxBlocks.lword;
    *block_size_ptr = (uint_32)u16BlockSize.u16;
}
#endif

#endif
