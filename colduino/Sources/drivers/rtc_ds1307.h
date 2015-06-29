/*! \file rtc_ds1307.h
 \brief Rotinas para ler e escrever dados no DS1307.
 
 Funcoes de leitura/escrita sao feitas via IIC
 */

/** \addtogroup iccGroup
 *  @{
 */

# ifndef _RTC_DS1307_H
# define _RTC_DS1307_H

#include "BRTOS.h"

/*! \def DS1307Address
 \brief Endereco do DS1307 (escravo).
 */

#define DS1307Address 0xD0

/*! \fn void RTC_ByteWrite(INT8U Address, INT8U Data)
 \brief Escreve Data em Address
 \param Data Valor a ser gravado
 \param Address Endereco a ser gravado
 
 \fn INT8U RTC_RandomRead(INT8U Address)
 \brief Leitura aleatoria no DS1307
 \param Address Endereco a ser lido
 \return Valor lido no endereco Address
 
 \fn INT8U RTC_CurrentAddressRead(void)
 \brief Leitura no DS1307
 \return Valor lido no ultimo endereco de memoria acessado
 
 \fn void RTC_DS1307_Init(void)
 \brief Configura os pinos para o protocolo IIC.
 */

void RTC_ByteWrite(INT8U Address, INT8U Data);

INT8U RTC_CurrentAddressRead(void);

INT8U RTC_RandomRead(INT8U Address);

void RTC_AckPolling(void);

INT8U RTC_DS1307_Init(void);

#endif
/** @}*/
