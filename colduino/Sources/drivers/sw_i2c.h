# ifndef _SW_I2C_H
# define _SW_I2C_H

/*************************************/
/* sw_i2c.h                          */
/*************************************/

#define NO_I2C_ACK 0
#define OK_I2C_ACK 1
/*************************/
/* Init the ports and the*/
/*  bus                  */
/*************************/
void sw_i2c_init(void);

/*************************/
/* Start Data Transfer   */
/*************************/
void sw_i2c_start(void);

/*************************/
/* Stop  Transfer        */
/*************************/
void sw_i2c_stop(void);

/*************************/
/* Write  Transfer       */
/*************************/
unsigned char sw_i2c_write(char);     // char caracter a escribir
                         // retorna OK_I2C_ACK (1) si ha habido ack
                         // retorna NO_I2C_ACK (0) si no ha habido ack

/*************************/
/* Read  Transfer        */
/*************************/
char  sw_i2c_read(unsigned char);    // Retorna el caracter leido
                           // si el aargumento, hace ack

#endif
