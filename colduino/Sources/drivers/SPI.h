/**
* \file SPI.h
* \brief Serial peripheral interface driver function prototypes.
*
*
**/

#define ENABLE_SPI1   TRUE
#define ENABLE_SPI2   FALSE

void init_SPI(unsigned char spi);


#if (ENABLE_SPI1 == TRUE)
extern void SPI1_SendChar(unsigned char data);
extern unsigned char SPI1_GetChar(void);
#endif


#if (ENABLE_SPI2 == TRUE)
extern void SPI2_SendChar(unsigned char data);
extern unsigned char SPI2_GetChar(void);
#endif

