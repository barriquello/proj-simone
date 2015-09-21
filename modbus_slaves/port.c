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
/*
 * port.c
 *
 *  Created on: Jan 30, 2015
 *      Author: Carlos
 */

#include "AppConfig.h"
#include "modbus_slaves.h"

#if COLDUINO
#pragma warn_unusedarg off

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

#include "modbus_ts.h"
#include "modbus_pm210.h"

static eMBSlaves Slave_Selected = MODBUS_NONE;


typedef eMBErrorCode (*peMBRegInputCB)( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs );
typedef eMBErrorCode (*peMBRegHoldingCB)( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode );
typedef eMBErrorCode (*peMBRegCoilsCB)( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode );
typedef eMBErrorCode (*peMBRegDiscreteCB)( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete );


eMBErrorCode eMBRegInputCB_def ( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs );
eMBErrorCode eMBRegHoldingCB_def ( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode );
eMBErrorCode eMBRegCoilsCB_def ( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode );
eMBErrorCode eMBRegDiscreteCB_def ( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete );

eMBErrorCode eMBRegInputCB_PM210 ( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs );
eMBErrorCode eMBRegHoldingCB_PM210 ( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode );
eMBErrorCode eMBRegCoilsCB_PM210 ( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode );
eMBErrorCode eMBRegDiscreteCB_PM210 ( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete );

eMBErrorCode eMBRegInputCB_TS ( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs );
eMBErrorCode eMBRegHoldingCB_TS ( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode );
eMBErrorCode eMBRegCoilsCB_TS ( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode );
eMBErrorCode eMBRegDiscreteCB_TS ( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete );


CONST peMBRegInputCB _eMBRegInputCB[MODBUS_NUM_SLAVES] = 
{
		eMBRegInputCB_PM210, eMBRegInputCB_TS, eMBRegInputCB_def
};

CONST peMBRegHoldingCB _eMBRegHoldingCB[MODBUS_NUM_SLAVES] = 
{
		eMBRegHoldingCB_PM210, eMBRegHoldingCB_TS, eMBRegHoldingCB_def
};

CONST peMBRegCoilsCB _eMBRegCoilsCB[MODBUS_NUM_SLAVES] = 
{
		eMBRegCoilsCB_PM210, eMBRegCoilsCB_TS, eMBRegCoilsCB_def
};

CONST peMBRegDiscreteCB _eMBRegDiscreteCB[MODBUS_NUM_SLAVES] = 
{
		eMBRegDiscreteCB_PM210, eMBRegDiscreteCB_TS, eMBRegDiscreteCB_def
};

#endif

void ModbusSetSlave(eMBSlaves slave_option)
{
	if (slave_option < MODBUS_NONE)
	{		
		Slave_Selected = slave_option;		
	}	
}

#if COLDUINO
eMBErrorCode eMBRegCoilsCB_def(UCHAR * pucRegBuffer, USHORT usAddress,
		USHORT usNCoils, eMBRegisterMode eMode)
{
	return MB_ENOERR;
}

eMBErrorCode eMBRegDiscreteCB_def(UCHAR * pucRegBuffer, USHORT usAddress,
		USHORT usNDiscrete)
{
	return MB_ENOERR;
}

eMBErrorCode eMBRegInputCB_def(UCHAR * pucRegBuffer, USHORT usAddress,
		USHORT usNRegs)
{
	return MB_ENOERR;
}

eMBErrorCode eMBRegHoldingCB_def(UCHAR * pucRegBuffer, USHORT usAddress,
		USHORT usNRegs, eMBRegisterMode eMode)
{
	return MB_ENOERR;
}
#endif

#if COLDUINO

eMBErrorCode eMBRegInputCB ( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
	return (*_eMBRegInputCB[Slave_Selected])(pucRegBuffer, usAddress, usNRegs);	
}
eMBErrorCode eMBRegHoldingCB ( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
{
	return (*_eMBRegHoldingCB[Slave_Selected])(pucRegBuffer, usAddress, usNRegs, eMode);
}
eMBErrorCode eMBRegCoilsCB ( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode )
{
	return (*_eMBRegCoilsCB[Slave_Selected])(pucRegBuffer, usAddress, usNCoils, eMode);
}
eMBErrorCode eMBRegDiscreteCB ( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
	return (*_eMBRegDiscreteCB[Slave_Selected])(pucRegBuffer, usAddress, usNDiscrete);	
}

#endif
