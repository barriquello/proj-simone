/*
 * File:    exceptions.c
 * Purpose: Generic exception handling for ColdFire processors
 *
 */

#include "derivative.h"
#include "exceptions.h"
#include "BRTOS.h"
#include "AppConfig.h"

#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H) || (defined _MCF51JE128_H)

volatile unsigned char usb_int_disable = 0;
volatile unsigned char usb_int_en_copy = 0;

void usb_int_dis(void)
{
	usb_int_disable++;
}

void usb_int_en(void)
{
	volatile unsigned char dummy;
	if (usb_int_disable)
	{
		usb_int_disable--;
	}

	if (INT_ENB == 0)
	{
		if (usb_int_disable == 0)
		{
			dummy = usb_int_en_copy;
			usb_int_en_copy = 0;
			INT_ENB = dummy;
		}
	}
}

#endif /* (defined _MCF51MM256_H) || (defined _MCF51JE256_H) */

#if 0
#pragma TRAP_PROC
void asm_exception_handler(void)
{
	// ************************
	// Entrada de interrupção
	// ************************
	OS_INT_ENTER();

	// Interrupt Handling
	PTBD_PTBD0 = 0;
	PTBDD_PTBDD0 = 1;
	
	DisableInterrupts;
	
	while (1)
	{
		__RESET_WATCHDOG();
	};

	// ************************
	// Interrupt Exit
	// ************************
	OS_INT_EXIT();
	// ************************
}
#endif

#if 0
extern void TickTimer(void);
extern void SwitchContext(void);
extern void USB_ISR(void);
extern void Analog_comparator(void);

#include "uart.h"
#if (ENABLE_UART1 == TRUE)
extern void uart1_tx(void);
extern void uart1_rx(void);
extern void uart1_error(void);
#endif

#if (ENABLE_UART2 == TRUE)
extern void uart2_tx(void);
extern void uart2_rx(void);
extern void uart2_error(void);
#endif 

extern void Timer2Overflow(void);
#endif


