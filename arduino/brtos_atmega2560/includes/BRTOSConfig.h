///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
/////                                                     /////
/////                   OS User Defines                   /////
/////                                                     /////
/////             !User configuration defines!            /////
/////                                                     /////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

// Define if simulation or DEBUG
//#define DEBUG 0

/// Define if verbose info is available
#define VERBOSE					0

/// Define if error check is available
#define ERROR_CHECK				0

/// Define if compute cpu load is active
#define COMPUTES_CPU_LOAD		1

// Define if whatchdog active
#define WATCHDOG				1

/// Define Number of Priorities
#define NUMBER_OF_PRIORITIES	8

/// Define if OS Trace is active
#define OSTRACE 0

#if (OSTRACE == 1)  
  #include "debug_info.h"
#endif

// Define the number of Task to be Installed
// must always be equal or higher to NumberOfInstalledTasks
#define NUMBER_OF_TASKS		16

/// Define if TimerHook function is active
#define TIMER_HOOK_EN		0

/// Define if IdleHook function is active
#define IDLE_HOOK_EN		0


// Habilita o servi�o de sem�foro do sistema
#define BRTOS_SEM_EN           1

// Habilita o servi�o de mutex do sistema
#define BRTOS_MUTEX_EN         1

// Habilita o servi�o de mailbox do sistema
#define BRTOS_MBOX_EN          0

// Habilita o servi�o de filas do sistema
#define BRTOS_QUEUE_EN         1

/// Enable or disable queue 16 bits controls
#define BRTOS_QUEUE_16_EN      0

/// Enable or disable queue 32 bits controls
#define BRTOS_QUEUE_32_EN      0

// Define o n�mero m�ximo de sem�foros (limita a aloca��o de mem�ria p/ sem�foros)
#define BRTOS_MAX_SEM          2

// Define o n�mero m�ximo de mutex (limita a aloca��o de mem�ria p/ mutex)
#define BRTOS_MAX_MUTEX        2

// Define o n�mero m�ximo de Mailbox (limita a aloca��o de mem�ria p/ mailbox)
#define BRTOS_MAX_MBOX         1

// Define o n�mero m�ximo de filas (limita a aloca��o de mem�ria p/ filas)
#define BRTOS_MAX_QUEUE        3

// TickTimer Defines
#define configCPU_CLOCK_HZ            (INT32U)16000000
#define configTICK_RATE_HZ            (INT32U)1000
#define configTIMER_PRE_SCALER        (INT8U)3
#define configTIMER_PRE_SCALER_VALUE  (INT8U)64
#define OSRTCEN                     0


//Stack Defines
// P/ ATMEGA2560 com 8kB de RAM, configurado com 1.5kB p/ STACK Virtual
#define HEAP_SIZE				46*32

// Queue heap defines
#define QUEUE_HEAP_SIZE			 (2*32 + 3*32)


// Stack Size of the Idle Task
#define IDLE_STACK_SIZE          2*32

