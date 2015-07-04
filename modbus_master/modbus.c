/******************************************************************************/
/* modbus.c                                                                   */
/*                                                                            */
/* Based on "libmodbus-2.0.3" - Unix\Win version                              */
/* Author: Stephane Raimbault <stephane.raimbault@gmail.com>                  */
/*                                                                            */
/* Modifed for embedded system 02.2011 Sergei Maslyakov <rusoil.9@gmail.com>  */
/******************************************************************************/


#include "data_types.h"
#include "crc16.h"
#include "modbus.h"


#if (PROCESSOR == COLDFIRE_V1)
#pragma warn_implicitconv off
#endif


/******************************************************************************/
/* Example                                                                    */
/******************************************************************************/
/*
   1. ModbusMaster_open() - init uart, set slave addr and func
   2. Modbus_make_query() - create modbus query. Input structure see in modbus_def.h.
      Func return error(<0) or expected answer datalen.
      Expected answer datalen need for receive and parsing answer.

   3. Send query
   4. Wait answer and parsing      
      Received data bytes need send in function Modbus_receive() and test
      return value.
   5. After receiving data - need run func Modbus_process_answ() - its func
      validate and select payload data from answer. Need test return value for
      error.
   6. ModbusMaster_close() - need if you used driver rs485 or for free alloc memory
*/


/******************************************************************************/
/*      Static variables                                                      */
/******************************************************************************/
__MB_ANSW_READY_DATA  * s_answ = NULL;
__MB_QUERY       	  * s_query = NULL;



#if 0
#define UNKNOWN_ERROR_MSG "Not defined in modbus specification"

static const uint8_t NB_TAB_ERROR_MSG = 12;
static const char *TAB_ERROR_MSG[] = {
        /* 0x00 */ UNKNOWN_ERROR_MSG,
        /* 0x01 */ "Illegal function code",
        /* 0x02 */ "Illegal data address",
        /* 0x03 */ "Illegal data value",
        /* 0x04 */ "Slave device or server failure",
        /* 0x05 */ "Acknowledge",
        /* 0x06 */ "Slave device or server busy",
        /* 0x07 */ "Negative acknowledge",
        /* 0x08 */ "Memory parity error",
        /* 0x09 */ UNKNOWN_ERROR_MSG,
        /* 0x0A */ "Gateway path unavailable",
        /* 0x0B */ "Target device failed to respond"
};
#endif

static void Modbus_change_order_bytes(uint8_t * const _pBuff, const uint32_t _dataLen) 
{

    uint8_t swap;
    uint32_t i;
    
    for (i = 0; i < _dataLen; i++) {
        swap = _pBuff[i + 1];
        _pBuff[i + 1] = _pBuff[i];
        _pBuff[i] = swap;
        i++;
    }
}

/* Computes the length of the expected response */
static uint32_t Compute_response_length(uint8_t * const query)
{
        uint32_t length;
                
        switch (query[1]) {
        case FC_READ_COIL_STATUS:
        case FC_READ_INPUT_STATUS: {
                /* Header + nb values (code from force_multiple_coils) */
                int nb = (query[4] << 8) | query[5];
                length = 3 + (nb / 8) + ((nb % 8) ? 1 : 0);
        }
                break;
        case FC_READ_HOLDING_REGISTERS:
        case FC_READ_INPUT_REGISTERS:
                /* Header + nb values */
                length = 3 + 2*(query[4] << 8 | query[5]);
                break;
        case FC_READ_EXCEPTION_STATUS:
                length = 4;
                break;
        default:
                length = MSG_LENGTH_UNDEFINED;
        }

        return (length + CHECKSUM_LENGTH_RTU);
}


/* Builds a RTU query header */
static int Build_query_basis_rtu(const uint8_t slave, const uint8_t function, const uint16_t start_addr,
								 const uint16_t nb, uint8_t * const query) 
{

	query[0] = slave;
	query[1] = function;
	query[2] = start_addr >> 8;
	query[3] = start_addr & 0x00ff;
	query[4] = nb >> 8;
	query[5] = nb & 0x00ff;

	return PRESET_QUERY_LENGTH_RTU;
}


/* Check_crc16() */

static sint32_t Check_crc16(const uint8_t * const _pMsg,
                            const uint32_t _msgLength) {

    const uint16_t crc_calc = ModbusCrc16(_pMsg, _msgLength - 2);
    const uint16_t crc_received = (_pMsg[_msgLength - 1] << 8)
                                      | _pMsg[_msgLength - 2];

    // Check CRC
    return (crc_calc == crc_received) ? MB_MASTER_ERR_OK : MB_MASTER_ERR_CRC;
}

/*  modbus_add_crc() */
static uint32_t Modbus_add_crc(uint8_t * const _pQuery,
                               const uint32_t _queryLength) {

    const uint16_t crc = ModbusCrc16(_pQuery, _queryLength);
    _pQuery[_queryLength] = (uint8_t)(crc & 0x00FF);
    _pQuery[_queryLength + 1] = (uint8_t)(crc >> 8);
    return 2;
}

/* Returns the slave id! */
static uint8_t Report_slave_id(const uint8_t _slave, const uint8_t _function)
{
        
        s_query->queryLen = Build_query_basis_rtu(_slave, _function, 0, 0, s_query->pQuery) - 4; /* start_addr and count are not used */

        s_query->queryLen += Modbus_add_crc(s_query->pQuery, s_query->queryLen); 

        return s_query->queryLen;
}

        
//==============================================================================
// App: Read_io_status()
//==============================================================================
static void Read_io_status(const uint8_t _slave,
                           const uint8_t _function,
                           const uint16_t _startAddr,
                           const uint16_t _nb) {

    s_query->queryLen = Build_query_basis_rtu(_slave,
                                             _function, 
                                             _startAddr,
                                             _nb,
                                             s_query->pQuery);

    s_query->queryLen += Modbus_add_crc(s_query->pQuery, s_query->queryLen);
}
//==============================================================================
//==============================================================================


//==============================================================================
// App: Read_registers()
//==============================================================================
static sint32_t Read_registers(const uint8_t _slave, const uint8_t _function,
                               const uint16_t _startAddr, const uint16_t _nb) {
    if (_nb > MAX_REGISTERS) {
        return MB_MASTER_ERR_LEN;
    };

    s_query->queryLen = Build_query_basis_rtu(_slave,
                                             _function,
                                             _startAddr,
                                             _nb,
                                             s_query->pQuery);

    s_query->queryLen += Modbus_add_crc(s_query->pQuery, s_query->queryLen);

    return MB_MASTER_ERR_OK;
}
//==============================================================================
//==============================================================================


//==============================================================================
// App: Set_single()
//==============================================================================
static void Set_single(const uint8_t _slave,
                       const uint8_t _function,
                       const uint16_t _addr,
                       const uint16_t _value) {

    s_query->queryLen = Build_query_basis_rtu(_slave,
                                             _function, 
                                             _addr,
                                             _value,
                                             s_query->pQuery);

    s_query->queryLen += Modbus_add_crc(s_query->pQuery, s_query->queryLen);
}
//==============================================================================
//==============================================================================


//==============================================================================
// App: Read_coil_status()
//==============================================================================
static sint32_t Read_coil_status(const uint8_t _slave,
                                 const uint16_t _startAddr,
                                 const uint16_t _nb) {
    if (_nb > MAX_STATUS) {
        return MB_MASTER_ERR_LEN;
    };

    Read_io_status(_slave, FC_READ_COIL_STATUS, _startAddr, _nb);

    return MB_MASTER_ERR_OK;
}
//==============================================================================
//==============================================================================


//==============================================================================
// App: Read_input_status()
//==============================================================================
static sint32_t Read_input_status(const uint8_t _slave,
                                  const uint16_t _startAddr,
                                  const uint16_t _nb) {
    if (_nb > MAX_STATUS) {
        return MB_MASTER_ERR_LEN;
    };

    Read_io_status(_slave, FC_READ_INPUT_STATUS, _startAddr, _nb);

    return MB_MASTER_ERR_OK;
}
//==============================================================================
//==============================================================================


//==============================================================================
// App: Read_holding_registers()
//==============================================================================
static sint32_t Read_holding_registers(const uint8_t _slave,
                                       const uint16_t _startAddr,
                                       const uint16_t _nb) {
    if (_nb > MAX_REGISTERS) {
        return MB_MASTER_ERR_LEN;
    }

    return Read_registers(_slave,
                          FC_READ_HOLDING_REGISTERS,
                          _startAddr,
                          _nb);
}
//==============================================================================
//==============================================================================


//==============================================================================
// App: Read_input_registers()
//==============================================================================
static sint32_t Read_input_registers(const uint8_t _slave,
                                     const uint16_t _startAddr,
                                     const uint16_t _nb) {
    if (_nb > MAX_REGISTERS) {
        return MB_MASTER_ERR_LEN;
    }

    return Read_registers(_slave,
                          FC_READ_INPUT_REGISTERS,
                          _startAddr,
                          _nb);
}
//==============================================================================
//==============================================================================


//==============================================================================
// App: Force_single_coil()
//==============================================================================
static void Force_single_coil(const uint8_t _slave,
                              const uint16_t _coilAddr,
                              uint32_t _state) {
    if (_state) {
        _state = 0xFF00;
    };

    Set_single(_slave, FC_FORCE_SINGLE_COIL, _coilAddr, _state);
}
//==============================================================================
//==============================================================================


//==============================================================================
// App: Preset_single_register()
//==============================================================================
static void Preset_single_register(const uint8_t _slave,
                                   const uint16_t _regAddr,
                                   const uint16_t _value) {

    Set_single(_slave, FC_PRESET_SINGLE_REGISTER, _regAddr, _value);
}
//==============================================================================
//==============================================================================


//==============================================================================
// App: Force_multiple_coils()
//==============================================================================
static sint32_t Force_multiple_coils(const uint8_t _slave,
                                     const uint16_t _startAddr,
                                     const uint16_t _nb,
                                     const uint8_t * const _pData) {
	
	uint32_t i = 0;
	uint32_t coilCheck = 0;
	uint32_t pos = 0;

	uint32_t byteCount = (uint32_t) (_nb / 8) + ((_nb % 8) ? 1 : 0);
	
    if (_nb > MAX_STATUS) {
        return MB_MASTER_ERR_LEN;
    }

    s_query->queryLen = Build_query_basis_rtu(_slave,
                                             FC_FORCE_MULTIPLE_COILS, 
                                             _startAddr,
                                             _nb,
                                             s_query->pQuery);
       
    s_query->pQuery[s_query->queryLen++] = byteCount;

    
    for (i = 0; i < byteCount; i++) {
        int32_t bit;

        bit = 0x01;
        s_query->pQuery[s_query->queryLen] = 0;

        while ((bit & 0xFF) && (coilCheck++ < _nb)) {

            if (_pData[pos++]) {
                s_query->pQuery[s_query->queryLen] |= bit;
            }
            else {
                s_query->pQuery[s_query->queryLen] &=~ bit;
            };
            bit = bit << 1;
        };
        s_query->queryLen++;
    };

    s_query->queryLen += Modbus_add_crc(s_query->pQuery, s_query->queryLen);

    return MB_MASTER_ERR_OK;
}
//==============================================================================
//==============================================================================


//==============================================================================
// App: Preset_multiple_registers()
//==============================================================================
static sint32_t Preset_multiple_registers(const uint8_t _slave,
                                          const uint16_t _startAddr,
                                          const uint16_t _nb,
                                          const uint8_t * const _pData) {
	uint32_t i = 0;
	
	if (_nb > MAX_REGISTERS) {
        return MB_MASTER_ERR_LEN;
    };

    s_query->queryLen = Build_query_basis_rtu(_slave,
                                             FC_PRESET_MULTIPLE_REGISTERS, 
                                             _startAddr,
                                             _nb,
                                             s_query->pQuery);

    s_query->pQuery[s_query->queryLen++] = _nb * 2;

    for (i = 0; i < ((uint32_t)_nb); i++) {
        s_query->pQuery[s_query->queryLen++] = _pData[i];
        s_query->pQuery[s_query->queryLen++] = _pData[i + 1];
    }

    s_query->queryLen += Modbus_add_crc(s_query->pQuery, s_query->queryLen);

    return MB_MASTER_ERR_OK;
}
//==============================================================================
//==============================================================================


//==============================================================================
// App: User_func()
//==============================================================================
static sint32_t User_func(const uint8_t _slave,
                          const uint8_t _function,
                          const uint16_t _dataLen,
                          const uint8_t * const _pData) {
	uint16_t i = 0;
	
	// Test
    if (_dataLen > (MAX_REGISTERS * 2)) {
        return MB_MASTER_ERR_LEN;
    };

    if (_function > 127) {
        return MB_MASTER_ERR_FUNC;
    };

    // Make query
    s_query->queryLen = 0;

    s_query->pQuery[s_query->queryLen++] = _slave;
    s_query->pQuery[s_query->queryLen++] = _function;

    for (i = 0; i < _dataLen; i++) {
        s_query->pQuery[s_query->queryLen++] = _pData[i];
    };

    // Add crc
    s_query->queryLen += Modbus_add_crc(s_query->pQuery, s_query->queryLen);

    return MB_MASTER_ERR_OK;
}
//==============================================================================
//==============================================================================



/* Modbus master open */
sint32_t ModbusMaster_open(const uint8_t _slave, const uint8_t _func,                      	   
                      	   uint8_t * const _pQuery, __MB_QUERY *m_query) 
{
    	
	// error checking
    if ((_slave > 247) || (_func > 127)) {
        return (MODBUS_OK);
    }

    // error checking    
	if(m_query == NULL){
		return (MODBUS_ERROR);
	}
	
	s_query = m_query;
	
	if (s_query->state == MODBUS_OPEN) {
		return (MODBUS_ERROR);
	}
	
    // Set param for query
    s_query->slave = _slave;
    s_query->func = _func;
    s_query->pQuery = _pQuery;
    s_query->queryLen = 0;
    s_query->expectedLen = 0;
    s_query->state = MODBUS_OPEN;
        
    return MODBUS_OK;
}
//==============================================================================
//==============================================================================


//==============================================================================
// App: Close modbus master
//==============================================================================
void ModbusMaster_close(void) {

	if (s_query != NULL){
		s_query->state = MODBUS_CLOSE;
	}
}
//==============================================================================
//==============================================================================


//==============================================================================
// App: Modbus_make_query()
//
// Inputs (structure):
// - addr       (uint16_t)
// - value      (uint16_t)
// - data array (def size in modbus_def.h)
// If used non-standard function value = data len
//
// Outputs:
// < 0 - error
// > 0 - expected response length
// = 0 - response length is undefined (used non-standard function)
//==============================================================================
sint32_t Modbus_make_query(const __MB_QUERY_BUILD * const _pQueryData) {
    sint32_t err = 0;

    switch (s_query->func)
    {
        //----------------------------------------------------------------------
        case FC_READ_COIL_STATUS:
          err = Read_coil_status(s_query->slave,
                                 _pQueryData->addr,
                                 _pQueryData->value);
        break;

        //----------------------------------------------------------------------
        case FC_READ_INPUT_STATUS:
          err = Read_input_status(s_query->slave,
                                  _pQueryData->addr,
                                  _pQueryData->value);
        break;

        //----------------------------------------------------------------------
        case FC_READ_HOLDING_REGISTERS:
          err = Read_holding_registers(s_query->slave,
                                       _pQueryData->addr,
                                       _pQueryData->value);
        break;

        //----------------------------------------------------------------------
        case FC_READ_INPUT_REGISTERS:
          err = Read_input_registers(s_query->slave,
                                     _pQueryData->addr,
                                     _pQueryData->value);
        break;

        //----------------------------------------------------------------------
        case FC_FORCE_SINGLE_COIL:
          Force_single_coil(s_query->slave,
                            _pQueryData->addr,
                            _pQueryData->value);
        break;

        //----------------------------------------------------------------------
        case FC_PRESET_SINGLE_REGISTER:
          Preset_single_register(s_query->slave,
                                 _pQueryData->addr,
                                 _pQueryData->value);
        break;

        //----------------------------------------------------------------------
        case FC_FORCE_MULTIPLE_COILS:
          err = Force_multiple_coils(s_query->slave,
                                     _pQueryData->addr,
                                     _pQueryData->value,
                                     _pQueryData->pData);
        break;

        //----------------------------------------------------------------------
        case FC_PRESET_MULTIPLE_REGISTERS:
          err = Preset_multiple_registers(s_query->slave,
                                          _pQueryData->addr,
                                          _pQueryData->value,
                                          _pQueryData->pData);
        break;
        
        //----------------------------------------------------------------------
        case FC_REPORT_SLAVE_ID:			
          err = Report_slave_id(s_query->slave,
						        s_query->func);
		break;

        //----------------------------------------------------------------------
        default:
          err = User_func(s_query->slave,
        		  	  	  s_query->func,
                          _pQueryData->value,
                          _pQueryData->pData);
        break;
    };

    if (err < 0) {
        return err;
    };    
    
    s_query->expectedLen = Compute_response_length(s_query->pQuery);
    
    return s_query->expectedLen;
}
//==============================================================================

/* Modbus_prepare_receiver */ 
sint32_t Modbus_prepare_receiver(__MB_ANSW_READY_DATA * const m_pAnsw, uint8_t * const answBuff) 
{
	
	if(m_pAnsw == NULL || answBuff == NULL){
		return MODBUS_ERROR;
	}
	
	s_answ = m_pAnsw;
	s_answ->pAnsw = answBuff;
	s_answ->answLen = 0;
	s_answ->errCode = 0;
	
	return MODBUS_OK;
}

//==============================================================================
// App: Modbus_receive()
//
// Outputs:
// < 0 - error
// > 0 - return answLen - wait next data byte
// = 0 - answer received, crc ok or timeout expired (non-standart func)
//==============================================================================
sint32_t Modbus_receive(const uint8_t _byte) {
    static uint32_t state;

    // Test
    if ((s_answ->answLen > MAX_MESSAGE_LENGTH)
        || (s_query->expectedLen > MAX_MESSAGE_LENGTH)) {
        return MB_MASTER_ERR_LEN;
    };

    // Init start parsing
    if (s_answ->answLen == 0) {
        state = eMB_PARS_SLAVE_ADDR;
    };

    s_answ->pAnsw[s_answ->answLen++] = _byte;

    switch (state)
    {
        //----------------------------------------------------------------------
        case eMB_PARS_SLAVE_ADDR:
          state++;
          if (s_answ->pAnsw[0] != s_query->slave) {
              return MB_MASTER_ERR_SLAVE;
          }
          else {
              return s_answ->answLen;
          };

        //----------------------------------------------------------------------
        case eMB_PARS_FUNC:
          state++;
          if (s_answ->pAnsw[1] != s_query->func) {
              s_query->expectedLen = 5;

              if (s_answ->pAnsw[1] != (s_query->func | 0x80)) {
                  return MB_MASTER_ERR_FUNC;
              };
          };
          return s_answ->answLen;

        //----------------------------------------------------------------------
        case eMB_PARS_DATA:
		 if (s_answ->pAnsw[1] == FC_REPORT_SLAVE_ID){
			 s_query->expectedLen = s_answ->pAnsw[2] + 4; 
		 }
          if (s_query->expectedLen != s_answ->answLen) {
              return s_answ->answLen;
          };
        break;

        //----------------------------------------------------------------------
        default:
          return MB_MASTER_ERR_UNDEF;
    };

    return Check_crc16(s_answ->pAnsw, s_answ->answLen);
}
//==============================================================================
//==============================================================================


//==============================================================================
// App: Modbus_process_answ()
//
// Return:
// - < 0 - error
// = 0 - no error
//==============================================================================
sint32_t Modbus_process_answ(uint8_t *ptr_data, uint16_t num_regs) {
    sint32_t err;
    uint8_t idx;

    // Test at timeout
    if ((s_answ->answLen == 0) || (s_answ->answLen < MIN_ANSWER_LENGTH)) {
        return MB_MASTER_ERR_TIMEOUT;
    };

    // Test at user func (need test crc or not)
    if (s_answ->answLen != s_query->expectedLen) {
        err = Check_crc16(s_answ->pAnsw, s_answ->answLen);

        if (err != MB_MASTER_ERR_OK) {
            return err;
        };
    };

    // Test on modbus exception
    if (s_query->func == (s_answ->pAnsw[1] | 0x80)) {
        s_answ->errCode = s_answ->pAnsw[2];

        return MB_MASTER_ERR_OK;
    };

    // Calc payload data
    s_answ->errCode = 0;

    switch (s_query->func)
    {
        //----------------------------------------------------------------------
        case FC_READ_COIL_STATUS:
        //----------------------------------------------------------------------
        case FC_READ_INPUT_STATUS:
          if ((s_answ->answLen - 5) != ((uint32_t)s_answ->pAnsw[2])) {
              return MB_MASTER_ERR_DATA;
          };

          s_answ->pAnsw += 3;
          s_answ->answLen -= 5;
        break;

        //----------------------------------------------------------------------
        case FC_READ_HOLDING_REGISTERS:
        //----------------------------------------------------------------------
        case FC_READ_INPUT_REGISTERS:
          if ((s_answ->answLen - 5) != ((uint32_t)s_answ->pAnsw[2])) {
              return MB_MASTER_ERR_DATA;
          };

          s_answ->pAnsw += 3;
          s_answ->answLen -= 5;
          
          if (ptr_data == NULL) { return MB_MASTER_ERR_DATA; }
          if (s_answ->answLen < num_regs) { return MB_MASTER_ERR_DATA; }
          
          //Modbus_change_order_bytes(s_answ->pAnsw, s_answ->answLen);          
          
          // copy 16-bit regs values
          for (idx = 0; idx < num_regs; idx++)
          {
        	  ptr_data[idx] = *(s_answ->pAnsw);
        	  s_answ->pAnsw++;
        	  ptr_data[idx] = *(s_answ->pAnsw);
        	  s_answ->pAnsw++;
          }
        break;

        //----------------------------------------------------------------------
        case FC_FORCE_SINGLE_COIL:
        //----------------------------------------------------------------------
        case FC_FORCE_MULTIPLE_COILS:
        //----------------------------------------------------------------------
        case FC_PRESET_SINGLE_REGISTER:
        //----------------------------------------------------------------------
        case FC_PRESET_MULTIPLE_REGISTERS:
        break;

        //----------------------------------------------------------------------
        default:
          s_answ->pAnsw += 2;
          s_answ->answLen -= 4;
        break;
    };

    return MB_MASTER_ERR_OK;
}
//==============================================================================
//==============================================================================

/** Utils **/

/* Sets many input/coil status from a single byte value (all 8 bits of
   the byte value are setted) */
void set_bits_from_byte(uint8_t *dest, int address, const uint8_t value)
{
        int i;

        for (i=0; i<8; i++) {
                dest[address+i] = (value & (1 << i)) ? MB_ON : MB_OFF;
        }
}

/* Sets many input/coil status from a table of bytes (only the bits
   between address and address + nb_bits are setted) */
void set_bits_from_bytes(uint8_t *dest, int address, int nb_bits,
                         const uint8_t tab_byte[])
{
        int i;
        int shift = 0;

        for (i = address; i < address + nb_bits; i++) {
                dest[i] = tab_byte[(i - address) / 8] & (1 << shift) ? MB_ON : MB_OFF;
                /* gcc doesn't like: shift = (++shift) % 8; */
                shift++;
                shift %= 8;
        }
}

/* Gets the byte value from many input/coil status.
   To obtain a full byte, set nb_bits to 8. */
uint8_t get_byte_from_bits(const uint8_t *src, int address, int nb_bits)
{
        int i;
        uint8_t value = 0;
 
        if (nb_bits > 8) {                
                nb_bits = 8;
        }

        for (i=0; i < nb_bits; i++) {
                value |= (src[address+i] << i);
        }
        
        return value;
}
