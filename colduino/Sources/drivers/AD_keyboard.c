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
#include "OS_types.h"
#include "AD_keyboard.h"


INT8U FindKey(INT16U ADLevel)
{
	  INT8U key = NO_KEY;
      
      if ((ADLevel>=UP_KEY_L) && (ADLevel<=UP_KEY_H))
      {
        key=UP_KEY;
      }
      else
      {
        if ((ADLevel>=DOWN_KEY_L) && (ADLevel<=DOWN_KEY_H))
        {
        	key=DOWN_KEY;
        }
        else
        {
          if ((ADLevel>=LEFT_KEY_L) && (ADLevel<=LEFT_KEY_H))
          {
        	  key=LEFT_KEY;
          }
          else
          {
            if ((ADLevel>=RIGHT_KEY_L) && (ADLevel<=RIGHT_KEY_H))
            {
            	key=RIGHT_KEY;
            }
            else
            {
            if ((ADLevel>=ENTER_KEY_L) && (ADLevel<=ENTER_KEY_H))
            {
        	   key=ENTER_KEY;
            }
            else
            {
        	   if ((ADLevel>=CANCEL_KEY_L) && (ADLevel<=CANCEL_KEY_H))
        	   {
        		   key=CANCEL_KEY;
        	   }
		  } 
		} 
	  } 
	} 
  }     
      
  return(key);
}
