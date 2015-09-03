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
        
      }
      #endif
      
      // Configure SPI 2
      #if (ENABLE_SPI2 == TRUE)
      if (spi == 2) 
      {  

      }
      #endif      
  }
  /* ### */
}



#if (ENABLE_SPI1 == TRUE)
// Função para enviar dados pela porta SPI
void SPI1_SendChar(INT8U data)
{
  
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
  
}


INT8U SPI2_GetChar(void)
{
    SPI2_SendChar(0xFF);
          
    return SPI2Data;
}

#endif
