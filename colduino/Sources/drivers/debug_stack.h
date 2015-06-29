
#define MAX_DEPTH_TRACE 200
#define MAX_TRACE_LINE  10

#define DELAYTASK 0
#define SEMPEND   1
#define QUEUEPEND 2
#define MUTEXPEND 3 
#define SEMPOST   4
#define QUEUEPOST 5
#define MUTEXPOST 6
#define OS_IDLE   7

#define ISR_ONLY   1
#define ISR_TICK   2

#define OS_TICK_SHOW 1
#define OS_IDLE_SHOW 0
#define OS_TRACE_BY_TASK 1

void Transmite_Uptime(unsigned char Comm);
void LCD_Uptime(CHAR8* string);
void Transmite_RAM_Ocupada(unsigned char Comm);
void Transmite_Task_Stacks(unsigned char Comm);
#if (COMPUTES_CPU_LOAD == 1)
void Transmite_CPU_Load(unsigned char Comm);
#endif

void Reason_of_Reset(INT8U Comm);


#if (OSTRACE == 1) 
void Update_OSTrace (INT8U task, INT8U syscall);
void Send_OSTrace(INT8U Comm);  
#endif

