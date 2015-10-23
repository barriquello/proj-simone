#include "hardware.h"

#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYBAUD (FOSC/16/BAUD)-1
#define F_CPU 16000000UL 

int main_demo(void)
{
  // Clock Init
  // Make clock go 16MHz 
  CLKPR = 0x80;        // Initiate write cycle for clock setting
  CLKPR = 0x00;        // 16 MHz clock. Clock division factor = 1
  
  // Disable the watchdog timer
  wdt_disable();
  
  for(;;){};


}
