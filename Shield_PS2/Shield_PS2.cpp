#include "Arduino.h"
#include "HardwareSerial.h"
#include "Shield_PS2.h"
	


PS2::PS2()
{

}

void PS2::init(long baudrate, byte rx, byte tx)
{
	if(tx==1 && rx==0)
	{
		HW=true; 
		Serial.begin(baudrate); 
		while (!Serial) {
		; // wait for serial port to connect. Needed for Leonardo only
		}
	}
	
	else
	{
		 HW=false; 
		 pinMode(rx,INPUT); 
		 pinMode(tx,OUTPUT); 
		 mySerial=new SoftwareSerial(rx, tx); 			 
		 mySerial->begin(baudrate);
		 
	}
	pinMode(A1,OUTPUT);
	digitalWrite(A1,HIGH); 
	
	
}
void PS2::uart_send(byte data){
	
	if(HW)
	{
		while(Serial.available()>0)
		{	
			Serial.read();
		}
		Serial.write(data); 
		Serial.flush(); 	//wait for all data transmitted
	}
	else
	{
		while(mySerial->available()>0)
		{	
			mySerial->read();
		}
		mySerial->write(data); 
		
	}
}
byte PS2::uart_rec(void){

	byte rec_data; 
	long waitcount=0; 
	
	if(HW)
	{
		while(true)
		{
			if (Serial.available() > 0) {
				// read the incoming byte:
				rec_data = Serial.read();
				SERIAL_ERR=false; 
				return(rec_data); 
			}
			waitcount++; 
			if(waitcount>50000)
			{
				SERIAL_ERR=true; 
				return (0xFF); 
			}
		}
	}
	else
	{
		while(true)
		{
			if(mySerial->available()>0)
			{
				rec_data = mySerial->read();
				SERIAL_ERR=false; 
				return(rec_data); 
			}
			waitcount++; 
			if(waitcount>50000)
			{
				SERIAL_ERR=true; 
				return (0xFF); 
			}
			
		}	
	
	}
}

byte PS2::getval(byte key)
{
	uart_send(key); 
	return uart_rec(); 
}

boolean PS2::getall()
{
	byte nbyte; 
	long waitcount;
	
	

	uart_send(p_btn_joy);
	
	if(HW)
	{		
		nbyte=Serial.readBytes(ps_data, 6);
		
		if(nbyte==6)
			return(true); 
		else
			return (false);
	}
		
	else
	{	
		waitcount=0; 
		while(mySerial->available()<6)
		{		
			waitcount++; 
			if(waitcount>50000)
			{				
				return (false); 
			}
		
		}		
		for(int i=0; i<6; i++)
		{	
		 		
			ps_data[i]=mySerial->read();
		}
		
		return(true);	
	
	}
		
	
	
	

}
void PS2::vibrate(byte motor, byte val)
{
	byte m;
	if(motor==1)
		m=29; 
	else
		m=30;
		
	
	uart_send(m); 
	uart_send(val); 
}

void PS2::reset(byte rst)
{
	if(rst==1)
		digitalWrite(A1, LOW); 
	else
		digitalWrite(A1, HIGH); 

}