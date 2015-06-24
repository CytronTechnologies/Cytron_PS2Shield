//Cytron PS2 Shield (SHIELD-PS2)
//www.cytron.com.my
//sample code to retrieve a btn status on PS2 Controller
 
#include <Shield_PS2.h>

//declare class objects
PS2 ps2=PS2();                    //PS2 class object: ps2

#define LEDPIN 13


void setup()
{
  
   ps2.init(9600, 2, 3);   //initialize the main board to use desired (baudrate, rx, tx)
                           //for Arduino Mega use RX:10, TX: 11 for software serial
                           //for Arduino Leonardo use pin 8, 9, 10, 11 as RX and TX for software serial
                             
                             
   pinMode(LEDPIN, OUTPUT); 
   digitalWrite(LEDPIN,LOW);    
      
}

void loop()
{
  
  if( ps2.getval(p_select)==0)      //LED on Main Board will light up if Select button is pressed
  {
    digitalWrite(LEDPIN,HIGH); 
  }
  else 
  {
    digitalWrite(LEDPIN,LOW); 
  }
  
  
  
}
