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



// Declaração do protótipo da função de teste da busy flag
static void bit_test(void);
void Delay_ms(unsigned int DelayTime);


// Cria um semaforo com contador = 1, informando que o recurso está disponível
// após a inicialização
void init_resource_lcd(INT8U priority)
{  
  // Cria um mutex com contador = 1, informando que o recurso está disponível
  // após a inicialização
  // Prioridade máxima a acessar o recurso = priority
  if (OSMutexCreate(&LCD,priority) != ALLOC_EVENT_OK)
  {
    // Oh Oh
    // Não deveria entrar aqui !!!
    while(1){};
  };
}


//Função para adquirir direito exclusivo ao LCD
void acquire_lcd(void)
{
  // Aloca o recurso do display LCD
  OSMutexAcquire(LCD);
}

//Função para liberar o display LCD
void release_lcd(void)
{
  // Libera o recurso do display LCD
  OSMutexRelease (LCD);    
}


// Função para escrita de uma frase no display
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


// Função para escrita de um número de 2 digitos no display
void write_number_lcd(INT8U number)
{
  INT8U i = 0; 
  
  i = (number / 10);
  putchar_lcd('0' + i);      
  putchar_lcd('0' + (number - (i * 10)));
}


// Envia um comando para o módulo do display
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


// Envia um caractere para o módulo do display
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


// Inicialização do display para 2 linhas com caracteres de 5x7
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


// Função de posicionamento do cursor do display
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


// Função para limpar o display e retornar a primeira posição da primeira linha
void clear_lcd(void)
{  
  instr_lcd(0x01) ;
}


// Função de teste da busy flag
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
/* Função de delay em milisegundos                                      */
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
  
