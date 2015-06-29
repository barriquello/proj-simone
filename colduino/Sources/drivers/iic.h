/*! \file iic.h
 \brief Protocolo IIC.
 
 Implementacao do protocolo IIC para o MCF51JE256RM.
 */


/*! \defgroup iccGroup DS1307, EEPROM and IIC*/
/** \addtogroup iccGroup
 *  @{
 */

#ifndef IIC_H_
#define IIC_H_

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "tipos.h"

/*! \def IIC_START()
 \brief Habilita modo mestre.
 
 \def IIC_STOP()
 \brief Habilita modo escravo.
 
 */

#define IIC_START() IICC1 |= IICC1_MST_MASK;
#define IIC_STOP()  IICC1 &= ~IICC1_MST_MASK;

/*! \fn void IIC_init(void)
 \brief Configura pinos para a comunicacao IIC.

 \fn void IIC_transmite(u08 end_escravo, u16 end_mem, u08 *dado)
 \brief Escreve dado em end_mem.
 \param end_escravo Endereco do escravo
 \param end_mem Endereco de memoria a ser escrito
 \param dado Dado a ser gravado em end_mem

 \fn void IIC_recebe(u08 end_escravo, u08 *dado)
 \brief Le dado do ultimo endereco acessado pelo dispositivo escravo.
 \param end_escravo Endereco do periferico escravo
 \param dado Dado a ser lido
 */

void IIC_init(void);
void IIC_transmite(u08 end_escravo, u16 end_mem, u08 *dado);
void IIC_recebe(u08 end_escravo, u08 *dado);

#endif /* IIC_H_ */

/** @}*/
