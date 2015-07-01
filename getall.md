# getall() #

## Description ##
This function get all the buttons status and joysticks value from Cytron PS2 Shield.


## Include ##
Shield\_PS2.h


## Prototype ##
boolean getall();


## Parameters ##
void


## Returns ##
**status**: true or false as indication of complete valid packet received or vice versa.
**Result**: is store in array **ps\_data[6](6.md)**

**6 bytes of data**
| **1st byte**| digital button group 1|
|:------------|:----------------------|
| **2nd byte**| digital button group 2|
| **3rd byte**| Right Joystick X axis |
| **4th byte**| Right Joystick Y axis |
| **5th byte**|Left Joystick X axis   |
| **6th byte**|Left Joystick Y axis   |

**Digital group 1:**
|bit 7 (MSB)| Left button|
|:----------|:-----------|
|bit 6      | Down button|
|bit 5      |Right button|
|bit 4      |Up button   |
|bit 3      |Start button|
|bit 2      |Right Joystick Center button|
|bit 1      |Left Joystick Center button|
|bit 0 (LSB)|Select button|

**Digital group 2:**
|bit 7 (MSB)|Square button|
|:----------|:------------|
|bit 6      |Cross button |
|bit 5      |Circle button|
|bit 4      |Triangle button|
|bit 3      |[R1](https://code.google.com/p/cytron-ps2-shield/source/detail?r=1) button|
|bit 2      |L1 button    |
|bit 1      |[R2](https://code.google.com/p/cytron-ps2-shield/source/detail?r=2)  button|
|bit 0      |L2 button    |

0 if the button is pressed
1 if button is not pressed




## Example ##
PS2 ps2=PS2();
boolean status
byte left\_joy\_y\_val;

status= ps2.getall();
left\_joy\_y\_val=ps2.ps\_data[5](5.md);






## See Also ##

KeyConstant