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

#include "iic2.h"

#if 0
/* modo mestre */
void IIC2_init (void){   
    
    IIC2F = 0x1F | IIC2F_MULT0_MASK; // SCL divisor = 240, mul = 02
    IIC2C1 = 0x80; // habilita IIC
    IIC2C1 |= 0x18; // habilita Tx sem ACK automático
    (void) IIC2S ; // limpa flags
    //IIC2C1 |= 0x20; // IIC em modo mestre 
    (void) IIC2S ; // limpa flags

}

void IIC2_transmite (u08 end_escravo, u16 end_mem, u08 *dado){   
      
   IIC2_START();
  
   do{         
      IIC2D = (u08)(end_escravo); // Tx endereço do escravo - W
   }while (!IIC2S_TCF || IIC2S_RXAK); // aguarda completar Tx
         
   do{
      IIC2D = (u08)((end_mem) >> 8); // Tx dado
   } while (!IIC2S_TCF || IIC2S_RXAK);  // aguarda bit de ack
   
   do{
      IIC2D = (u08)(end_mem & 0xFF); // Tx dado
   } while (!IIC2S_TCF || IIC2S_RXAK);  // aguarda bit de ack
   
   if(dado != NULL) {     
     do{
        IIC2D = (*dado); // Tx dado
     } while (!IIC2S_TCF || IIC2S_RXAK); // aguarda bit de ack
   }else{
     //IIC2C1_RSTA = 1;  // repete start          
   }
   
   IIC2_STOP();
}


void IIC2_recebe(u08 end_escravo,u08 *dado){   

   do{    
      while (!IIC2S_TCF){} // aguarda completar Tx
      IIC2D = (u08)(end_escravo | 0x01); // Tx endereço do escravo - R
    } while(IIC2S_RXAK);  // aguarda bit de ack

 	IIC2C1_TX = 0; // modo Rx
	while (!IIC2S_TCF){} // aguarda completar Tx
	*dado = IIC2D; // Tx dado
  IIC2C1_TX = 1; // modo Tx
}
#endif
