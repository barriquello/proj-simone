/*************************************/
/* Antonio  Alvarez                  */
/* March-2004                        */
/* i2c.c                             */
/* I2c bus acces from MSP430f149 in  */
/* the Olmex EasyWeb" Board          */
/* Functions defined in this file:   */
/*    i2cInit ()                     */
/*    i2cStart()                     */
/*    i2cStop ()                     */
/*    i2cRead ()                     */
/*    i2cWrite()                     */
/* Functions internal to this file   */
/*    SetLowSDA ()                   */
/*    SetLowSCL ()                   */
/*    SetHighSDA()                   */
/*    SetHighSCL()                   */
/*************************************/

#include "derivative.h"
#include "sw_i2c.h"

#define SDA         PTFD_PTFD4_MASK  // Bit uno  Datos:  Serial Data Line      ; usar ptf4
#define SCL         PTFD_PTFD3_MASK  // Bit dos  Reloj: Serial Clock Line     	; usar ptf3
#define PORTAI2C    PTFD
#define PORTAI2CDIR PTFDD
//#define PORTAI2CSEL 
#define PORTAI2CIN  PTFD

/******************************************************************************/
/*                                                                            */
/* Acceso al Puerto                                                           */
/*     PxSEL   Indica el modo del puerto                                      */
/*           0  como I/O                                                      */
/*           1  como la otra funcionalidad                                    */
/*     PxDIR   Indica la direccion                                            */
/*           0  como Entrada                                                  */
/*           1  como salida                                                   */
/*     PxOUT   Indica el valor de salida                                      */
/*           0  salida baja                                                   */
/*           1  salida alta                                                   */
/*     PxIN    Indica el valor de entrada                                     */
/******************************************************************************/

/*************************/
static void delay_i2c(unsigned int time_end)
{
	volatile unsigned int timeout_counter = 0x00;
	while (timeout_counter < time_end)
		timeout_counter++;
}

#define I2C_HIGHLOW_TIME  100  

#ifdef I2C_HIGHLOW_TIME
#define	DELAY_I2C()    delay_i2c(I2C_HIGHLOW_TIME)
#else
#define	DELAY_I2C() 
#endif

static void SetLowSDA()
{
	PORTAI2C &= ~SDA;		
	PORTAI2CDIR |= SDA;           // SDA Salida
	DELAY_I2C();
}
static void SetHighSDA()
{
	PORTAI2CDIR &= ~SDA;         //SDA Entrada
	DELAY_I2C();
}

static void SetLowSCL()
{
	PORTAI2C &= ~SCL;
	DELAY_I2C();
}
static void SetHighSCL()
{
	PORTAI2C |= SCL;
	DELAY_I2C();
}
/*************************/
/* Inicializar las lineas*/
/* y el bus              */
/*************************/

void sw_i2c_init(void)
{

#ifdef   PORTAI2CSEL 
	PORTAI2CSEL &= ~SDA;
	PORTAI2CSEL &= ~SCL; // Funcion I/O para SDA Y SCL
#endif

	PORTAI2C &= ~SCL;   // Salida a cero
	PORTAI2C &= ~SDA;   // SDA  Open Colector

	PORTAI2CDIR |= SCL;    // SCL COMO SALIDA
	PORTAI2CDIR &= ~SDA;    // SDA COMO ENTRADA

	SetHighSCL();
	SetLowSDA(); // visto en el analizador logico como un pulso de
	SetHighSDA(); // 5 a 3.56 microsegundos aprox .

	// Ambas lineas quedan en alto
}

/*************************/
/* Start Data Transfer   */
/*************************/
void sw_i2c_start(void)
{

	/*
	 *  Mudar SDA de high pra low com SCL em high
	 * 
	 */

	SetHighSCL();
	SetHighSDA();

	SetHighSCL();
	SetLowSDA();

	SetLowSCL();
	SetHighSDA();

	/* Visto en el analizador lógico como:
	 *  SCL ------------------_________________ 
	 *  SDA -----____________________---------
	 *          0           2.7      5.5    microsegundos
	 */
}
/*************************/
/* Stop  Transfer        */
/*************************/
void sw_i2c_stop(void)
{
	/*
	 *  Mudar SDA de low pra high com SCL em high
	 * 
	 */
	SetLowSCL();
	SetLowSDA();

	SetHighSCL();
	SetLowSDA();

	SetHighSCL();
	SetHighSDA();
}

/*************************/
/* Write  Transfer       */
/*************************/
unsigned char sw_i2c_write(char i2c_data)
{

	unsigned char i;
	static unsigned char retorno;

	for (i = 0; i < 8; i++)
	{
		SetLowSCL(); // so pode mudar linha SDA com clk em nivel baixo

		if (i2c_data & 0x80)          // Primero el bit mas significativo
			SetHighSDA();
		else
			SetLowSDA();

		SetHighSCL();
		i2c_data <<= 1;
	}
	SetLowSCL();

	/* ack Read */
	SetHighSDA();

	SetHighSCL();
	
	if (PORTAI2CIN & SDA)
	{
			retorno = NO_I2C_ACK;      // el slave no ha bajado la linea
	}else
	{
			retorno = OK_I2C_ACK;
	}
	
	SetLowSCL();	
	return (retorno);
}
/*************************/
/* Read  Transfer        */
/*************************/
char sw_i2c_read(unsigned char ack)
{
	int i;
	char caracter = 0x00;

	SetLowSCL();
	SetHighSDA();

	for (i = 0; i < 8; i++)
	{
		caracter = caracter << 1;
		SetHighSCL();
		if (PORTAI2CIN & SDA)
			caracter = caracter + 1;
		SetLowSCL();
	}

	if (ack)
	{                         //Send ACK to sender 
		SetLowSDA();
	}
	SetHighSCL();
	SetLowSCL();

	return (caracter);
}
