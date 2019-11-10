// rotary encoder

void setEncoderResolution()
{
  if (digitalRead(encoderResolutionPin1)==LOW)
  {
	encoderResolution=encoderResolution1;
  }
  if (digitalRead(encoderResolutionPin2)==LOW)
  {
	encoderResolution=encoderResolution2;
  }
  if (digitalRead(encoderResolutionPin3)==LOW)
  {
	encoderResolution=encoderResolution3;
  }
}


void setEncoderAxis()
{
  int i=0;

  if (digitalRead(encoderXpin)==LOW)
  {
	encoderAxis="X";
  } else
  {
	i++;
  }

  if (digitalRead(encoderYpin)==LOW)
  {
	encoderAxis="Y";
  } else
  {
	i++;
  }
  
  if (digitalRead(encoderZpin)==LOW)
  {
	encoderAxis="Z";
  }else
  {
	i++;
  }

  if (i==3)
  {
	encoderAxis="none";
  }
}

void readEncocder()
{

  setEncoderAxis();
  setEncoderResolution();
  // cancel jogging if the encoder stopped moving
  if ((millis()- encoderPreviousMicros) > encoderCancelIntervall && cancelSent == LOW && encoderResolution<1000)
  {
	Serial1.write(0x85);
	cancelSent=HIGH;
  }
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) 
  {
    if (grblMode!=1 && encoderAxis != "none")
    {
	  if ((millis() - encoderPreviousMicros) > encoderCmdIntervall)
	  {
		encoderPreviousMicros=millis();
		float dif = oldPosition - newPosition;
		if ((dif/encoderResolution)<encoderMaxSteps)
		{
		  // Serial.println(dif);
		  Serial1.println("$J=G91 "+ encoderAxis + String(dif/encoderResolution)+" F3000");
		  oldPosition = newPosition;
		  cancelSent=LOW;
		}
	  }
	}
  }



}

