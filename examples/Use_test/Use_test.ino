#include <touchExt.h>
// Please don't use delay() function in your code 
#define TOUCH_UMBRAL 60
//#define touchExt tb

touchExt button1(0, TOUCH_UMBRAL);
touchExt button2(39,400,ADC_PULLDOWN);
touchExt button3(1,4000,ADC_PULLUP);


void setup() 
{
   Serial.begin(115200);
}

void loop() 
{
   if(button1.isTouched()  ){  Serial.println("Touch button 1");    }
   if(button2.isClick()){   Serial.println("click button 2");    }
   if(button3.isReleased()){   Serial.println("relase button3");    }
}
