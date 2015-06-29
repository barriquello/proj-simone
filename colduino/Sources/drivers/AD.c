/**
* \file ad.c
* \brief Microcontroller drivers
*
* This file contain the A/D drivers.
*
**/

#include "hardware.h"
#include "AD.h"
#include "BRTOS.h"

#pragma warn_implicitconv off


////////////////////////////////////////////////
////////////////////////////////////////////////
///    Rotinas do A/D                        ///
////////////////////////////////////////////////
//////////////////////////////////////////////// 
void ADSetup(INT8U ADLowPower, INT8U ADSpeed, INT8U SampleTime, INT8U LongSampleTimeSelect, INT8U NumBits)
{
  INT8U ADconfig = 0;
  INT8U ADconfig2 = 0;
  
  // Configuração do A/D
  SCGC1  |= SCGC1_ADC_MASK;           /* Enables adc clock */
  
  /* Disable HW trigger and autocompare */
  ADCSC2 = 0x00;
  
  
  // Low power option
  if (ADLowPower == LowPower) 
  {
    ADconfig = ADconfig | 0x80;
  }else 
  {
    ADconfig = ADconfig & 0x7F;  
  }

  
  // Speed option
  if (ADSpeed == HighSpeed) 
  {
    ADconfig2 = ADconfig2 | 0x04;
  }else 
  {
    ADconfig2 = ADconfig2 & 0xFB;
  }  
  
  // Sample time option
  if(SampleTime == LongSampleTime) 
  {
    ADconfig = ADconfig | 0x10;  
  }else 
  {
    ADconfig = ADconfig & 0xEF;    
  }  
       
  
  // AD clock option
  if ((configCPU_CLOCK_HZ) < AD_MAX_CLOCK)
  {  
    ADconfig = ADconfig & 0x9F;
  }
  else
  {
    if ((configCPU_CLOCK_HZ >> 1) < AD_MAX_CLOCK)
    {  
      ADconfig = ADconfig | 0x20;
    } else
    {
      if ((configCPU_CLOCK_HZ >> 2) < AD_MAX_CLOCK)
      {
        ADconfig = ADconfig | 0x40;
      }else
      {
        if ((configCPU_CLOCK_HZ >> 3) < AD_MAX_CLOCK)
          ADconfig = ADconfig | 0x60;
      }
    }
  }     
  
  switch(NumBits)
  {
    case 8:
      ADconfig = ADconfig & 0xF3;
      break;
    case 10:
      ADconfig = ADconfig | 0x08;
      break;
    case 12:
      ADconfig = ADconfig | 0x04;
      break;
    default:
      break;    
  }
  
  switch(LongSampleTimeSelect)
  {
    case 20:
      ADconfig2 = ADconfig2 & 0xFC;
      break;
    case 12:
      ADconfig2 = ADconfig2 | 0x01;
      break;
    case 6:
      ADconfig2 = ADconfig2 | 0x02;
      break;
    case 2:
      ADconfig2 = ADconfig2 | 0x03;
      break;      
    default:
      break;    
  }  
        
  
  /* ADC1CFG: ADLPC=0,ADIV1=1,ADIV0=0,ADLSMP=0,MODE1=1,MODE0=0,ADICLK1=0,ADICLK0=0 */
  ADCCFG1 = ADconfig;              /* Set prescaler bits */ 
  
  ADCCFG2 = ADconfig2;              

  /* ADC1SC1: COCO=0,AIEN=0,ADCO=0,ADCH4=1,ADCH3=1,ADCH2=1,ADCH1=1,ADCH0=1 */
  ADCSC1 = ADC_OFF;              /* Disable the module */
}




INT16U ADConvert(INT8U canal)
{
  INT16U return_ad = 0;
  ADCSC1 = (INT8U)(canal);    /* Inicia a medida de um canal */
  while(!ADCSC1_COCO){};
  
  return_ad = ADCR;
  ADCSC1 = 0x1F;
  return return_ad;
}

