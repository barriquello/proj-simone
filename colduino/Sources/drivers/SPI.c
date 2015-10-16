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
#include "utils.h"

#if !__GNUC__
#pragma warn_implicitconv off
#endif


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

        /* SPI System Enable */
#if __GNUC__
        BITSETMASK(SPI1C1,SPI1C1_SPE_MASK);
#else
        SPI1C1_SPE = 1;
#endif
        
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

#if __GNUC__
        BITSETMASK(SPI2C1,SPI2C1_SPE_MASK);
#else
        SPI2C1_SPE = 1;
#endif
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
	/* wait until transmit buffer is empty*/
	#if __GNUC__
		 while (!(BITTESTMASK(SPI1S,SPI1S_SPTEF_MASK))){};
	#else
		 while (!SPI1S_SPTEF){};
	#endif

  
  (void)SPI1S;
  SPI1D = data;                         /* Transmit counter*/ 
  
  	/* wait until receive buffer is full*/
	#if __GNUC__
		 while (!(BITTESTMASK(SPI1S,SPI1S_SPRF_MASK))){};
	#else
		 while (!SPI1S_SPRF){};
	#endif

    
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
	/* wait until transmit buffer is empty*/
	#if __GNUC__
		 while (!(BITTESTMASK(SPI2S,SPI2S_SPTEF_MASK))){};
	#else
		 while (!SPI2S_SPTEF){};
	#endif
  
  (void)SPI2S;
  SPI2D = data;                         /* Transmit counter*/ 
  
	/* wait until receive buffer is full*/
	#if __GNUC__
		 while (!(BITTESTMASK(SPI2S,SPI2S_SPRF_MASK))){};
	#else
		 while (!SPI2S_SPRF){};
	#endif
    
  (void)SPI2S;                          // Acknowledge flag
  SPI2Data = SPI2D;                     // Acknowledge flag  
}


INT8U SPI2_GetChar(void)
{
    SPI2_SendChar(0xFF);
          
    return SPI2Data;
}

#endif
