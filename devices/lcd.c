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
/**
* \file lcd.c
* \brief Alphanumeric LCD main functions
*
* This file contain the main functions of the alphanumeric lcd, such as:
* initialize the lcd, write a character, write a sentence, clear the lcd,etc.
*
**/

#include "hardware.h"
#include "lcd.h"
#include "BRTOS.h"

#pragma warn_implicitconv off



// Declara um ponteiro para o bloco de controle do Display LCD
BRTOS_Mutex *LCD;



// Declara��o do prot�tipo da fun��o de teste da busy flag
static void bit_test(void);
void Delay_ms(unsigned int DelayTime);


// Cria um semaforo com contador = 1, informando que o recurso est� dispon�vel
// ap�s a inicializa��o
void init_resource_lcd(INT8U priority)
{  
  // Cria um mutex com contador = 1, informando que o recurso est� dispon�vel
  // ap�s a inicializa��o
  // Prioridade m�xima a acessar o recurso = priority
  if (OSMutexCreate(&LCD,priority) != ALLOC_EVENT_OK)
  {
    // Oh Oh
    // N�o deveria entrar aqui !!!
    while(1){};
  };
}


//Fun��o para adquirir direito exclusivo ao LCD
void acquire_lcd(void)
{
  // Aloca o recurso do display LCD
  OSMutexAcquire(LCD);
}

//Fun��o para liberar o display LCD
void release_lcd(void)
{
  // Libera o recurso do display LCD
  OSMutexRelease (LCD);    
}


// Fun��o para escrita de uma frase no display
void printf_lcd(char *string)
{
  while(*string)
  { 
    // sends the character
    putchar_lcd(*string);    
    // Increments data string
    string++;
  }
  
}


// Fun��o para escrita de um n�mero de 2 digitos no display
void write_number_lcd(INT8U number)
{
  INT8U i = 0; 
  
  i = (number / 10);
  putchar_lcd('0' + i);      
  putchar_lcd('0' + (number - (i * 10)));
}


// Envia um comando para o m�dulo do display
void instr_lcd(CHAR8 command)
{  
  #if (LCD_DATA_BUS == 4)              
    INT8U data = 0;
    
    // Config LCD for instruction
    RS = 0;
	#if (LCD_DATA_BUS != 4)
		RW = 0;
	#endif
    
    // First nibble
    data = (command & 0xF0);
    DATA &= 0x0F << DATA_SHIFT;
    DATA |= data >> DATA_SHIFT;
    E = 1;
    delay_600ns();
    E = 0;    
    
    // Second nibble
    data = ((command & 0x0F) << 4);
    DATA &= 0x0F << DATA_SHIFT;
    DATA |= data >> DATA_SHIFT;
    E = 1;
    delay_600ns();
    E = 0; 
    
    #if (LCD_USE_BRTOS == 1)
      DelayTask(2);
    #else
      Delay_ms(1);
    #endif        
    
  #else  
    // Test the busy flag
    bit_test();
    
    // Config LCD for instruction
    RS = 0;
    RW = 0;    
    
    DATA = command;
    
    E = 1;
    delay_600ns();
    E = 0;
  #endif
}


// Envia um caractere para o m�dulo do display
void putchar_lcd(CHAR8 dado)
{
  #if (LCD_DATA_BUS == 4)
    INT8U data = 0;
    
    // Config LCD for data
    RS = 1;
	#if (LCD_DATA_BUS != 4)
		RW = 0;
	#endif
    
    // First nibble
    data = (dado & 0xF0);
    DATA &= 0x0F << DATA_SHIFT;
    DATA |= data >> DATA_SHIFT;    
    E = 1;
    delay_600ns();
    E = 0;    
    
    // Second nibble
    data = ((dado & 0x0F) << 4);
    DATA &= 0x0F << DATA_SHIFT;
    DATA |= data >> DATA_SHIFT; 
    E = 1;
    delay_600ns();
    E = 0;   
    
    #if (LCD_USE_BRTOS == 1)
      DelayTask(2);
    #else
      Delay_ms(1);
    #endif    
        
  #else  
    // Test the busy flag
    bit_test();
    
    // Config LCD for data
    RS = 1;
    RW = 0;        
    
    DATA = dado;
    
    E = 1;
    delay_600ns();
    E = 0;
  #endif   
}


// Inicializa��o do display para 2 linhas com caracteres de 5x7
// Deslocamento do cursor a direita com cursor apagado
void init_lcd(void){
  // Init data bus to output, all signals to zero
  #if (LCD_DATA_BUS == 4)
    DATA      &= ((0x0F << DATA_SHIFT) | (0x0F) >> DATA_SHIFT);
    DATA_DIR  |= (0xF0 >> DATA_SHIFT);
  #else
    DATA      = 0;
    DATA_DIR  = 0xFF;
  #endif
  
  // Init control bus to output, all signals to zero
  RS        = 0;
  RS_DIR    = 1;
  
  #if (LCD_DATA_BUS != 4)
  RW        = 0;
  RW_DIR    = 1;  
  #endif
  
  E         = 0;
  E_DIR     = 1;  
  
  #if (LCD_DATA_BUS == 4)
    instr_lcd(0x28);
	#if (LCD_USE_BRTOS == 1)
	  DelayTask(15);
	#else
	  Delay_ms(15);
	#endif
	  
    instr_lcd(0x28);
	#if (LCD_USE_BRTOS == 1)
	  DelayTask(15);
	#else
	  Delay_ms(15);
	#endif    
  #else  
    instr_lcd(0x38);
	#if (LCD_USE_BRTOS == 1)
	  DelayTask(15);
	#else
	  Delay_ms(15);
	#endif
	  
    instr_lcd(0x38);
	#if (LCD_USE_BRTOS == 1)
	  DelayTask(15);
	#else
	  Delay_ms(15);
	#endif    
  #endif
  
  instr_lcd(0x06);
  instr_lcd(0x0C);
  instr_lcd(0x01);  
}


// Fun��o de posicionamento do cursor do display
void xy_position_lcd(INT8U linha, INT8U coluna)
{ 
  INT8U linha_coluna = 0;
    
  switch(linha)
  {
    case 1:
      coluna--;
      linha_coluna = 0x80 + coluna;
      break;
    case 2:
      coluna--;
      linha_coluna = 0xC0 + coluna;
      break;
    default:
      linha_coluna = 0x01;
      return;
  }
  instr_lcd(linha_coluna);
}


// Fun��o para limpar o display e retornar a primeira posi��o da primeira linha
void clear_lcd(void)
{  
  instr_lcd(0x01) ;
}


// Fun��o de teste da busy flag
static void bit_test(void)
{
  // Config LCD for read instruction
  RS = 0;   
  #if (LCD_DATA_BUS != 4)
	  RW = 1;
  #endif
  
  DATA_DIR = 0x00;
  
  E = 1;
  delay_450ns();
  
  // Wait until the busy flag informs that the LCD controller is idle
  while(BUSY_FLAG)
  {
    #if (LCD_USE_BRTOS == 1)
      DelayTask(1);
    #endif   
  };
  
  delay_450ns();
  
  E = 0;
  
  #if (LCD_DATA_BUS != 4)
	  RW = 0;
  #endif
  
  DATA_DIR = 0xFF;
}


/*----------------------------------------------------------------------*/
/* Fun��o de delay em milisegundos                                      */
/*----------------------------------------------------------------------*/
void Delay_ms(unsigned int DelayTime)
{
  unsigned int j;
  
  // loop = 4 cpu cycles + 15 cycles of the 600ns delay = 19 cpu cycles
  DelayTime = DelayTime * (LCD_CPU_CLOCK/LCD_FOR_NUMBER_OF_CYCLES/1000);
  
  for(j=0;j<DelayTime;j++)
  {
    delay_600ns();
  }
}
  
