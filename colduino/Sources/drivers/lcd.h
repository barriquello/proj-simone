/**
* \file lcd.h
* \brief Alphanumeric LCD function prototypes.
*
*
**/

// Número de bits de dados do barramento do LCD
#define LCD_DATA_BUS              4
#define LCD_USE_BRTOS             1
#define LCD_CPU_CLOCK             24000000
#define LCD_FOR_NUMBER_OF_CYCLES  19

// Definições para escolha dos pinos da porta do microcontrolador
#define RS            PTDD_PTDD2
#define RS_DIR        PTDDD_PTDDD2
#define E             PTDD_PTDD3
#define E_DIR         PTDDD_PTDDD3
#if (LCD_DATA_BUS != 4)
	#define RW            PTDD_PTDD1
	#define RW_DIR        PTDDD_PTDDD1
#endif
#define DATA          PTDD
#define DATA_DIR      PTDDD
#define BUSY_FLAG     PTDD_PTDD7
#define DATA_SHIFT	  0

#define BACKLIGHT_DIR PTCDD_PTCDD7
#define BACKLIGHT	  PTCD_PTCD7



#define  delay_450ns()      asm   \
                            {     \
                              nop \
                              nop \
                              nop \
                              nop \
                              nop \
                              nop \
                              nop \
                              nop \
                              nop \
                              nop \
                              nop \
                            }
                            

#define  delay_600ns()      asm   \
                            {     \
                              nop \
                              nop \
                              nop \
                              nop \
                              nop \
                              nop \
                              nop \
                              nop \
                              nop \
                              nop \
                              nop \
                              nop \
                              nop \
                              nop \
                              nop \
                            }

void printf_lcd(char *string);
void instr_lcd(char comando);
void putchar_lcd(char dado);
void write_number_lcd(unsigned char numero);
void init_lcd(void);
void init_resource_lcd(unsigned char priority);
void acquire_lcd(void);
void release_lcd(void);
void xy_position_lcd(unsigned char linha, unsigned char coluna);
void clear_lcd(void);
void Delay_ms(unsigned int DelayTime);
