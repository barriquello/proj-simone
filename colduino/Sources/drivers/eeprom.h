/*! \file eeprom.h
 \brief Interface para ler/escrever na memoria eeprom.
 
 Funcoes de leitura e escrita sao feitas por IIC.
 */


/** \addtogroup iccGroup
 *  @{
 */

# ifndef _EEPROM_H
# define _EEPROM_H

#include "tipos.h"

/*! \def WRITE_CYCLE_TIME
 \brief EEPROM requer 10ms para ser escrita.
 
 \def EEPROMAddress
 \brief Endereco do dispositivo EEPROM (escravo)
 */

#define EEPROMAddress    0xA0
#define WRITE_CYCLE_TIME     10 //ms
/*! \fn void EEPROM_ByteWrite(unsigned int endr, char dado)
 \brief Escreve na EEPROM
 \param endr Endereco a ser escrito
 \param dado Valor a ser escrito em endr
 
 \fn char EEPROM_RandomRead(unsigned int endr)
 \brief Leitura aleatoria na EEPROM
 \param endr Endereco a ser lido
 \return Valor lido no endereco endr
 
 \fn char EEPROM_CurrentAddressRead(void)
 \brief Leitura na EEPROM
 \return Valor lido no ultimo endereco de memoria acessado
 
 \fn void EEPROM_Init(void)
 \brief Configura os pinos para o protocolo IIC.
 
 */
void EEPROM_ByteWrite(u16 endr, u08 dado);

u08 EEPROM_RandomRead(u16 endr);

u08 EEPROM_CurrentAddressRead(void);

void EEPROM_AckPolling(void);

void EEPROM_Init(void);

#endif

/** @}*/
