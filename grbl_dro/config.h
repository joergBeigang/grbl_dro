//config.h




/*
   rotary encoder
   pin definition
*/
// rotary encoder - those pins should have interrupt abilities
#define encoderApin 2
#define encoderBpin 3

// pins for the rotary switch for axis selction
// switch = pin against GND (internal pull up is on)
#define encoderXpin 8
#define encoderYpin 9
#define encoderZpin 10

// resolution
// there are three diffrent resolution or speeds for the 
// rotary encoder
#define encoderResolution1 1000
#define encoderResolution2 100
#define encoderResolution3 50

// pins for the rotafy switch of the encoder resolution
#define encoderResolutionPin1 5
#define encoderResolutionPin2 6
#define encoderResolutionPin3 7

// timing for canceling jogging, when the rotary encoder stopped moving
// that's needed for fast jogs and slow machine acceleration
// not too low, otherwise GRBL is being hammered with cancel commands and hangs it self
#define encoderCancelIntervall 200

// max step size
// defining the maximal step size for the jog commands. In some rare cases read errors
// can happen. Those would result in large distance jog commands which would be very dangerous
// value is micrometer
#define encoderMaxSteps 1000

// send jog cmd intervall
// limiting the time between the jog commands
// rotary encoders with a very high resolution (like 600 pulses per rev) can
// produce errors when turned too fast
// milliseconds
#define encoderCmdIntervall 100





/* 
   potentiometer for feed and spindle overrides
   pin goes to the center pin of the potentiometer
   the other two pins are connected to GND and 5V
*/
#define feedPin A0
#define spindlePin A1
// smoothing the analog read
#define smoothSteps 10

/*
   7 segment 8 digit LED display
*/

// pins
#define LED_X_DataIn 53
#define LED_X_CLK 52
#define LED_X_LOAD 51

#define LED_Y_DataIn 50
#define LED_Y_CLK 49
#define LED_Y_LOAD 48

#define LED_Z_DataIn 47
#define LED_Z_CLK 46
#define LED_Z_LOAD 45

#define LED_I_DataIn 44
#define LED_I_CLK 43
#define LED_I_LOAD 42

// brightness of the LED display
#define intensity 2

/*
   interval for sending "?" to GRBL
*/
#define updateInterval 200

/*
   baud rate
   the baud rate is set to a pretty low value to give 
   the slow arduino mega enough time to to all it's calucations
   while making sure the communication is working. 
   It's not as bad as it sounds: 9600 baud = 1200 byte/sec
   that's roughly 42 lines of gcode per second. For a milling 
   machine more then enough to keep the buffer full.
   GRBL got to be set to the same baud rate (in the config.h file)
*/

#define baudRate 9600


