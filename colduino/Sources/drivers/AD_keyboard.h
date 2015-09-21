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
#define KEYB_CHANNEL		 10
#define AD_KEY_RANGE		 50	// 0,04V @ (3,3V, 12 bits)

#define ENTER_KEY          	 (INT8U)11
#define CANCEL_KEY         	 (INT8U)12
#define UP_KEY         		 (INT8U)13
#define DOWN_KEY         	 (INT8U)14
#define LEFT_KEY         	 (INT8U)15
#define RIGHT_KEY         	 (INT8U)16
#define NO_KEY             	 (INT8U)255

#define UP_KEY_L           	 (INT16U)(1009 - AD_KEY_RANGE)
#define UP_KEY_H             (INT16U)(1009 + AD_KEY_RANGE)
#define DOWN_KEY_L           (INT16U)(561 - AD_KEY_RANGE)
#define DOWN_KEY_H           (INT16U)(561 + AD_KEY_RANGE)
#define LEFT_KEY_L           (INT16U)(278 - AD_KEY_RANGE)
#define LEFT_KEY_H           (INT16U)(278 + AD_KEY_RANGE)
#define RIGHT_KEY_L          (INT16U)(807 - AD_KEY_RANGE)
#define RIGHT_KEY_H          (INT16U)(807 + AD_KEY_RANGE)
#define ENTER_KEY_L          (INT16U)(1188 - AD_KEY_RANGE)
#define ENTER_KEY_H          (INT16U)(1188 + AD_KEY_RANGE)
#define CANCEL_KEY_L         (INT16U)0
#define CANCEL_KEY_H         (INT16U)AD_KEY_RANGE


INT8U FindKey(INT16U ADLevel);

