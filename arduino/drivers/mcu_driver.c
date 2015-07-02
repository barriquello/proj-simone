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

  // Clock Init
  // Make clock go 16MHz
  CLKPR = 0x80;        // Initiate write cycle for clock setting
  CLKPR = 0x00;        // 16 MHz clock. Clock division factor = 1
  
  // Disable the watchdog timer
  wdt_disable();
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

}


/*****************************************************************************
 *
 *    @name     Init_Sys
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
void Init_Sys(void)
{
    Mcu_Init(); /* initialize the MCU registers */
    MCG_Init(); /* initialize the MCG to generate 24MHz bus clock */
}
