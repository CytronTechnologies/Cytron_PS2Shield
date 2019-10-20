/*
  Read_Button - Sample Code for Cytron PS2 Controller Module.
  Refer to https://github.com/shashank3199/Cytron_PS2_Shield for More Info.
  Copyright (c) 2018 RoboManipal. All right reserved
  File created by : Shashank Goyal
*/

/*
	Read Button Function  -

  readButtonStatus(<PARAMETER>);

  PARAMETERS -

  PS2_SELECT,  PS2_JOYSTICK_LEFT,  PS2_JOYSTICK_RIGHT,  PS2_START,
  PS2_UP,  PS2_RIGHT,  PS2_DOWN,  PS2_LEFT,
  PS2_LEFT_2,  PS2_RIGHT_2,  PS2_LEFT_1,  PS2_RIGHT_1,
  PS2_TRIANGLE,  PS2_CIRCLE,  PS2_CROSS,  PS2_SQUARE 
*/

#include <Cytron_PS2_Shield.h>

Cytron_PS2_Shield PS2;

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
  String msg = "";
  msg.concat(millis());
  msg.concat("\t");
  msg.concat(PS2.readButton(PS2_CROSS));
  Serial.println(msg);
}
