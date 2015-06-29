/*
 * FreeModbus Libary: HCS08 Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 * Copyright (C) 2008 Trond Melen
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: porttimer.c,v 1.1 2008/03/28 15:59:07 wolti Exp $
 */

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
#include "timer2.h"

/* ----------------------- static functions ---------------------------------*/
static void prvvTIMERExpiredISR(void);

/* ----------------------- Start implementation -----------------------------*/
BOOL xMBPortTimersInit(USHORT usTimeout50us)
{
	if (usTimeout50us > 50 ) return FALSE;	
	
	Timer2Setup(usTimeout50us*BM_BUS_CLOCK/20000, FALSE, (TimerOverflowCallback_fn) prvvTIMERExpiredISR );
	
	return TRUE;
	
}

void vMBPortTimersEnable(void)
{
	/* Enable the timer with the timeout passed to xMBPortTimersInit( ) */
	Timer2Start();
}

void vMBPortTimersDisable(void)
{
	/* Disable any pending timers. */
	Timer2Stop(TRUE);
}

/* This is called whenever the timer has expired. This function
 * must then call pxMBPortCBTimerExpired( ) to notify the protocol stack that
 * the timer has expired.
 */

static void prvvTIMERExpiredISR(void)
{
	if(TRUE == pxMBPortCBTimerExpired())
	{
		
	}	
	
}
