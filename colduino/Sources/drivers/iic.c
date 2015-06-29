#include "iic.h"
#include "BRTOS.h"
/* modo mestre */
void IIC_init(void)
{
	SOPT3 |= SOPT3_IICPS_MASK; //SDA = PTF4, SCL = PTF3 (bit IICPS)

	/*
	 IIC Clock Gate Control — This bit controls the clock gate to the IIC1 module.
	 0 Bus clock to the IIC module is disabled.
	 1 Bus clock to the IIC module is enabled.
	 */

	SCGC1 |= SCGC1_IIC_MASK;

	IICF = ((0x01) << 6) | 0x1F; // SCL divisor = 240 (0x1F), mul = 01 => bus clock / 2 => 50kHz
	IICC1 = IICC1_IICEN_MASK; // habilita IIC
	IICC1 |= IICC1_TX_MASK | IICC1_TXAK_MASK; // habilita Tx sem ACK automático
	(void) IICS; // limpa flags
	IICC1 |= IICC1_MST_MASK; // IIC em modo mestre 
	(void) IICS; // limpa flags

}

#define DELAY_MS           1
#define IIC_DELAY()  	   DelayTask(DELAY_MS)
#define IIC_DELAY_WRITE()  DelayTask(DELAY_MS*10)

void IIC_transmite(u08 end_escravo, u16 end_mem, u08 *dado)
{
		
	IIC_START()

	//IIC_DELAY();

	do
	{
		IICD = (u08) (end_escravo); // Tx endereço do escravo - W
	} while (!IICS_TCF || IICS_RXAK); // aguarda completar Tx

	IIC_DELAY();	

	do
	{
		IICD = (u08) ((end_mem) >> 8); // Tx dado
	} while (!IICS_TCF || IICS_RXAK);  // aguarda bit de ack

	IIC_DELAY();
	

	do
	{
		IICD = (u08) (end_mem & 0xFF); // Tx dado
	} while (!IICS_TCF || IICS_RXAK);  // aguarda bit de ack

	IIC_DELAY();

	if (dado != NULL)
	{
		do
		{
			IICD = (*dado); // Tx dado
		} while (!IICS_TCF || IICS_RXAK); // aguarda bit de ack
		
		IIC_DELAY();	
		
		IIC_STOP();
		
		IIC_DELAY_WRITE();
	}
	else
	{
		//IICC1 |= IICC1_RSTA_MASK;  // repete start   
		//IIC_DELAY();		
		
		//IIC_STOP();
		
		//IIC_DELAY_WRITE();
	}
}

void IIC_recebe(u08 end_escravo, u08 *dado)
{
	IICC1_TX = 1; // modo Tx

	do
	{
		while (!IICS_TCF)
		{
		} // aguarda completar Tx
		IICD = (u08) (end_escravo | 0x01); // Tx endereço do escravo - R
	} while (IICS_RXAK);  // aguarda bit de ack

	//IIC_DELAY();
	IICC1_TX = 0; // modo Rx
	while (!IICS_TCF)
	{
	} // aguarda completar Tx
	*dado = IICD; // Tx dado
	IICC1_TX = 1; // modo Tx
}


