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
#include "mcu_driver.h"


/*****************************************************************************
 * @name     MCU_Init
 *
 * @brief:   Initialization of the MCU.
 *
 * @param  : None
 *
 * @return : None
 *****************************************************************************
 * It will configure the MCU to disable STOP and COP Modules.
 * It also set the MCG configuration and bus clock frequency.
 ****************************************************************************/
void Mcu_Init()
{

#if ((defined _MCF51MM256_H) || (defined _MCF51JE256_H) || (defined _MCF51JE128_H))
    SOPT1 = 0x32; /* Enable COP; enable bkgd, stop and wait mode */
                /*
                 *  0b01110010
                 *    ||||||||__ bit0: RESET Pin Enable
                 *    |||||||___ bit1: Background Debug Mode Pin Enable
                 *    ||||||____ bit2: Mini-FlexBus Security Level
                 *    |||||_____ bit3: Boot Loader Mode Select Status, Read Only bit
                 *    ||||______ bit4: WAIT Mode Enable
                 *    |||_______ bit5: STOP Mode enable
                 *    ||________ bit6: COP Watchdog Timeout
                 *    |_________ bit7: COP Watchdog Timeout
                 */    
                 
    SOPT2 = 0x06; /* set right endianess for USB module */
    
    /* System Power Management Status and Control 1 Register */
    SPMSC1 = 0x1D;
                /*
                 *  0b01011101
                 *    ||||||||__ bit0: Bandgap buffer enabled
                 *    |||||||___ bit1: Reserved, Read Only bit
                 *    ||||||____ bit2: Low-Voltage Detect(LVD) logic disabled
                 *    |||||_____ bit3: LVD disabled during stop mode
                 *    ||||______ bit4: LVDF does not generate hardware resets
                 *    |||_______ bit5: Hardware interrupt disabled(use polling)
                 *    ||________ bit6: If LVWF = 1, a low-voltage
                 *    |                condition has occurred
                 *    |_________ bit7: Low-voltage warning is not present
                 */    
                 
    /* System Power Management Status and Control 2 Register */
    SPMSC2 = 0x00;
                        /*
                         *  0b00000000
                         *    ||||||||__ bit0:   PPDC       Partlal Power Down Control
                         *    |||||||___ bit1:   0
                         *    ||||||____ bit2:   PPDACK Partlal Power Down Acknowledge
                         *    |||||_____ bit3:   PPDF       partlal Power Down Flag
                         *    ||||______ bit4:   LVWV       Low-Voltage Warning Voltage Select
                         *    |||_______ bit5:   LVDV       Low_Voltage Detect Voltage select
                         *    ||________ bit6:   0
                         *    |_________ bit7:   0
                         */

#endif

    /*IO configuration*/
    PTAD  = 0x00;       /*PTA0--PTA7 are all available for JE256*/
    PTADD = 0x00;       /*Set input direction*/
    PTAPE = 0x00;       /*Pull-up disable*/
    PTASE = 0x00;       /*slew rate control*/
    PTADS = 0x00;       /*drive strength*/

    PTBD  = 0x00;       /*PTB0--PTB7 are all available for JE256*/
    PTBDD = 0x00;       /*Set input direction*/
    PTBPE = 0x00;       /*Pull-up disable*/
    PTBSE = 0x00;       /*slew rate control*/
    PTBDS = 0x00;       /*drive strength*/

    PTCD  = 0x00;       /*PTC0--PTC7 are all available for JE256*/
    PTCDD = 0x00;       /*Set input direction*/
    PTCPE = 0x00;       /*Pull-up disable*/
    PTCSE = 0x00;       /*slew rate control*/
    PTCDS = 0x00;       /*drive strength*/

    PTDD  = 0x00;       /*PTD0--PTD7 are all available for JE256*/
    PTDDD = 0x00;       /*Set input direction*/
    PTDPE = 0x00;       /*Pull-up disable*/
    PTDSE = 0x00;       /*slew rate control*/
    PTDDS = 0x00;       /*drive strength*/

    PTED  = 0x00;       /*PTE0--PTE7 are all available for JE256*/
    PTEDD = 0x00;       /*Set input direction*/
    PTEPE = 0x00;       /*Pull-up disable*/
    PTESE = 0x00;       /*slew rate control*/
    PTEDS = 0x00;       /*drive strength*/

    PTFD  = 0x00;       /*PTF0--PTF7 are all available for JE256*/
    PTFDD = 0x00;       /*Set input direction*/
    PTFPE = 0x00;       /*Pull-up disable*/
    PTFSE = 0x00;       /*slew rate control*/
    PTFDS = 0x00;       /*drive strength*/

    PTGD  = 0x00;       /*PTG0 is available for JE256/80 pins*/
    PTGDD = 0x00;       /*Set input direction*/
    PTGPE = 0x00;       /*Pull-up disable    */
    PTGSE = 0x00;       /*slew rate control*/
    PTGDS = 0x00;       /*drive strength */
}

/*****************************************************************************
 * @name     MCG_Init
 *
 * @brief:   Initialization of the Multiple Clock Generator.
 *
 * @param  : None
 *
 * @return : None
 *****************************************************************************
 * Provides clocking options for the device, including a phase-locked
 * loop(PLL) and frequency-locked loop (FLL) for multiplying slower reference
 * clock sources
 ****************************************************************************/
void MCG_Init()
{
#if ((defined _MCF51MM256_H) || (defined _MCF51JE256_H)|| (defined _MCF51JE128_H))
  /* Assume 12MHz external clock source connected. */
  
  /* In order to use the USB we need to enter PEE mode and MCGOUT set to 48 MHz. 
     Out of reset MCG is in FEI mode. */
  
  //------FBE MODE------  
  /* Assume 16MHz external clock source connected. */
  // RANGE = 1; HGO = 1; ERCLKEN=1; EREFS = 1; BDIV = 000
  MCGC2 = 0x36;
               /*
                *  0b00110110
                *    ||||||||__ bit0: External ref clock disabled in stop
                *    |||||||___ bit1: MCGERCLK active
                *    ||||||____ bit2: Oscillator requested
                *    |||||_____ bit3: FLL/PLL not disabled in bypass modes
                *    ||||______ bit4: Configure crystal oscillator for
                *    |||              high gain operation
                *    |||_______ bit5: High frequency range selected for
                *    ||               crystal oscillator of 1 MHz to 16 MHz
                *    ||________ bit6: Divides selected clock by 1
                *    |_________ bit7: Divides selected clock by 1
                */
  
  // DIV32 =1
  MCGC3 = 0x10;
               /*
                *  0b00010000
                *    ||||||||__ bit0: VCO Divider - Multiply by 32
                *    |||||||___ bit1: VCO Divider - Multiply by 32
                *    ||||||____ bit2: VCO Divider - Multiply by 32
                *    |||||_____ bit3: VCO Divider - Multiply by 32
                *    ||||______ bit4: Divide-by-32 is disabled
                *    |||_______ bit5: Clock monitor is disabled
                *    ||________ bit6: PLL is selected
                *    |_________ bit7: Generate an interrupt request on loss of lock
                */  
  
  // CLKS = 10; RDIV = 100; IREFS = 0;
  MCGC1 = 0xA0; 
               /*
                *  0b10100000
                *    ||||||||__ bit0: Internal ref clock stays enabled in stop
                *    |||||||          if IRCLKEN is set or if MCG is in FEI,
                *    |||||||          FBI or BLPI mode before entering stop.
                *    |||||||___ bit1: MCGIRCLK active
                *    ||||||____ bit2: External reference clock selected
                *    |||||_____ bit3: External Reference Divider
                *    ||||______ bit4: External Reference Divider
                *    |||_______ bit5: External Reference Divider
                *    ||________ bit6: External reference clock is selected
                *    |_________ bit7: External reference clock is selected
                */
#if (__GNUC__)

  // Wait for Reference Status bit to update
  while(MCGSC & MCGSC_IREFST_MASK){};

  // Wait for clock status bits to update
  while((MCGSC & MCGSC_CLKST_MASK) != (0b10 << MCGSC_CLKST_BITNUM)){};
#else
  // Wait for Reference Status bit to update
  while (MCGSC_IREFST){};
  
  // Wait for clock status bits to update 
  while (MCGSC_CLKST != 0b10){};
#endif




  //------PBE MODE------ 
  // PLLS =1; DIV32 = 1; VDIV = 1100 
  MCGC3 = 0x5C;
               /*
                *  0b01011100
                *    ||||||||__ bit0: VCO Divider - Multiply by 32
                *    |||||||___ bit1: VCO Divider - Multiply by 32
                *    ||||||____ bit2: VCO Divider - Multiply by 32
                *    |||||_____ bit3: VCO Divider - Multiply by 32
                *    ||||______ bit4: Divide-by-32 is disabled
                *    |||_______ bit5: Clock monitor is disabled
                *    ||________ bit6: PLL is selected
                *    |_________ bit7: Generate an interrupt request on loss of lock
                */    
#if (__GNUC__)
  // wait for PLL status bit to update
  while(!(MCGSC & MCGSC_PLLST_MASK)){};
  
  // Wait for LOCK bit to set
  while(!(MCGSC & MCGSC_LOCK_MASK)){};
#else
  // wait for PLL status bit to update
  while (!MCGSC_PLLST){};
  
  // Wait for LOCK bit to set 
  while (!MCGSC_LOCK){};
#endif


  
  //------PEE MODE------   
  // CLKS = 00; RDIV = 100; IREFS = 0
  MCGC1 = 0x20;
               /*
                *  0b00100000
                *    ||||||||__ bit0: Internal ref clock stays enabled in stop
                *    |||||||          if IRCLKEN is set or if MCG is in FEI,
                *    |||||||          FBI or BLPI mode before entering stop.
                *    |||||||___ bit1: MCGIRCLK active
                *    ||||||____ bit2: External reference clock selected
                *    |||||_____ bit3: External Reference Divider
                *    ||||______ bit4: External Reference Divider
                *    |||_______ bit5: External Reference Divider
                *    ||________ bit6: External reference clock is selected
                *    |_________ bit7: External reference clock is selected
                */  
#if (__GNUC__)
  while((MCGSC & MCGSC_CLKST_MASK) != (0b11 << MCGSC_CLKST_BITNUM)){};
#else
  // Wait for clock status bits to update 
  while (MCGSC_CLKST != 0b11){};
#endif

#endif
}


/*****************************************************************************
 *
 *    @name     System_Init
 *
 *    @brief    This function Initializes the system
 *
 *    @param    None
 *
 *    @return   None
 *
 ****************************************************************************
 * Intializes the MCU, MCG, KBI, RTC modules
 ***************************************************************************/
void System_Init(void)
{
    Mcu_Init(); /* initialize the MCU registers */
    MCG_Init(); /* initialize the MCG to generate 24MHz bus clock */
}
