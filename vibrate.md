# vibrate() #

## Description ##
This function set the motor 1 or 2 on PS2 controller (if exist) to vibrate.


## Include ##
Shield\_PS2.h


## Prototype ##
void vibrate(byte motor, byte val);


## Parameters ##
**motor**: 1, 2

**val**:
| motor1| 1 (vibrator motor on), 0 (vibrator motor off)|
|:------|:---------------------------------------------|
| motor2|  0 to 255 (adjustable speed)                 |


## Returns ##
void


## Example ##
PS2 ps2=PS2();


ps2.vibrate(2, 255);



## See Also ##

KeyConstant