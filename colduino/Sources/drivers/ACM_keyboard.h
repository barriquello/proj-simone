#include "BRTOS.h"

extern BRTOS_Sem *sKeyboard;

////////////////////////////////////////////////
////////////////////////////////////////////////
///    Rotinas do ACM                        ///
////////////////////////////////////////////////
//////////////////////////////////////////////// 

#define Enable  1
#define Disable 0

#define External  1
#define Internal 0

#define FallingAndRising 0
#define Falling 1
#define Rising  2

#define ACM_CHANNEL0	1
#define ACM_CHANNEL1	2
#define ACM_CHANNEL2	4
#define ACM_CHANNEL3	8
#define ACM_CHANNEL4	16
#define ACM_CHANNEL5	32
#define ACM_CHANNEL6	64

void ACM_Keyb_Setup(unsigned char State, unsigned char Interrupt, unsigned char Mode, unsigned char channel);
void ACMEnable(void);  
void ACMDisable(void);
void Analog_comparator(void);
              
  // State - ENABLE/DISABLE
  // Bandgap - INTERNAL/EXTERNAL
  // Interrupt - ENABLE/DISABLE
  // Output - Output the state of ACM: ENABLE/DISABLE
  // MODE - Mode of detection: Rising, Falling, FallingAndRising     
              
