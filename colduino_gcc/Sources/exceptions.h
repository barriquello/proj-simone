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

#ifdef __cplusplus
}
#endif

#endif   /* _MCF_EXCEPTIONS_H */

