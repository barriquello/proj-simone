/*
 * File: exceptions.h
 * Purpose: Generic exception handling for ColdFire processors
 *
 * Notes:
 */

#ifndef _MCF_EXCEPTIONS_H
#define _MCF_EXCEPTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H) || (defined _MCF51JE128_H)
extern void usb_int_dis(void);
extern void usb_int_en(void);
#endif /*  (defined _MCF51MM256_H) || (defined _MCF51JE256_H)  */


/***********************************************************************/
/*
 * This is the assembly exception handler defined in the vector table.  
 * This function is in assembler so that the frame pointer can be read  
 * from the stack.
 * Note that the way to give the stack frame as argument to the c handler
 * depends on the used ABI (Register, Compact or Standard).
 *
 */
void asm_exception_handler(void);


#if 1
extern void TickTimer(void);
extern void SwitchContext(void);
extern void USB_ISR(void);
extern void Analog_comparator(void);

#include "AppConfig.h"
#include "UART.h"
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

#define Trap14_Handler 			SwitchContext
#define Int_TPM1_Ovf_Handler 	TickTimer

#if (ENABLE_UART1 == TRUE)
#define Int_SCI1_Err_Handler 	uart1_error
#define Int_SCI1_Rx_Handler 	uart1_rx
#define Int_SCI1_Tx_Handler		uart1_tx
#endif

#if (ENABLE_UART2 == TRUE)
#define Int_SCI2_Err_Handler 	uart2_error
#define Int_SCI2_Rx_Handler 	uart2_rx
#define Int_SCI2_Tx_Handler 	uart2_tx
#endif

#if USB_DEVICE_ENABLED == 1
#define Int_USB_Handler 	USB_ISR
#endif

#if  COMPARATOR_ENABLED == 1
#define Int_CMP_Handler 	Analog_comparator
#endif

#endif

#ifdef __cplusplus
}
#endif

#endif   /* _MCF_EXCEPTIONS_H */

