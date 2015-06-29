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
