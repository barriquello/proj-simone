#ifndef IIC_H
#define IIC_H

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "tipos.h"

#define IIC2_START() IIC2C1 |= IICC1_MST_MASK;
#define IIC2_STOP()  IIC2C1 &= ~IICC1_MST_MASK;

void IIC2_init (void);  
void IIC2_transmite (u08 end_escravo, u16 end_mem, u08 *dado);
void IIC2_recebe(u08 end_escravo,u08 *dado);

#endif
