/**
* \file SPI.c
* \brief Serial peripheral interface (SPI) driver.
*
* This file contain the functions of the SPI driver, such as:
* initialize the SPI, send and receive a byte.
*
**/

#include "hardware.h"
#include "spi.h"
#include "BRTOS.h"

#if (ENABLE_SPI1 == TRUE)
INT8U SPI1Data = 0;
#endif

void init_SPI(INT8U spi)
{  
  /* ### Init_SPI init code */ 
 volatile char IOReg;
 
      // Configure SPI 1
      #if (ENABLE_SPI1 == TRUE)
      if (spi == 1) 
      {          
        // set PB2(MOSI), PB1(SCK) as output
        DDRB    = (1<<PB1)|(1<<PB2);
        // enable SPI in Master Mode with SCK = CK/4
        SPCR    = (1<<SPE)|(1<<MSTR);
		
        IOReg   = SPSR;                 	// clear SPIF bit in SPSR
        IOReg   = SPDR;
      }
      #endif      
     
  /* ### */
}

#if (ENABLE_SPI1 == TRUE)
// Função para enviar dados pela porta SPI
void SPI1_SendChar(INT8U data)
{
   SPDR  = data;          // send Character
   while (!(SPSR & (1<<SPIF)));    // wait until Char is sent 
   SPI1Data = SPDR;
}


INT8U SPI1_GetChar(void)
{
    SPI1_SendChar(0xFF);          
    return SPI1Data;
}

#endif
