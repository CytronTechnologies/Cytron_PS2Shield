/*
  Cytron_PS2_Shield.cpp - Library to deal with Cytron PS2 Controller Module.
  Copyright (c) 2018 RoboManipal. All right reserved
  File created by : Shashank Goyal
*/

#include "Cytron_PS2_Shield.h"

// ############# Private Member Functions #########################
// Default Write Function for Sending Value to the PS2
void Cytron_PS2_Shield::write(uint8_t data)
{
	// Default Implemtation of the Function
	while(PS2Serial->available() > 0) 
	{	
		PS2Serial->read();
	}
	PS2Serial->write(data);
	PS2Serial->flush();
}

// Default Read Function for Receiving Value from the PS2
uint8_t Cytron_PS2_Shield::read(void)
{
	// Default Implemtation of the Function
	uint8_t rec_data; 
	long waitcount = 0; 
	
	while(true)
	{
		if(PS2Serial->available() > 0)
		{
			rec_data = PS2Serial->read();
			return(rec_data);
		}
		waitcount++; 
		if(waitcount > 50000)
		{
			return (0xFF); 
		}
	}
	
}

// ################### Constructors #######################
Cytron_PS2_Shield::Cytron_PS2_Shield() 
{
	// Empty constructor
}

Cytron_PS2_Shield::Cytron_PS2_Shield(Stream *AttachedSerial) 
{
	// Connect PS2 Serial
	this->AttachPS2Serial(AttachedSerial);
}

Cytron_PS2_Shield::Cytron_PS2_Shield(int Joystick)
{
	// Select Joystick for the Motion
	this->SetJoystick(Joystick);
}

Cytron_PS2_Shield::Cytron_PS2_Shield(Stream *AttachedSerial,int	Joystick)
{
	// Connect PS2 Serial
	this->AttachPS2Serial(AttachedSerial);
		// Select Joystick for the Motion
	this->SetJoystick(Joystick);
}

// ############# Member Functions #########################
// Attach Serial
void Cytron_PS2_Shield::AttachPS2Serial(Stream *AttachedSerial) 
{
	// Connect PS2 Serial
	this->PS2Serial = AttachedSerial;
	// Debugger message (level: INFO)
	this->debugger.print("PS2 Serial attached", INFO);
}

// Set which Joystick is being used.
void Cytron_PS2_Shield::SetJoystick(int Joystick) 
{
	// Select Joystick
	this->Joystick = Joystick;
	// Debugger message (level: INFO)
	String msg = "Joystick set as ";
	msg.concat(Joystick);
	this->debugger.print(msg, INFO);
}

// Fetch Data from PS2 and Update Class Variables
void Cytron_PS2_Shield::UpdateData()
{
	// Check which Joystick is being used 
	if(Joystick == RIGHT_JOYSTICK)
	{
		this->Axis_raw_values[X_AXIS] = this->readButton(PS2_JOYSTICK_RIGHT_X_AXIS);
		this->Axis_raw_values[Y_AXIS] = this->readButton(PS2_JOYSTICK_RIGHT_Y_AXIS);
	}

	else if(Joystick == LEFT_JOYSTICK)
	{
		this->Axis_raw_values[X_AXIS] = this->readButton(PS2_JOYSTICK_LEFT_X_AXIS);
		this->Axis_raw_values[Y_AXIS] = this->readButton(PS2_JOYSTICK_LEFT_Y_AXIS);
	} 

	else
	{
		debugger.print(ERROR, "Unknown Joystick Attached");
		return ; 
	}	

	// ------------------- Raw Values ------------------------------
	// Debugger message (Level: DEBUG)
	// X_AXIS: %X_AXIS_VALUE% Y_AXIS: %Y_AXIS_VALUE%
	// For example:
	// X_AXIS: 180 Y_AXIS: 100
	String msg = "Raw Axis Values ";
	msg.concat(" X_AXIS: ");
	msg.concat(this->Axis_raw_values[X_AXIS]);
	msg.concat(" Y_AXIS: ");
	msg.concat(this->Axis_raw_values[Y_AXIS]);
	debugger.print(DEBUG,msg);

	// ---------------- Full Scaled Values ------------------------
	// Debugger message (Level: DEBUG)
	// Full scale Axis Values: %FS_X_AXIS% %FS_Y_AXIS%
	msg = "Full scale Axis Values ";
	// Centering the Axis Values to zero at Mid Point of the Joystick 
	int tempX = this->Axis_raw_values[X_AXIS] - 128;
	int tempY = 127 - this->Axis_raw_values[Y_AXIS];
	// Temporary Variables - 
	float rad = pow((pow(tempX,2)+pow(tempY,2)),0.5);
	// Mapping the Square Coordintae System to Circular Coordinte System -
	int Mult = (tempX*tempX>tempY*tempY) ? tempX : tempY;
	Mult *= sgnm(Mult);
	this->Axis_scaled_values[X_AXIS] = ( tempX * Mult) / rad;
	this->Axis_scaled_values[Y_AXIS] = ( tempY * Mult) / rad;

	msg.concat(" X_AXIS: ");
	msg.concat(this->Axis_scaled_values[X_AXIS]);
	msg.concat(" Y_AXIS: ");
	msg.concat(this->Axis_scaled_values[Y_AXIS]);
	debugger.print(DEBUG,msg);

	// ---------------- Polar Values -------------------------------
	// Debugger message (Level: DEBUG)
	// Full scale Polar Values: %POLAR_RADIUS% %POLAR_ANGLE%

	// Angle = arcTan(X_AXIS/Y_AXIS)
	// Angle Values in Radian
	this->Polar_values[ANGLE]=atan2(tempY,tempX)-PI/2;
	// To make Angles Positive
	if(this->Polar_values[ANGLE]<0)
		this->Polar_values[ANGLE] += 2*PI;
		// Radius = sqrt(X_AXIS^2 + Y_AXIS^2)
	this->Polar_values[RADIUS]=pow((pow(this->Axis_scaled_values[X_AXIS],2)+pow(this->Axis_scaled_values[Y_AXIS],2)),0.5);
		// Conversion to Degrees and Phase Shift by 90 Degrees
	this->Polar_values[ANGLE] *=180/PI;
	if(this->Polar_values[RADIUS] == 0)
		this->Polar_values[ANGLE] = 0;
	msg = "Full scale Polar Values ";
	msg.concat(" RADIUS: ");
	msg.concat(this->Polar_values[RADIUS]);
	msg.concat(" ANGLE: ");
	msg.concat(this->Polar_values[ANGLE]);
	debugger.print(DEBUG,msg);
}

// Used to read the Pre Defined Button States
uint8_t Cytron_PS2_Shield::readButton(uint8_t key)
{
	// Default Implemtation of the Function
	this->write(key);
	return (this->read()^1);
}

// #################### Getter Functions #######################

// --------------------- Raw Axis values -----------------------
int Cytron_PS2_Shield::GetX_Axis_Raw()
{
	// Read X_AXIS
	return this->Axis_raw_values[X_AXIS];
}	

int Cytron_PS2_Shield::GetY_Axis_Raw()
{
	// Read Y_AXIS
	return this->Axis_raw_values[Y_AXIS];
}

// ------------------- Scaled Axis Values ----------------------
int Cytron_PS2_Shield::GetX_Axis()
{
	// Read X_AXIS Scaled
	return this->Axis_scaled_values[X_AXIS];
}

int Cytron_PS2_Shield::GetY_Axis()
{
	// Read Y_AXIS Scaled
	return this->Axis_scaled_values[Y_AXIS];
}

// ------------------- Polar Values ---------------------------
float Cytron_PS2_Shield::GetPolarAngle()
{
	// Read Polar Angle
	return this->Polar_values[ANGLE];
}

float Cytron_PS2_Shield::GetPolarRadius()
{
	// Read Polar Radius
	return this->Polar_values[RADIUS];
}