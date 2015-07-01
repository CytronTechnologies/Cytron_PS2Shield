# getval() #

## Description ##
This function get button or joystick status/value from Cytron PS2 Shield.


## Include ##
Shield\_PS2.h


## Prototype ##
byte getval(byte key);


## Parameters ##
**key**: Please refer to the Key Constants Page


## Returns ##
value or status of button or joystick,

**buttons**

0 if the button is pressed

1 if button is not pressed

**Joy Stick**

Shield-PS2 will return the particular value of corresponding joystick in the selected axis

**p\_con\_status**

Shield-PS2 will read PS2 controller status

1 is return if controller is detected or connected to the PS2 connector on Shield-PS2


## Example ##
PS2 ps2=PS2();
byte val;

value = ps2.getval(p\_select);



## See Also ##

KeyConstant