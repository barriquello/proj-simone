/******************************************************************************
*                                                  
*  (c) copyright Freescale Semiconductor 2008
*  ALL RIGHTS RESERVED
*
*  File Name:   SD.h
*                                                                          
*  Description: Header File for SD using SPI Driver 
*                                                                                     
*  Assembler:   Codewarrior for HC(S)08 V6.1
*                                            
*  Version:     1.0                                                         
*                                                                                                                                                         
*  Author:      Jose Ruiz (SSE Americas)
*                                                                                       
*  Location:    Guadalajara,Mexico                                              
*                                                                                                                  
*                                                  
* UPDATED HISTORY:
*
* REV   YYYY.MM.DD  AUTHOR        DESCRIPTION OF CHANGE
* ---   ----------  ------        --------------------- 
* 1.0   2008.02.18  Jose Ruiz     Initial version
* 
*/


#ifndef __SD__
#define __SD__

/* Includes */
#include "AppConfig.h"
#include "OS_types.h"
#include "diskio.h"

#if COLDUINO
#include "types.h"
#else
#include "stdint.h"
#endif
//#include "usb_msc.h"


/* User definitions */
#define USE_OS          1
#define SD_BLOCK_512     
#define SD_WAIT_CYCLES 30

/* Definitions */
#define   _OUT       1
#define   _IN        0

/* Standard Definitions */
#ifdef  SD_BLOCK_512
    #define SD_BLOCK_SIZE   (0x00000200)
    #define SD_BLOCK_SHIFT  (9)
    #define BLOCK_SIZE      512
#endif

/* TypeDefs */
typedef union
{
	uint8_t  bytes[4];
	uint32_t lword;		
}T32_8;

typedef union
{
	uint8_t  u8[2];
	uint16_t u16;		
}T16_8;


#if COLDUINO
#define SD_CARD_PORT	1
/* SD card Inserted detection Pin */
#define SD_CS    PTAD_PTAD0      /* Slave Select 1 */
#define _SD_CS   PTADD_PTADD0

#define SD_AUSENT        (PTBD_PTBD7)
#define _SD_AUSENT       PTBDD_PTBDD7
#define SD_AUSENT_PULLUP PTBPE_PTBPE7

#define SD_WP			  PTBD_PTBD6
#define _SD_WP			  PTBDD_PTBDD6
#define SD_WP_PULLUP	  PTBPE_PTBPE6

#define	FCLK_SLOW()	  SCGC2  |= SCGC2_SPI1_MASK;        /* Enables spi1 clock */			\
(void)SPI1S;                      /* Read the status register */		\
(void)SPI1D;                      /* Read the device register */		\
SPI1BR = 0x10; 					/* 196 Khz with 24 MHz busclock */ 	\
SPI1C2 = 0x00;                                      					\
SPI1C1 = SPI1C1_SPE_MASK | SPI1C1_MSTR_MASK

#define	FCLK_FAST()	  SPI1BR = 0x00

#else

/* SD card Inserted detection Pin */
#define SD_CS        dummy  /* Slave Select 1 */
#define _SD_CS		  

#define SD_AUSENT       1 
#define _SD_AUSENT       
#define SD_AUSENT_PULLUP  

#define SD_WP			  
#define _SD_WP			  
#define SD_WP_PULLUP	  

#define	FCLK_SLOW()	 
#define	FCLK_FAST()	  

#endif

#define SD_PRESENT 		(!SD_AUSENT)

#define ENABLE    0
#define DISABLE   1

/* Port Controls  (Platform dependent) */
#if SD_CARD_PORT
#define CS_LOW()	SD_CS = 0			/* MMC CS = L */
#define	CS_HIGH()	SD_CS = 1			/* MMC CS = H */
#define SOCKWP	    SD_WP	            /* Write protected. yes:true, no:false, default:false */
#define SOCKINS		(!SD_AUSENT)	        /* Card detected.   yes:true, no:false, default:true */
#else
#define CS_LOW()				/* MMC CS = L */
#define	CS_HIGH()				/* MMC CS = H */
//#define SOCKWP	    	        /* Write protected. yes:true, no:false, default:false */
#define SOCKINS			      0  /* Card detected.   yes:true, no:false, default:true */
#endif

/* Error Codes */
enum
{
	SD_OK,
	COMMAND_FAILS,
	INIT_FAILS,
	WRITE_COMMAND_FAILS,
	WRITE_DATA_FAILS,
	READ_COMMAND_FAILS,
	READ_DATA_FAILS,
	NO_SD_CARD,
	INIT_SD_FAILS,
	MOUNT_SD_FAILS
};


/* Static Definitions */
/******************************* SD Card Standard Commands **********************************/
#define CMD0	(0)			/* GO_IDLE_STATE */
#define CMD1	(1)			/* SEND_OP_COND (MMC) */
#define	ACMD41	(0x80+41)	/* SEND_OP_COND (SDC) */
#define CMD8	(8)			/* SEND_IF_COND */
#define CMD9	(9)			/* SEND_CSD */
#define CMD10	(10)		/* SEND_CID */
#define CMD12	(12)		/* STOP_TRANSMISSION */
#define ACMD13	(0x80+13)	/* SD_STATUS (SDC) */
#define CMD16	(16)		/* SET_BLOCKLEN */
#define CMD17	(17)		/* READ_SINGLE_BLOCK */
#define CMD18	(18)		/* READ_MULTIPLE_BLOCK */
#define CMD23	(23)		/* SET_BLOCK_COUNT (MMC) */
#define	ACMD23	(0x80+23)	/* SET_WR_BLK_ERASE_COUNT (SDC) */
#define CMD24	(24)		/* WRITE_BLOCK */
#define CMD25	(25)		/* WRITE_MULTIPLE_BLOCK */
#define CMD32	(32)		/* ERASE_ER_BLK_START */
#define CMD33	(33)		/* ERASE_ER_BLK_END */
#define CMD38	(38)		/* ERASE */
#define CMD55	(55)		/* APP_CMD */
#define CMD58	(58)		/* READ_OCR */

/* Card type flags (CardType) */
#define CT_MMC		0x01		/* MMC ver 3 */
#define CT_SD1		0x02		/* SD ver 1 */
#define CT_SD2		0x04		/* SD ver 2 */
#define CT_SDC		(CT_SD1|CT_SD2)	/* SD */
#define CT_BLOCK	0x08		/* Block addressing */ 

/* FatFS Prototypes */
void disk_timerproc (void);
void SD_CLKDelay(INT8U);
INT8U GetCardType(void);
INT8U GetCardStat(void);
INT8U GetCardInit(void);
void SetCardStat(INT8U state);
void GetFatTimer(INT32U *time);
void SetFatTimer(INT32U time);
DWORD get_fattime (void);
void xmit_spi(INT8U dat);

#if (USB_CLASS_TYPE == BRTOS_USB_MSD)
#if 0
void SD_Write_Block(PTR_LBA_APP_STRUCT lba_data_ptr);
void SD_Read_Block(PTR_LBA_APP_STRUCT lba_data_ptr);
uint_8 SD_ReadCSD(void);
void SD_Card_Info(uint_32_ptr max_blocks_ptr, uint_32_ptr block_size_ptr);
#endif
#endif

#endif /* __SD__ */
