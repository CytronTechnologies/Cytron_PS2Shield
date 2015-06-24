//Cytron PS2 Shield (SHIELD-PS2)
//www.cytron.com.my
//sample code to display all buttons & joystick values to the LCD keypad Shield

#include <LCD4Bit_mod.h> 
#include <Shield_PS2.h>

//declare class objects
LCD4Bit_mod lcd = LCD4Bit_mod(2); //LCD4Bit_mod object : lcd
PS2 ps2=PS2();                    //PS2 class object: ps2

#define LEFT_BTN_MASK 128
#define DOWN_BTN_MASK 64

void setup()
{
 lcd.init();  
 lcd.clear();  
 
 ps2.init(9600, 0, 1);   //initialize the main board to use desired (baudrate, rx, tx)

 ps2.reset(1);             //call to reset Shield-PS2
 ps2.reset(0);
 
 lcd.cursorTo(1, 0);       //display welcome message
 lcd.printIn("Cytron ");
 
 lcd.cursorTo(2, 0);
 lcd.printIn("SHIELD-PS2 ");
  
  delay(2000); 
  
  lcd.clear();
  
}

void loop()
{
  
  if(ps2.getall()==true)      //get all buttons and joystick status
  {
    //print every button status: 1= not pressed, 0 = pressed (refer usermanual of Shield-PS2)
    /*Group 1 
      bit 7 (MSB): Left button
      bit 6: Down button
      bit 5: Right button
      bit 4: Up button
      bit 3: Start button
      bit 2: Right Joystick Center button
      bit 1: Left Joystick Center button
      bit 0 (LSB): Select button
    */
    /*Group 2
      bit 7 (MSB): Square button
      bit 6: Cross button
      bit 5: Circle button
      bit 4: Triangle button
      bit 3: R1 button
      bit 2: L1 button
      bit 1: R2  button
      bit 0: L2 button
      */
    
    lcd.cursorTo(1, 0);
    p_bin(ps2.ps_data[0]); 
    p_bin(ps2.ps_data[1]); 
    lcd.cursorTo(2, 0);
    
    //print both joysticks values on each axes.
    p_dec(ps2.ps_data[2]);   lcd.printIn(" ");
    p_dec(ps2.ps_data[3]);   lcd.printIn(" ");
    p_dec(ps2.ps_data[4]);   lcd.printIn(" ");
    p_dec(ps2.ps_data[5]);   lcd.printIn(" ");
    
    //test vibration motor on PS2 
    if( (ps2.ps_data[0]&LEFT_BTN_MASK) ==0)    //if Left button pressed Motor 1 vibrate
    {
        lcd.cursorTo(2, 15);
        lcd.printIn("v");        
        ps2.vibrate(1,1); 
    }
    else
    {
      lcd.cursorTo(2, 15);
      lcd.printIn(" ");
      ps2.vibrate(1,0); 
    }    
    if( (ps2.ps_data[0]&DOWN_BTN_MASK) ==0)    //if Down button pressed Motor 2 vibrate
    {
        lcd.cursorTo(2, 15);
        lcd.printIn("v");        
        ps2.vibrate(2,255); 
    }
    else
    {
      lcd.cursorTo(2, 15);
      lcd.printIn(" ");
      ps2.vibrate(2,0); 
    }
 
  }
  else    //not valid packet received
  {
    lcd.cursorTo(0, 0);
    lcd.printIn("False");
  }
  
  
}



//Simple Function to print 8bits binary
void p_bin(char val)
{
  byte data=byte(val); 
  
  byte mask=128; 
  for(int i=0; i<8; i++)
  {       
    if((mask&data)==0)
      lcd.printIn("0");
    else
       lcd.printIn("1");
       
    mask=mask>>1;     
  }   
}

//Simple function to print 3 digit decimal
void p_dec(char val)
{
  byte data=byte(val); 
  char str[]={' ',0}; 
  
  str[0]=data/100 +'0'; 
  lcd.printIn(str);
  data%=100; 
  str[0]=data/10 +'0'; 
  lcd.printIn(str);
  data%=10; 
  str[0]=data +'0'; 
  lcd.printIn(str);
  
}
