/*
 * port.c
 *
 *  Created on: Jan 30, 2015
 *      Author: Carlos
 */


#pragma warn_unusedarg off

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

#include "modbus_ts.h"
#include "modbus_pm210.h"

#if 1
typedef eMBErrorCode (*peMBRegInputCB)( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs );
typedef eMBErrorCode (*peMBRegHoldingCB)( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode );
typedef eMBErrorCode (*peMBRegCoilsCB)( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode );
typedef eMBErrorCode (*peMBRegDiscreteCB)( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete );
#endif


#if 1
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
#endif

static eMBSlaves Slave_Selected = MODBUS_NONE;
#define MODBUS_NUM_SLAVES  (3)

const peMBRegInputCB _eMBRegInputCB[MODBUS_NUM_SLAVES] = 
{
		eMBRegInputCB_PM210, eMBRegInputCB_TS, eMBRegInputCB_def
};

const peMBRegHoldingCB _eMBRegHoldingCB[MODBUS_NUM_SLAVES] = 
{
		eMBRegHoldingCB_PM210, eMBRegHoldingCB_TS, eMBRegHoldingCB_def
};

const peMBRegCoilsCB _eMBRegCoilsCB[MODBUS_NUM_SLAVES] = 
{
		eMBRegCoilsCB_PM210, eMBRegCoilsCB_TS, eMBRegCoilsCB_def
};

const peMBRegDiscreteCB _eMBRegDiscreteCB[MODBUS_NUM_SLAVES] = 
{
		eMBRegDiscreteCB_PM210, eMBRegDiscreteCB_TS, eMBRegDiscreteCB_def
};


void ModbusSetSlave(eMBSlaves slave_option)
{
	if (slave_option < MODBUS_NONE)
	{		
		Slave_Selected = slave_option;		
	}	
}

#if 1
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

#if 1

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
