///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
/////                                                     /////
/////                   OS User Defines                   /////
/////                                                     /////
/////             !User configuration defines!            /////
/////                                                     /////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

/// Define the endianess of the microcontroller
#define PSP_ENDIAN			BRTOS_BIG_ENDIAN

/// Define if simulation or DEBUG
//#define DEBUG 1

/// Define if verbose info is available
#define VERBOSE 0

/// Define if error check is available
#define ERROR_CHECK 0

/// Define if whatchdog is active
#define WATCHDOG 1

/// Define if compute cpu load is active
#define COMPUTES_CPU_LOAD 1

// The Nesting define must be set in the file HAL.h
// Example:
/// Define if nesting interrupt is active
//#define NESTING_INT 0

/// Define Number of Priorities
#define NUMBER_OF_PRIORITIES 32

/// Define the maximum number of Tasks to be Installed
/// must always be equal or higher to NumberOfInstalledTasks
#define NUMBER_OF_TASKS (INT8U)5

/// Define if OS Trace is active
#define OSTRACE 0

#if (OSTRACE == 1)  
  #include "debug_stack.h"
#endif

/// Define if TimerHook function is active
#define TIMER_HOOK_EN 		   1

/// Define if IdleHook function is active
#define IDLE_HOOK_EN 		   0

/// Enable or disable semaphore controls
#define BRTOS_SEM_EN           1

/// Enable or disable mutex controls
#define BRTOS_MUTEX_EN         1

/// Enable or disable mailbox controls
#define BRTOS_MBOX_EN          1

/// Enable or disable queue controls
#define BRTOS_QUEUE_EN         1

/// Enable or disable queue 16 bits controls
#define BRTOS_QUEUE_16_EN      1

/// Enable or disable queue 32 bits controls
#define BRTOS_QUEUE_32_EN      1

/// Defines the maximum number of semaphores\n
/// Limits the memory allocation for semaphores
#define BRTOS_MAX_SEM          8

/// Defines the maximum number of mutexes\n
/// Limits the memory allocation for mutex
#define BRTOS_MAX_MUTEX        4

/// Defines the maximum number of mailboxes\n
/// Limits the memory allocation mailboxes
#define BRTOS_MAX_MBOX         4

/// Defines the maximum number of queues\n
/// Limits the memory allocation for queues
#define BRTOS_MAX_QUEUE        4


/// TickTimer Defines
#define configCPU_CLOCK_HZ          (INT32U)24000000    ///< CPU clock in Hertz
#define configTICK_RATE_HZ          (INT32U)1000        ///< Tick timer rate in Hertz
#define configTIMER_PRE_SCALER      0                   ///< Informs if there is a timer prescaler
#define configRTC_CRISTAL_HZ        (INT32U)1000
#define configRTC_PRE_SCALER        10
#define OSRTCEN                     0


// Stack Size of the Idle Task
#define IDLE_STACK_SIZE             (INT16U)192


/// Stack Defines
/// Coldfire with 16KB of RAM: 56 * 128 bytes = 7KB of Virtual Stack
#define HEAP_SIZE 54*128

// Queue heap defines
// Configurado com 2KB p/ filas
#define QUEUE_HEAP_SIZE 8*128
