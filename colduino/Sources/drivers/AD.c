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
* \file ad.c
* \brief Microcontroller drivers
*
* This file contain the A/D drivers.
*
**/

#include "hardware.h"
#include "AD.h"
#include "BRTOS.h"

#if !__GNUC__
#pragma warn_implicitconv off
#endif


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

INT16U AD_get_core_temp(void)
{
	INT16U digital_temp = 0;
	INT16U bandgap = 0;
	INT16S temperature = 0;
	
	/* Mede temperatura do core */
	UserEnterCritical();
		digital_temp = ADConvert(TEMP_SENSOR_CH);
	UserExitCritical();

	UserEnterCritical();
		bandgap = ADConvert(BANDGAP_CH);
	UserExitCritical();

	digital_temp = (1170 * digital_temp) / bandgap;

	if (digital_temp > 701)
	{
		temperature = 25 - (INT16S)(((digital_temp - 701) * 1000) / 1646);
	}
	else
	{
		temperature = 25 - (INT16S)(((digital_temp - 701) * 1000) / 1769);
	}

	return (INT16U)temperature;
	
}

