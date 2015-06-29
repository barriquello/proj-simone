////////////////////////////////////////////////
////////////////////////////////////////////////
///    Rotinas do A/D                        ///
////////////////////////////////////////////////
////////////////////////////////////////////////
#define NormalPower  0
#define LowPower     1

#define NormalSpeed  0
#define HighSpeed    1

#define ShortSampleTime 0
#define LongSampleTime  1

#define AD_MAX_CLOCK      8000000


#define TEMP_SENSOR_CH    26
#define BANDGAP_CH        27
#define VREFH_CH          29
#define ADC_OFF           31


void ADSetup(unsigned char ADLowPower, unsigned char ADSpeed, unsigned char SampleTime, unsigned char LongSampleTimeSelect, unsigned char NumBits);
unsigned short int ADConvert(unsigned char canal);
