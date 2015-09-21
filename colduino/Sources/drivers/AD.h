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
////////////////////////////////////////////////
////////////////////////////////////////////////
///    Rotinas do A/D                        ///
////////////////////////////////////////////////
////////////////////////////////////////////////

#include "BRTOs.h"

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


void ADSetup(INT8U ADLowPower, INT8U ADSpeed, INT8U SampleTime, INT8U LongSampleTimeSelect, INT8U NumBits);
INT16U ADConvert(INT8U canal);
INT16U AD_get_core_temp(void);
