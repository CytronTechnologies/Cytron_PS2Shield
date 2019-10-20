/*
  Cytron_PS2_Shield.h - Library to deal with Cytron PS2 Controller Module.
  Copyright (c) 2018 RoboManipal. All right reserved
  File created by : Shashank Goyal
*/

#ifndef Cytron_PS2_Shield_h
#define Cytron_PS2_Shield_h

#include "Arduino.h"
#include <SoftwareSerial.h>
#include "Stream.h"
#include "DebuggerSerial.h"

#define RIGHT_JOYSTICK 0
#define LEFT_JOYSTICK 1

#define X_AXIS 0
#define Y_AXIS 1

#define ANGLE 0
#define RADIUS 1

#define sgnm(x) x>=0?1:-1

// Define PS2 button to number
enum 
{
  // Digital button
  PS2_SELECT,
  PS2_JOYSTICK_LEFT,
  PS2_JOYSTICK_RIGHT,
  PS2_START,
  PS2_UP,
  PS2_RIGHT,
  PS2_DOWN,
  PS2_LEFT,
  PS2_LEFT_2,
  PS2_RIGHT_2,
  PS2_LEFT_1,
  PS2_RIGHT_1,
  PS2_TRIANGLE,
  PS2_CIRCLE,
  PS2_CROSS,
  PS2_SQUARE,
  // Analog button
  PS2_JOYSTICK_LEFT_X_AXIS,
  PS2_JOYSTICK_LEFT_Y_AXIS,
  PS2_JOYSTICK_RIGHT_X_AXIS,
  PS2_JOYSTICK_RIGHT_Y_AXIS,
  PS2_JOYSTICK_LEFT_UP,
  PS2_JOYSTICK_LEFT_DOWN,
  PS2_JOYSTICK_LEFT_LEFT,
  PS2_JOYSTICK_LEFT_RIGHT,
  PS2_JOYSTICK_RIGHT_UP,
  PS2_JOYSTICK_RIGHT_DOWN,
  PS2_JOYSTICK_RIGHT_LEFT,
  PS2_JOYSTICK_RIGHT_RIGHT,
};

class Cytron_PS2_Shield
{
    //####################### Data Members ##########################
    // Joystick Value to Choose Right or Left Joystick
    int Joystick;
    // Raw Values as recieved from the PS2
    int Axis_raw_values[2];
    // Values Adjusted using Cartesian Convention
    int Axis_scaled_values[2];
    // Values Calculated using Polar Convention
    float Polar_values[2];
    // Serial Line to which the PS2 is Connected
    Stream *PS2Serial;

    //###################### Private Member Functions ###############
    // Default write Function from the Library
    void write(uint8_t data);
    // Default read Function from the Library
    uint8_t read(void);

  public:

    // ################### Debugger Serial ##############
    DebuggerSerial debugger;

    // ################### Constructors #################
    
    Cytron_PS2_Shield();
    Cytron_PS2_Shield(Stream *AttchedSerial);   
    Cytron_PS2_Shield(int Joystick);
    Cytron_PS2_Shield(Stream *AttachedSerial,int Joystick);   
  
    // ############# Library Member Functions ##########
    
    // Attach PS2 to Serial
    void AttachPS2Serial(Stream *AttachedSerial);
    // Update Values recieved from the PS2
    void UpdateData();
    // Set Joystick Choice Left or Right
    void SetJoystick(int Joystick);
    // Read Button for Reading Status of any Button.
    uint8_t readButton(uint8_t key);
    // Get Raw X_Axis Values for the Selected Joystick
    int GetX_Axis_Raw();
    // Get Raw Y_Axis Values for the Selected Joystick
    int GetY_Axis_Raw();
    // Get Adjusted X_Axis Values for the Selected Joystick
    int GetX_Axis();
    // Get Adjusted Y_Axis Values for the Selected Joystick
    int GetY_Axis();
    // Get Adjusted PolarAngle Values for the Selected Joystick
    float GetPolarAngle();
    // Get Adjusted PolarRadius Values for the Selected Joystick
    float GetPolarRadius();
};

#endif
