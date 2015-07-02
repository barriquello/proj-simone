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
 * @version
 * @date
 * @brief   This software is the GPRS_TRAFO project for Coldfire V1 JE256
 *****************************************************************************/

#if ((defined _MCF51MM256_H) || (defined _MCF51JE256_H) || (defined _MCF51JE128_H))
/* checksum bypass */
const unsigned char boot:0x040A = 0x00;   //zero out checksum to bypass boot loader


#endif /* (defined _MCF51MM256_H) || (defined _MCF51JE256_H) */

/******************************************************************************
 * @name        main
 * @brief       This function initializes the system, enables the interrupts and calls the application
 * @param       None
 * @return      None
 *****************************************************************************/
void main_app(void);

void main(void)
{

	main_app();
	
	for (;;)
	{
		__RESET_WATCHDOG();
		/* __RESET_WATCHDOG(); by default, COP is disabled with device init. When enabling, also reset the watchdog. */
	} /* loop forever */
	/* please make sure that you never leave main */
}

