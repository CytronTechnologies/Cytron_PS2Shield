# reset() #

## Description ##
This function reset Cytron PS2 Shield.


## Include ##
Shield\_PS2.h


## Prototype ##
void reset(byte rst);


## Parameters ##
**rst** : 1 (pull down reset signal), 0 (release the reset signal)


## Returns ##
void



## Example ##
PS2 ps2=PS2();

ps2.reset(1);
delay(10);
ps2.reset(0);


## See Also ##

KeyConstant