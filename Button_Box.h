#define NUMBER_OF_SHIFT_CHIPS 3

#define DATA_WIDTH NUMBER_OF_SHIFT_CHIPS*8

#define PULSE_WIDTH_USEC 5

#define POLL_DELAY_MSEC  1

#define BYTES_VAL_T unsigned long

//74HC595 (LED Shift Register) Setup
const int dataPin  = 1;
const int latchPin = 2;
const int clockPin = 3;

//74HC165 (Button & Switch Shift Register) Setup
const int clockEnablePin = 4;
const int dataIn = 5;
const int clockIn = 6;
const int load = 7;

//Read Inputs
byte incoming = 0;

BYTES_VAL_T pinValues;
BYTES_VAL_T oldPinValues;
