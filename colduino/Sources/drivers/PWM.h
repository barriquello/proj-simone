////////////////////////////////////////////////
////////////////////////////////////////////////
///    Definições dos Módulos PWM            ///
////////////////////////////////////////////////
////////////////////////////////////////////////


#define LeftAlign   0
#define CenterAlign 1

#define PositiveDutyCyclePolarity 1
#define NegativeDutyCyclePolarity 0

void PWMSetup(unsigned char TPM_Number,  unsigned short int Frequency, unsigned short int Align,
              unsigned char ChannelZero, unsigned short int DutyZero,  unsigned short int PolarityZero, 
              unsigned char ChannelOne,  unsigned short int DutyOne,   unsigned short int PolarityOne,
              unsigned char ChannelTwo,  unsigned short int DutyTwo,   unsigned short int PolarityTwo);