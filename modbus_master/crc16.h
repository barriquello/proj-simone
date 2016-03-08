 /** \addtogroup Sistema
 *  @{
 */

/** \addtogroup modbus
 *  @{
 */
 
  /** \defgroup crc16 CRC16
 *  @{
	Verificação de redundância cíclica com polinômio x^16+x^15+x^2+1
	\see http://modbus.org/docs/Modbus_over_serial_line_V1_02.pdf
 */
 
/******************************************************************************/
/* crc16.h                                                                    */
/******************************************************************************/


#ifndef __CRC16_H
#define __CRC16_H

#include "data_types.h"

/**************************** Func declarations *******************************/
uint16_t ModbusCrc16(const uint8_t * const _pBuff, uint32_t _len);



#endif

/** @} */
/** @} */
/** @} */
