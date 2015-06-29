/**
* \file ad.c
* \brief Microcontroller drivers
*
* This file contain the PWM drivers.
*
**/

#include "hardware.h"
#include "BRTOS.h"
#include "PWM.h"

#pragma warn_implicitconv off

////////////////////////////////////////////////
////////////////////////////////////////////////
///    Rotinas do Módulo PWM TPM             ///
////////////////////////////////////////////////
////////////////////////////////////////////////
 
void PWMSetup(INT8U TPM_Number, INT16U Frequency, INT16U Align,
              INT8U ChannelZero, INT16U DutyZero,INT16U PolarityZero, 
              INT8U ChannelOne,   INT16U DutyOne,   INT16U PolarityOne,
              INT8U ChannelTwo,   INT16U DutyTwo,   INT16U PolarityTwo)
{
  INT16U module = 0;  
  INT8U prescale = 0;
  INT32U duty = 0;
  INT8U mode = 0;

  
  if ((TPM_Number == 1) || (TPM_Number == 2)) 
  {
    /* ### Init_TPM init code */  
    for (prescale = 0;prescale <=7;prescale++)
    {
      if (Align == LeftAlign)
        module = (configCPU_CLOCK_HZ / Frequency) >> prescale;
      
      if (Align == CenterAlign)
        module = (configCPU_CLOCK_HZ / Frequency) >> (prescale + 1);
    
      if (module < 0xFFFF)
         break;
    }
    
    
    /* TPM3SC: TOF=0,TOIE=0,CPWMS=0,CLKSB=0,CLKSA=0,PS2=0,PS1=0,PS0=0 */
    switch(TPM_Number)
    {
      case 1:
        SCGC1  |= SCGC1_TPM1_MASK;           /* Enables tpm1 clock */
        TPM1SC  = 0x00;                      /* Stop and reset counter */
        TPM1MOD = module;                    /* Period value setting */
        break;      
      case 2:
        SCGC1  |= SCGC1_TPM2_MASK;           /* Enables tpm2 clock */
        TPM2SC  = 0x00;                      /* Stop and reset counter */
        TPM2MOD = module;                    /* Period value setting */
        break;
      default:
        break;                  
    }
    
    if (ChannelZero == 1)
    {
      if (TPM_Number == 1) 
      {
        (void)(TPM1C0SC == 0);               /* Channel 0 int. flag clearing (first part) */  
      
        if(PolarityZero == PositiveDutyCyclePolarity)
          mode = 0x28;
        else
          mode = 0x24;
        
        TPM1C0SC = mode;                     /* Int. flag clearing (2nd part) and channel 0 contr. register setting */
        TPM1C0V = (module * DutyZero) / 100; /* Compare 0 value setting */
      }
      
      if (TPM_Number == 2) 
      {
        (void)(TPM2C0SC == 0);               /* Channel 0 int. flag clearing (first part) */  
      
        if(PolarityZero == PositiveDutyCyclePolarity)
          mode = 0x28;
        else
          mode = 0x24;
        
        TPM2C0SC = mode;                     /* Int. flag clearing (2nd part) and channel 0 contr. register setting */
        TPM2C0V = (module * DutyZero)/100;
      }
      
    }
    
    if (ChannelOne == 1)
    {
      if (TPM_Number == 1) 
      {  
        (void)(TPM1C1SC == 0);               /* Channel 0 int. flag clearing (first part) */  
      
        if(PolarityOne == PositiveDutyCyclePolarity)
          mode = 0x28;
        else
          mode = 0x24;    

        TPM1C1SC = mode;                     /* Int. flag clearing (2nd part) and channel 0 contr. register setting */
        TPM1C1V = (module * DutyOne) / 100; /* Compare 0 value setting */
      }
      
      if (TPM_Number == 2) 
      {  
        (void)(TPM2C1SC == 0);               /* Channel 0 int. flag clearing (first part) */  
      
        if(PolarityOne == PositiveDutyCyclePolarity)
          mode = 0x28;
        else
          mode = 0x24;    

        TPM2C1SC = mode;                     /* Int. flag clearing (2nd part) and channel 0 contr. register setting */
        TPM2C1V = (module * DutyOne) / 100; /* Compare 0 value setting */
      }    
    }
    
    if (ChannelTwo == 1)
    {
      if (TPM_Number == 1) 
      {  
        (void)(TPM1C2SC == 0);               /* Channel 0 int. flag clearing (first part) */  
      
        if(PolarityTwo == PositiveDutyCyclePolarity)
          mode = 0x28;
        else
          mode = 0x24;
        
        TPM1C2SC = mode;                     /* Int. flag clearing (2nd part) and channel 0 contr. register setting */
        TPM1C2V = (module * DutyTwo) / 100; /* Compare 0 value setting */
      }
      
      if (TPM_Number == 2) 
      {  
        (void)(TPM2C2SC == 0);               /* Channel 0 int. flag clearing (first part) */  
      
        if(PolarityTwo == PositiveDutyCyclePolarity)
          mode = 0x28;
        else
          mode = 0x24;
        
        TPM2C2SC = mode;                     /* Int. flag clearing (2nd part) and channel 0 contr. register setting */
        TPM2C2V = (module * DutyTwo) / 100; /* Compare 0 value setting */
      }          
    }
    
       
    switch(TPM_Number)
    {
      case 1:
        (void)TPM1SC;                       /* Stop and reset counter */
        if (Align == LeftAlign) 
          TPM1SC = 0x08 + prescale;            /* Int. flag clearing (2nd part) and timer control register setting */
        if (Align == CenterAlign) 
          TPM1SC = 0x28 + prescale;            /* Int. flag clearing (2nd part) and timer control register setting */      
        break;
      case 2:
        (void)TPM2SC;                       /* Stop and reset counter */
        if (Align == LeftAlign) 
          TPM2SC = 0x08 + prescale;            /* Int. flag clearing (2nd part) and timer control register setting */
        if (Align == CenterAlign) 
          TPM2SC = 0x28 + prescale;            /* Int. flag clearing (2nd part) and timer control register setting */      
        break;
      default:
        break;                  
    }     
  }
}