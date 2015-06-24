#ifndef Shield_PS2_h
#define Shield_PS2_h

#include "Arduino.h"
#include "SoftwareSerial.h"

//Arduino Leonardo
#if defined (__AVR_ATmega32U4__)
	#define Serial Serial1
#else 
	#define Serial Serial
#endif

//#definitions
#define p_select 0
#define p_joyl 	 1
#define p_joyr 	2
#define p_start 3
#define p_up	4
#define p_right 5
#define p_down	6
#define p_left	7
#define p_l2	8
#define p_r2	9
#define p_l1	10
#define p_r1	11
#define p_triangle	12
#define p_circle	13
#define p_cross		14
#define p_square	15
#define p_joy_lx	16
#define p_joy_ly	17
#define p_joy_rx	18
#define p_joy_ry	19
#define p_joy_lu	20
#define p_joy_ld	21
#define p_joy_11	22
#define p_joy_lr	23
#define p_joy_ru	24
#define p_joy_rd	25
#define p_joy_rl	26
#define p_joy_rr	27

#define p_con_status	28
#define p_motor1		29
#define p_motor2		30
#define p_btn_joy		31



class PS2
{
	public:
	boolean SERIAL_ERR;
	char ps_data[6]; 
	
	
	//constructor
	PS2();	
	
	//init function
	void init(long baudrate, byte rx, byte tx);	
	byte getval(byte key);
	boolean getall(); 
	void vibrate(byte motor, byte val);
	void reset(byte rst);

	
	protected:
	boolean HW;
	SoftwareSerial* mySerial;	
	void uart_send(byte data);
	byte uart_rec(void); 
	
	
};


	


#endif




