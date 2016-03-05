/* The License
 * 
 * Copyright (c) 2015 Universidade Federal de Santa Maria
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.

*/

/*! \file SD.h
 \brief Interface para ler/escrever dados no SD.
 
 Funcoes de leitura e escrita sao feitas por SPI.
 */


/*! \defgroup Devices SD*/

/** \addtogroup Devices
 *  @{
 */
 
 
#ifndef __SD__
#define __SD__


/* Includes */
#include "AppConfig.h"
#include "OS_types.h"
#include "diskio.h"
#include "utils.h"

#if COLDUINO
#include "types.h"
#else
#include "stdint.h"
#endif


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
	#define SD_CARD_PORT		1
	#define SD_CARD_DETECTION	1

	#if !__GNUC__
	/* SD card Inserted detection Pin */
	#define SD_CS    PTAD_PTAD0      /* Slave Select 1 */
	#define _SD_CS   PTADD_PTADD0

	#define SD_AUSENT        (PTBD_PTBD7)
	#define _SD_AUSENT       PTBDD_PTBDD7
	#define SD_AUSENT_PULLUP PTBPE_PTBPE7

	#define SD_WP			  PTBD_PTBD6
	#define _SD_WP			  PTBDD_PTBDD6
	#define SD_WP_PULLUP	  PTBPE_PTBPE6

	#else
	#define SD_SELECT()		  		BITTEST(PTAD,0)
	#define SD_SELECT_DIR_OUT() 	BITSET(PTADD,0)
	#define SD_SELECT_ENABLE()		BITCLEAR(PTAD,0)
	#define SD_SELECT_DISABLE()		BITSET(PTAD,0)
	#define IS_SD_AUSENT()	  		BITTEST(PTBD,7)
	#define SD_AUSENT_DIR_OUT()		BITSET(PTBDD,7)
	#define SD_AUSENT_PUP()	  		BITSET(PTBPE,7)
	#define IS_SD_WP()		  		BITTEST(PTBD,6)
	#define SD_WP_DIR_IN()      	BITCLEAR(PTBDD,6)
	#define SD_WP_PUP()	  	  		BITSET(PTBPE,6)

	#define SD_AUSENT 			IS_SD_AUSENT()
	#endif

	#define	FCLK_SLOW()	  SCGC2  |= SCGC2_SPI1_MASK;        /* Enables spi1 clock */			\
	(void)SPI1S;                      /* Read the status register */		\
	(void)SPI1D;                      /* Read the device register */		\
	SPI1BR = 0x10; 					/* 196 Khz with 24 MHz busclock */ 	\
	SPI1C2 = 0x00;                                      					\
	SPI1C1 = SPI1C1_SPE_MASK | SPI1C1_MSTR_MASK

	#define	FCLK_FAST()	  SPI1BR = 0x00
#elif ARDUINO
	#define SD_CARD_PORT		1
	#define SD_CARD_DETECTION	0
	#define IS_SD_AUSENT()	  	FALSE
	
	/* port for arduino mega 2560 - shield SD - CS pin PG5 */
	#define SD_SELECT_PORT_DATA		PORTG
	#define SD_SELECT_PORT_DIR      DDRG
	#define SD_SELECT_PIN           5
	#define SD_SELECT()		  		BITTEST(SD_SELECT_PORT_DATA,SD_SELECT_PIN)
	#define SD_SELECT_DIR_OUT() 	BITSET(SD_SELECT_PORT_DIR,SD_SELECT_PIN)
	#define SD_SELECT_ENABLE()		BITCLEAR(SD_SELECT_PORT_DATA,SD_SELECT_PIN)
	#define SD_SELECT_DISABLE()		BITSET(SD_SELECT_PORT_DATA,SD_SELECT_PIN)

	#define SD_AUSENT 				0

	#define	FCLK_SLOW()	   DDRB = (1<<PB0)| (1<<PB1)|(1<<PB2); SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0); SPSR &= ~(1 << SPI2X); (void)SPDR; (void)SPSR;
	#define	FCLK_FAST()	   SPCR	= SPCR & ~(0b11); (void)SPDR; (void)SPSR;
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

#if __GNUC__
#define SD_PRESENT 		(!(IS_SD_AUSENT()))
#else
#define SD_PRESENT 		(!SD_AUSENT)
#endif

#define ENABLE    0
#define DISABLE   1

/* Port Controls  (Platform dependent) */
#if COLDUINO
	#if __GNUC__
		#define CS_LOW()   SD_SELECT_ENABLE()
		#define	CS_HIGH()  SD_SELECT_DISABLE()
		#define SOCKWP	   IS_SD_WP()
		#define SOCKINS    (!(IS_SD_AUSENT()))
	#else
		#define CS_LOW()	SD_CS = 0			/* MMC CS = L */
		#define	CS_HIGH()	SD_CS = 1			/* MMC CS = H */
		#define SOCKWP	    SD_WP	            /* Write protected. yes:true, no:false, default:false */
		#define SOCKINS		(!SD_AUSENT)	        /* Card detected.   yes:true, no:false, default:true */
	#endif
#elif ARDUINO
	#define CS_LOW()				SD_SELECT_ENABLE()
	#define	CS_HIGH()				SD_SELECT_DISABLE()
	//#define SOCKWP	    	        /* Write protected. yes:true, no:false, default:false */
	#define SOCKINS			      TRUE		/* Card detected.   yes:true, no:false, default:true */
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
/** @}*/
