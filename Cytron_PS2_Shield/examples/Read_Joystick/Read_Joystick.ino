/*
  Read_Joystick - Sample Code for Cytron PS2 Controller Module.
  Refer to https://github.com/shashank3199/Cytron_PS2_Shield for More Info.
  Copyright (c) 2018 RoboManipal. All right reserved
  File created by : Shashank Goyal
*/

/*
	Read Joystick Functions  -

	GetX_Axis_Raw();
	GetY_Axis_Raw();

	GetX_Axis();
	GetY_Axis();

	GetPolarRadius();
	GetPolarAngle();
*/

#include <Cytron_PS2_Shield.h>

Cytron_PS2_Shield PS2;
int x,y;

void setup()
{
  Serial.begin(115200);
  Serial2.begin(115200);
  PS2.AttachPS2Serial(&Serial2);
  PS2.SetJoystick(RIGHT_JOYSTICK);
  PS2.debugger.Initialize("PS2", &Serial, DEBUG);
  PS2.debugger.disableDebugger();
}

void loop()
{
  PS2.UpdateData();
  String msg = "";
  msg.concat(millis());
  x = PS2.GetX_Axis();
  y = PS2.GetY_Axis();
  msg.concat("\t");
  msg.concat(x);
  msg.concat("\t");
  msg.concat(y);
  Serial.println(msg);
}
