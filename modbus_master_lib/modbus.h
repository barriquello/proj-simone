/******************************************************************************/
/* modbus.h                                                                   */
/*                                                                            */
/* Based on "libmodbus-2.0.3" - Unix\Win version                              */
/* Author: Stephane Raimbault <stephane.raimbault@gmail.com>                  */
/*                                                                            */
/* Modifed for embedded system 02.2011 Sergei Maslyakov <rusoil.9@gmail.com>  */
/******************************************************************************/


#ifndef __MODBUS_H
#define __MODBUS_H

#include "data_types.h"
#include "modbus_def.h"


/********************** Prototypes struct for MB_MASTER ***********************/
typedef enum
{
    eMB_PARS_SLAVE_ADDR = 0,
    eMB_PARS_FUNC,
    eMB_PARS_DATA
} __MB_PARS_ANSW;


typedef struct
{
    uint16_t  addr;
    uint16_t  value;
    uint8_t * pData;
} __MB_QUERY_BUILD;

typedef struct
{
    uint8_t * pAnsw;
    uint32_t  answLen;
    uint8_t   errCode;
} __MB_ANSW_READY_DATA;


typedef struct
{
    __MB_ANSW_READY_DATA answ;
    __MB_QUERY_BUILD     query;
} __MB_QUERY_SEND;


typedef struct // 4-byte aligned
{
    uint32_t  state;
	uint8_t   slave;
    uint8_t   func;
    uint8_t   expectedLen;
    uint8_t   queryLen;
    uint8_t * pQuery;
} __MB_QUERY;


/** MODBUS uses a ‘big-Endian’  
 * Ex.: 16-bits 0x1234 the first byte sent is 0x12 then 0x34*/


/**************************** Func declarations *******************************/
//sint32_t ModbusMaster_open(const uint8_t _slave, const uint8_t _func, uint8_t * const _pQuery);

sint32_t ModbusMaster_open(const uint8_t _slave, const uint8_t _func, uint8_t * const _pQuery, __MB_QUERY *m_query); 

void ModbusMaster_close(void);

sint32_t Modbus_make_query(const __MB_QUERY_BUILD * const _pQueryData);

sint32_t Modbus_prepare_receiver(__MB_ANSW_READY_DATA * const m_pAnsw, uint8_t * const answBuff);

sint32_t Modbus_receive(const uint8_t _byte);

sint32_t Modbus_process_answ(uint8_t *ptr_data, uint16_t num_regs);

sint32_t Modbus_GetData(uint8_t slave, uint8_t func, uint8_t *data_ptr, uint16_t start_address, uint8_t num_regs);

uint8_t Modbus_init(void);

#include "port.h"
void Modbus_SlaveSelect(eMBSlaves slave_option);


/** 
 * UTILS FUNCTIONS
 **/

/* Sets many input/coil status from a single byte value (all 8 bits of
   the byte value are setted) */
void set_bits_from_byte(uint8_t *dest, int address, const uint8_t value);

/* Sets many input/coil status from a table of bytes (only the bits
   between address and address + nb_bits are setted) */
void set_bits_from_bytes(uint8_t *dest, int address, int nb_bits,
                         const uint8_t *tab_byte);

/* Gets the byte value from many input/coil status.
   To obtain a full byte, set nb_bits to 8. */
uint8_t get_byte_from_bits(const uint8_t *src, int address, int nb_bits);

#endif
