/**
* \file HAL.h
* \brief BRTOS Hardware Abstraction Layer defines and inline assembly
*
* This file contain the defines and inline assembly that are processor dependant.
*
*
**/

/*********************************************************************************************************
*                                               BRTOS
*                                Brazilian Real-Time Operating System
*                            Acronymous of Basic Real-Time Operating System
*
*                              
*                                  Open Source RTOS under MIT License
*
*
*
*                                     OS HAL Header to Coldfire V1
*
*
*   Author:   Gustavo Weber Denardin
*   Revision: 1.0
*   Date:     20/03/2009
*
*   Authors:  Carlos Henrique Barriquelo e Gustavo Weber Denardin
*   Revision: 1.2
*   Date:     01/10/2010
*
*********************************************************************************************************/

#ifndef OS_HAL_H
#define OS_HAL_H

#include "OS_types.h"
#include "hardware.h"

// HAL functions prototype
void SwitchContext(void);
void TickTimer(void);

/// Supported processors
#define COLDFIRE_V1			1
#define HCS08			    2
#define MSP430			  	3
#define ATMEGA			  	4
#define PIC18			    5


/// Define the used processor
#define PROCESSOR 		COLDFIRE_V1

/// Define the CPU type
#define OS_CPU_TYPE 	INT32U

#define STACK_MARK  			1

/// Define if the optimized scheduler will be used
#define OPTIMIZED_SCHEDULER 	0

/// Define if nesting interrupt is active
#define NESTING_INT 			1

#define TASK_WITH_PARAMETERS 	0

/// Define if its necessary to save status register / interrupt info
#if NESTING_INT == 1
  #define OS_SR_SAVE_VAR INT16U CPU_SR = 0;
#else
  #define OS_SR_SAVE_VAR
#endif

/// Define stack growth direction
#define STACK_GROWTH 0            /// 1 -> down; 0-> up

/// Define CPU Stack Pointer Size
#define SP_SIZE 32


extern INT8U  iNesting;
extern INT32U SPvalue;


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////      Port Defines                                /////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

/// Defines the change context command of the choosen processor
#define ChangeContext(void) __trap(14); //__asm volatile ("TRAP %14\n\t");


/// Defines the disable interrupts command of the choosen microcontroller
#define UserEnterCritical() DisableInterrupts;
/// Defines the enable interrupts command of the choosen microcontroller
#define UserExitCritical() EnableInterrupts;

#if (NESTING_INT == 0)
  
  /// Defines the disable interrupts command of the choosen microcontroller
  #define OSEnterCritical() UserEnterCritical()
  /// Defines the enable interrupts command of the choosen microcontroller
  #define OSExitCritical() UserExitCritical()
  
#else

  INT16U OS_CPU_SR_Save(void);
  #define  OSEnterCritical()  (CPU_SR = OS_CPU_SR_Save())	 // Disable interrupts    
  void OS_CPU_SR_Restore(INT16U);
  #define  OSExitCritical()  (OS_CPU_SR_Restore(CPU_SR))	 // Enable interrupts  
  
#endif

/// Defines the low power command of the choosen microcontroller
#define OS_Wait //asm(STOP #0x2000);
/// Defines the tick timer interrupt handler code (clear flag) of the choosen microcontroller
#define TICKTIMER_INT_HANDLER TPM1SC_TOF = 0
#define TIMER_MODULE  TPM1MOD
#define TIMER_COUNTER TPM1CNT


// stacked by the RTI interrupt process
// M�nimo de 60 devido ao salvamento de 15 registradores de 32 bits da CPU
// D0-D7 (32 bytes) + A0-A6 (28 bytes) + Format (1 byte) + Vector (1 byte) + SR (2 bytes) + SP (4 bytes)
/// Minimum size of a task stack.
/// Example in the coldfire processor: D0-D7 (32 bytes) + A0-A6 (28 bytes) + Format (1 byte) + Vector (1 byte) + SR (2 bytes) + SP (4 bytes) = 68 bytes
#if (defined STACK_MARK && STACK_MARK == 1)
#if (NESTING_INT == 1)
#define NUMBER_MIN_OF_STACKED_BYTES (72+4)
#else
#define NUMBER_MIN_OF_STACKED_BYTES (68+4)
#endif
#else
#if (NESTING_INT == 1)
#define NUMBER_MIN_OF_STACKED_BYTES 72
#else
#define NUMBER_MIN_OF_STACKED_BYTES 68
#endif
#endif

// User defined: stacked for user function calls + local variables
// Ainda, como podem ocorrer interrup��es durante as tarefas, alocar 28 bytes a cada
// interrup��o ativa
// 4 bytes to Local Variable Allocation
// 4 bytes to Function Call





////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////      Functions Prototypes                        /////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

#if (TASK_WITH_PARAMETERS == 1)
  void CreateVirtualStack(void(*FctPtr)(void*), INT16U NUMBER_OF_STACKED_BYTES, void *parameters);
#else
  void CreateVirtualStack(void(*FctPtr)(void), INT16U NUMBER_OF_STACKED_BYTES);
#endif

/*****************************************************************************************//**
* \fn void TickTimerSetup(void)
* \brief Tick timer clock setup
* \return NONE
*********************************************************************************************/
void TickTimerSetup(void);

/*****************************************************************************************//**
* \fn void OSRTCSetup(void)
* \brief Real time clock setup
* \return NONE
*********************************************************************************************/
void OSRTCSetup(void);

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
/////                                                     /////
/////               Coldfire Nesting Defines              /////
/////                                                     /////
/////                                                     /////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

#if (NESTING_INT == 1)

/*****************************************************************************************//**
* \fn inline asm void SaveContext(void)
* \brief Save context function
* \return NONE
*********************************************************************************************/
#define SaveContext()  __asm__ volatile("lea.l		(-36, %sp), %sp \n\t" \
						   	   	    	"movem.l		%d3-%d7, (%sp) \n\t" \
										"movem.l		%a2-%a6, (%sp) \n\t" )


/// Save Context Define
#define OS_SAVE_CONTEXT() SaveContext()
////////////////////////////////////////////////////////////


/*****************************************************************************************//**
* \fn inline asm void RestoreContext(void)
* \brief Restore context function
* \return NONE
*********************************************************************************************/
#define RestoreContext() __asm__ volatile("movem.l		(%sp), %d3-%d7 		\n\t"   \
										  "movem.l		(%sp), %a2-%a6		\n\t"   \
										  "lea.l		%sp@(36), %sp		\n\t"   )


/// Restore Context Define
#define OS_RESTORE_CONTEXT() RestoreContext()
////////////////////////////////////////////////////////////



/*****************************************************************************************//**
* \fn inline asm void SaveSP(void)
* \brief Restore context function
* \return NONE
*********************************************************************************************/
#define SaveSP() __asm__ volatile("MOVE    %A7,SPvalue \n\t")

/// Save Stack Pointer Define
#define OS_SAVE_SP() SaveSP()
////////////////////////////////////////////////////////////

/*****************************************************************************************//**
* \fn inline asm void RestoreContext(void)
* \brief Restore context function
* \return NONE
*********************************************************************************************/
#define RestoreSP() __asm__ volatile("move.l  SPvalue, %sp\n\t");

/// Restore Stack Pointer Define
#define OS_RESTORE_SP() RestoreSP()
////////////////////////////////////////////////////////////




/*****************************************************************************************//**
* \fn inline asm void RestoreSR(void)
* \brief Restore context function
* \return NONE
*********************************************************************************************/
#define RestoreSR()
#if 0
__asm__ volatile("MOVE.W   SR,D1 	\n\t" \
								 "MOVE.W   26(A7),D0 	\n\t" \
								 "ANDI.L   #0x0700,D0  \n\t" \
								 "ANDI.L   #0xF8FF,D1 	\n\t" \
								 "OR       D1,D0 		\n\t" \
								 "MOVE.W   D0,SR		\n\t" )
#endif


/// Restore Status Register Define
#define OS_ENABLE_NESTING() RestoreSR()
////////////////////////////////////////////////////////////




#define RestoreIntSR()	__asm__ volatile("NOP")


/// Restore Status Register from ISR
#define OS_RESTORE_NESTING() RestoreIntSR()





#define CriticalDecNesting()
#if 0
__asm__ volatile("MOVE.W   %SR,%D2 	    \n\t" \
											 "ORI.L    #0x0700,%D2   \n\t" \
											 "MOVE.W   %D2,%SR 	    \n\t" \
											 "MVZ.B    iNesting,%D0  \n\t" \
        									 "SUBQ.L   #1,%D0 		\n\t" \
        									 "MOVE.B   %D0,iNesting  \n\t")
#endif



#define OSRestoreISR() 	__asm__ volatile("lea.l   (4, %sp), %sp\n\t" 		  \
		 	 	 	 	 	 	 	 	 "movem.l (%sp), %d0-%d2/%a0-%a1\n\t" \
										 "lea.l   (%sp, 24), %sp\n\t"         \
										 "rte\n\t" 							  );

#define OS_RESTORE_ISR()  OSRestoreISR()



  
#else





///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
/////                                                     /////
/////          Coldfire Without Nesting Defines           /////
/////                                                     /////
/////                                                     /////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////      Save Context Define                         /////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

asm inline __declspec(register_abi) void SaveContext(void) 
{  
	LEA		   -40(A7),A7				    // reserve space on current stack
	MOVEM.L  D3-D7/A2-A6,(A7)			// save CPU registers
}

#define OS_SAVE_CONTEXT() SaveContext()
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////      Restore Context Define                      /////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

asm inline __declspec(register_abi) void RestoreContext(void)
{  
	MOVEM.L (A7),D3-D7/A2-A6  			// restore other CPU registers
	LEA		  40(A7),A7			     	    // adjust stack pointer value
}

#define OS_RESTORE_CONTEXT() RestoreContext()
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////      Save Stack Pointer Define                   /////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

asm inline __declspec(register_abi) void OS_SAVE_SP(void) 
{  
	MOVE     A7,SPvalue           // save top of stack
}
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////      Save Stack Pointer Define                   /////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

asm inline __declspec(register_abi) void OS_RESTORE_SP(void)
{  
	MOVE    SPvalue,A7              // restore top of stack
}
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////










asm inline __declspec(register_abi) CriticalDecNesting(void)
{                                                                     
        MVZ.B    iNesting,D0
        SUBQ.L   #1,D0
        MOVE.B   D0,iNesting
}


asm inline __declspec(register_abi) void OSRestoreISR(void) {

     MOVEM.L          (A7),D0-D2/A0-A1                     // restore CPU scratch registers
     LEA              20(A7),A7                            // adjust stack pointer value
     RTE
}

#define OS_RESTORE_ISR()  OSRestoreISR()


#endif


#if (OPTIMIZED_SCHEDULER == 1)
#if __GNUC__
#define READY_LIST_VAR read_list
#endif

#define Optimezed_Scheduler()  \
INT8U priority;								\
__asm volatile   ("FF1 %1       \n\t"		\
				  "NEG %1 	    \n\t" 	    \
				  "ADDI #31,%1  \n\t"       \
				  "MOVE.L %0,%1 \n\t"		\
				  : "=r" (priority)			\
				  : "r" (READY_LIST_VAR));	\
return priority

#endif



#define BTOSStartFirstTask()      OS_RESTORE_SP();       \
                                  OS_RESTORE_CONTEXT();  \
                                  OS_RESTORE_ISR()




//////////////// ISR dedicated stack /////////////////
#define ISR_DEDICATED_STACK 0

#if (defined ISR_DEDICATED_STACK && defined ISR_DEDICATED_STACK == 1)
	#define OS_RESTORE_ISR_SP()    //__asm__ volatile ("MOVE.L SPval_bkp, %sp \n\t")
	#define ISR_STACK_SIZE  (128)
	extern  OS_CPU_TYPE ISR_STACK[ISR_STACK_SIZE];
	extern INT32U SPval_bkp;
#endif

#endif
