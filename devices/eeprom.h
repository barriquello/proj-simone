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
