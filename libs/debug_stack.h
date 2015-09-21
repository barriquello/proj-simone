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

