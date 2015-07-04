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

#pragma warn_implicitconv off


#if (ENABLE_SPI1 == TRUE)
INT8U SPI1Data = 0;
#endif

#if (ENABLE_SPI2 == TRUE)
INT8U SPI2Data = 0;
#endif


void init_SPI(INT8U spi)
{  
  /* ### Init_SPI init code */
  
  if ((spi == 1) || (spi == 2)) 
  {
      // Configure SPI 1
      #if (ENABLE_SPI1 == TRUE)
      if (spi == 1) 
      {  
        SCGC2  |= SCGC2_SPI1_MASK;           /* Enables spi1 clock */
        (void)SPI1S;                         /* Read the status register */
        (void)SPI1D;                         /* Read the device register */
        /* SPI1C1: SPIE=0,SPE=0,SPTIE=0,MSTR=0,CPOL=0,CPHA=1,SSOE=0,LSBFE=0 */
        SPI1C1 = 0x00;                       /* The SPRF interrupt flag is cleared when the SPI1 module is disabled. */
        
        /* SPI1C2: MODFEN=0,BIDIROE=0,SPISWAI=0,SPC0=0 */
        // Modo bidirecional single-wire desativado
        SPI1C2 = 0x00;                                      
        
        /* SPI1BR: SPPR2=0,SPPR1=0,SPPR0=1,SPR2=0,SPR1=0,SPR0=0 */
        // Configura o clock da porta SPI p/ 6 Mhz --> 24Mhz / 2*2
        SPI1BR = 0x10;
                                              
        (void)(SPI1S == 0);                  /* Dummy read of the SPI1S registr to clear the MODF flag */
        
        /* SPI1C1: SPIE=0,SPE=0,SPTIE=0,MSTR=1,CPOL=0,CPHA=0,SSOE=0,LSBFE=0 */
        SPI1C1 = 0x10;
        SPI1C1_SPE = 1;
        
        (void)SPI1S;  
      }
      #endif
      
      // Configure SPI 2
      #if (ENABLE_SPI2 == TRUE)
      if (spi == 2) 
      {  
        SCGC2  |= SCGC2_SPI2_MASK;           /* Enables spi2 clock */
        (void)SPI2S;                         /* Read the status register */
        (void)SPI2D;                         /* Read the device register */
        /* SPI1C1: SPIE=0,SPE=0,SPTIE=0,MSTR=0,CPOL=0,CPHA=1,SSOE=0,LSBFE=0 */
        SPI2C1 = 0x00;                       /* The SPRF interrupt flag is cleared when the SPI1 module is disabled. */
        
        /* SPI1C2: MODFEN=0,BIDIROE=0,SPISWAI=0,SPC0=0 */
        // Modo bidirecional single-wire desativado
        SPI2C2 = 0x00;                                      
        
        /* SPI1BR: SPPR2=0,SPPR1=0,SPPR0=1,SPR2=0,SPR1=0,SPR0=0 */
        // Configura o clock da porta SPI p/ 6 Mhz --> 24Mhz / 2*2
        SPI2BR = 0x10;
                                              
        (void)(SPI2S == 0);                  /* Dummy read of the SPI1S registr to clear the MODF flag */
        
        /* SPI1C1: SPIE=0,SPE=0,SPTIE=0,MSTR=1,CPOL=0,CPHA=0,SSOE=0,LSBFE=0 */
        SPI2C1 = 0x10;
        SPI2C1_SPE = 1;
        
        (void)SPI2S;  
      }
      #endif      
  }
  /* ### */
}



#if (ENABLE_SPI1 == TRUE)
// Função para enviar dados pela porta SPI
void SPI1_SendChar(INT8U data)
{
  while (!SPI1S_SPTEF){};               /* wait until transmit buffer is empty*/
  
  (void)SPI1S;
  SPI1D = data;                         /* Transmit counter*/ 
  
  while (!SPI1S_SPRF){};                  /* wait until receive buffer is full*/
    
  (void)SPI1S;                            // Acknowledge flag
  SPI1Data = SPI1D;                        // Acknowledge flag  
}


INT8U SPI1_GetChar(void)
{
    SPI1_SendChar(0xFF);          
    return SPI1Data;
}

#endif


#if (ENABLE_SPI2 == TRUE)
// Função para enviar dados pela porta SPI
void SPI2_SendChar(INT8U data)
{
  while (!SPI2S_SPTEF){};               /* wait until transmit buffer is empty*/
  
  (void)SPI2S;
  SPI2D = data;                         /* Transmit counter*/ 
  
  while (!SPI2S_SPRF){};                /* wait until receive buffer is full*/
    
  (void)SPI2S;                          // Acknowledge flag
  SPI2Data = SPI2D;                     // Acknowledge flag  
}


INT8U SPI2_GetChar(void)
{
    SPI2_SendChar(0xFF);
          
    return SPI2Data;
}

#endif
