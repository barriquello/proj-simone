Modbus-master lib for emdedded applications
Based on "libmodbus-2.0.3" (http://libmodbus.org/) Stéphane Raimbault <stephane.raimbault@gmail.com>

Modbus Master RTU for serial lines. Optimized for use with the RTOS. 

Implemented Modbus func:

0x01 - Read Coils
0x02 - Read Discrete Inputs
0x03 - Read Holding Registers
0x04 - Read Input Registers
0x05 - Write Single Coil
0x06 - Write Single Register
0x0F - Write Multiple Coils
0x10 - Write Multiple Registers
interface for user-def func