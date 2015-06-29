#include "hardware.h"
#include "DA.h"

#pragma warn_implicitconv off


////////////////////////////////////////////////
////////////////////////////////////////////////
///    Rotinas do D/A                        ///
////////////////////////////////////////////////
////////////////////////////////////////////////
void DASetup(void)
{ 
  // Configuração do A/D
  SCGC1 |= SCGC1_DAC_MASK;           			/* Enables dac clock */
  DACC0 = DACC0_DACEN_MASK | DACC0_DACRFS_MASK;
}




void DAConvert(INT16S data)
{
	DACDAT0 = data;
}

