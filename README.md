# grbl_dro
a man in the middle approach for a DRO including a rotary jog control for GRBL

It runs on an Arduino Mega 2560. Should run on any Arduino board with at least two hardware serials.
As a display four 7 segment 8 digit LED displays driven by a max72XX are used. They are nice and bright
and very cheap.
It's all done by wiring cheap standard components together. No custom circuit board is needed.


Basically it’s sitting between the computer and grbl. In a defined interval it’s sending an ‘?’ character to grbl in order to receive and status update. This status update is being parsed and printed out on the LED display. 
Beside this core functions there is also a rotary encoder which can together with two rotary switches for direction and resolution jog the machine. 
And two potentiometers are controlling the feed and spindle override. 

All the configuration is happening in the config.h file. A schematic is not really needed, as it’s quite well documented in config.h.

One big issue here is the performance of the Arduino Mega board. The Library for the LED display takes it’s time for computing. So I had to lower the communication speed to 9600 Baud to get a stable communication. Maybe this works better on a faster board, like the teensy. It compiles without any changes on a teensy 3.6. I just couldn’t test it, because I don’t own a teensy. 
But on the other hand 9600 is not such a big drama. That’s still fast enough to keep the buffer on my mill filled up. 
 
