#include "hardware.h"

#if 0

#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYBAUD (FOSC/16/BAUD)-1
#define F_CPU 16000000UL 


void uart0_init(unsigned int baudrate)
{
	/*Set baud rate */
	UBRR0H = (baudrate>>8);
	UBRR0L = baudrate;

	/*Enable receiver and transmitter. Enable RX interrupt */
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1 << RXCIE0);
	/* Set frame format: 8 bit data, 1 stop bit */
	UCSR0C = (3<<UCSZ00); 								
}

void putchar_uart0(char data)
{
   /* Wait for empty transmit buffer */
	while (!(UCSR0A & 0x20)){}
    UCSR0A = 0x20;
	// Put data into buffer, sends the data */
    UDR0 = data;
}

void printf_uart0(char *string)
{
	while (*string)
	{
		putchar_uart0(*string);
		string++;
	}
}


const char Term_prompt_str[] PROGMEM = "Terminal started\r\n";
const char * const Term_prompt[] PROGMEM = {Term_prompt_str};	
static char BufferText[32];

int main_demo(void)
{
	// Clock Init
	// Make clock go 16MHz 
	CLKPR = 0x80;        // Initiate write cycle for clock setting
	CLKPR = 0x00;        // 16 MHz clock. Clock division factor = 1
  
	// Disable the watchdog timer
	wdt_disable();

	uart0_init(MYBAUD);	 
	
		//printP_uart0((char*)pgm_read_word(&(Term_prompt)));
	#include "string.h"
	memset(BufferText,0x00,sizeof(BufferText));
	strcpy_P(BufferText, (PGM_P)pgm_read_word(&(Term_prompt[0])));
	printf_uart0(BufferText);

	for(;;){};

}
#endif