
#include "LedControl.h"
#include <Encoder.h>
#include "config.h"

 

// 7 segment LED display
LedControl lcX=LedControl(LED_X_DataIn, LED_X_CLK ,LED_X_LOAD ,1);
LedControl lcY=LedControl(LED_Y_DataIn, LED_Y_CLK ,LED_Y_LOAD ,1);
LedControl lcZ=LedControl(LED_Z_DataIn, LED_Z_CLK ,LED_Z_LOAD ,1);
LedControl lcI=LedControl(LED_I_DataIn, LED_I_CLK ,LED_I_LOAD ,1);

// encoder
Encoder myEnc(encoderApin, encoderBpin);
long oldPosition  = -999;
String encoderAxis = "none";
int encoderResolution = 1000;
unsigned long encoderPreviousMicros = 0; // for the timer to cancel jogging when the encoder knop stopped moving
unsigned long encoderPreviousCmdMills = 0; // for the timer to cancel jogging when the encoder knop stopped moving
bool cancelSent = HIGH;


// feed and spindle overrides 
int feedOverride ;
int spindleOverride;
bool updateOverride = LOW;
int spindleDifference = 0;
int feedDifference = 0;
int feedInput;
int spindleInput;
int stepsCount=0;
int feedAry[smoothSteps];
int spindleAry[smoothSteps];


// status 0=Idle 1=run 2=alarm 3=error
int grblMode;

// timing for asking GRBL for an update 
unsigned long updatePreviousMillis = 0;    // will store last time a "?" was sent to grbl


/*
  Serial communication
*/
// reading Serial input
#define  SplittingArraySize 6
int SplittingArraySizeAdd = 9;
String   SplittingArray[SplittingArraySize];
boolean grblStringAvailable = false;                        // If a complete string received from GRBL
String  grblStringRx = "";   

// Arrays that store the informations displayed on the LED display
String outputGRBL[15]; // all values are in here
float disp[15]; // all values in float format are in here

/*
   Setup
*/

void setup() 
{
  Serial.begin(baudRate);
  Serial1.begin(baudRate);
  lcX.shutdown(0,false);
  lcY.shutdown(0,false);
  lcZ.shutdown(0,false);
  lcI.shutdown(0,false);
  lcX.setIntensity(0,intensity);
  lcY.setIntensity(0,intensity);
  lcZ.setIntensity(0,intensity);
  lcI.setIntensity(0,intensity);
  lcX.clearDisplay(0);
  lcY.clearDisplay(0);
  lcZ.clearDisplay(0);
  lcI.clearDisplay(0);
  pinMode(encoderXpin, INPUT_PULLUP);
  pinMode(encoderYpin, INPUT_PULLUP);
  pinMode(encoderZpin, INPUT_PULLUP);
  
  pinMode(encoderResolutionPin1, INPUT_PULLUP);
  pinMode(encoderResolutionPin2, INPUT_PULLUP);
  pinMode(encoderResolutionPin3, INPUT_PULLUP);
}


void loop()
{
  readEncocder();
  // pipe through the serial communication in one direction
  if (Serial.available()) 
  {     // If anything comes in Serial1 (pins 0 & 1)
    // make sure no feed or spindle override commands are being send
    char tmp = Serial.read();
	Serial1.write(tmp);   // read it and send it out Serial (USB)
  }
 
  // digital read out and communication in the other direction
  dro();
  
  // send the update request to GRBL
  unsigned long currentMillis = millis();
  if (currentMillis - updatePreviousMillis >= updateInterval && grblMode != 1) 
  {
    updatePreviousMillis = currentMillis;
    Serial1.write("?");
  }

} // end loop
