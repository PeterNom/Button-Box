//#include <Joystick.h>

#include "Button_Box.h"

BYTES_VAL_T read_shift_regs()
{
  long bitVal;
  BYTES_VAL_T bytesVal = 0;

  /* Trigger a parallel Load to latch the state of the data lines,
  */
  digitalWrite(clockEnablePin, HIGH);
  digitalWrite(load, LOW);
  delayMicroseconds(PULSE_WIDTH_USEC);
  digitalWrite(load, HIGH);
  digitalWrite(clockEnablePin, LOW);

  for(int i = 0; i < DATA_WIDTH; i++)
  {
    bitVal = digitalRead(dataIn);

    /* 
     *  Set the corresponding bit in bytesVal.
    */
    bytesVal |= (bitVal << ((DATA_WIDTH-1) - i));

    /* 
     *  Pulse the Clock (rising edge shifts the next bit).
    */
    digitalWrite(clockIn, HIGH);
    delayMicroseconds(PULSE_WIDTH_USEC);
    digitalWrite(clockIn, LOW);
  }

  return(bytesVal);
}

void display_pin_values()
{
    Serial.print("Pin States:\r\n");

    for(int i = 0; i < DATA_WIDTH; i++)
    {
        Serial.print("  Pin-");
        Serial.print(i);
        Serial.print(": ");

        if((pinValues >> i) & 1)
            Serial.print("HIGH");
        else
            Serial.print("LOW");

        Serial.print("\r\n");
    }

    Serial.print("\r\n");
}

void setup() {

  Serial.begin(9600);
  
  //74HC595
  //pinMode(latchPin, OUTPUT);
  //pinMode(clockPin, OUTPUT);
  //pinMode(dataPin,  OUTPUT);

  //74HC165
  pinMode(load, OUTPUT);
  pinMode(clockEnablePin, OUTPUT);
  pinMode(clockIn, OUTPUT);
  pinMode(dataIn, INPUT);

  digitalWrite(clockIn, LOW);
  digitalWrite(load, HIGH);

  /* 
   *  Read in and display the pin states at startup.
  */
  pinValues = read_shift_regs();
  display_pin_values();
  oldPinValues = pinValues;
}

void loop() {
  /* Read the state of all zones.
  */
  pinValues = read_shift_regs();

  /* If there was a chage in state, display which ones changed.
  */
  if(pinValues != oldPinValues)
  {
    Serial.print("*Pin value change detected*\r\n");
    display_pin_values();
    oldPinValues = pinValues;
  }
  for(int i = 0; i<DATA_WIDTH; i++)
  {
    if(pinValues & (1 << i))
    {
      
    }
  }
  delay(POLL_DELAY_MSEC);
}
