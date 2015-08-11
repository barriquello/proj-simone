#include "BRTOS.h"
#include "drivers.h"
#include "tasks.h"
#include "AppConfig.h"

#ifdef __cplusplus
extern "C"
#endif

/******************************************************************************
 * @file main.c
 * @author Carlos H. Barriquello
 * @brief  This is the main entry point of the software
 *****************************************************************************/

#if ((defined _MCF51MM256_H) || (defined _MCF51JE256_H) || (defined _MCF51JE128_H))
const unsigned char boot:0x040A = 0x00;   //zero out checksum to bypass boot loader
#endif /* (defined _MCF51MM256_H) || (defined _MCF51JE256_H) */

/******************************************************************************
 * @name        main
 * @brief       This function calls the application
 * @param       None
 * @return      None
 *****************************************************************************/
void main(void)
{

	main_app();
	
	for (;;)
	{
		__RESET_WATCHDOG();
		/* __RESET_WATCHDOG(); by default, COP is disabled with device init. When enabling, also reset the watchdog. */
	} /* loop forever */
}

