# init() #

## Description ##
This function initialize the hardware needed by Cytron PS2 Shield


## Include ##
Shield\_PS2.h


## Prototype ##
void init(long baudrate, byte rx, byte tx);


## Parameters ##
**baudrate**: 9600,57600,115200 (match to the hardware mini jumper selection)

**rx**: 0, 2, 8, 10

**tx**: 1, 3, 9, 11


## Returns ##
void


## Example ##
PS2 ps2=PS2();

ps2.init(9600, 0, 1);


## See Also ##
[G15 constructor](http://code.google.com/p/cytron-g15-shield/wiki/G15)


ReturnStatus