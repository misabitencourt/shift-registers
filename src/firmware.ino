// 74HC165 Connections
// PL pin 1
int load = 7;
// CE pin 15
int clockEnablePin = 5;
// Q7 pin 7
int dataIn = 4;
// CP pin 2
int clockIn = 6;


// 74HC595 Connections
// ST_CP pin 12
const int latchPin = 10;
// SH_CP pin 11
const int clockPin = 11;
// DS pin 14
const int dataPin = 12;


// Local vars
int outputState = 0;


void setup()
{
  
  // 74HC165 connections
  pinMode(load, OUTPUT);
  pinMode(clockEnablePin, OUTPUT);
  pinMode(clockIn, OUTPUT);
  pinMode(dataIn, INPUT);

  // 74HC595 connections
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  // Setup Serial Monitor
  Serial.begin(9600);
  Serial.println("started!");
}


void loop()
{

  // Input Shift registers here:
  // Write pulse to load pin
  digitalWrite(load, LOW);
  delayMicroseconds(5);
  digitalWrite(load, HIGH);
  delayMicroseconds(5);
  // Get data from 74HC165
  digitalWrite(clockIn, HIGH);
  digitalWrite(clockEnablePin, LOW);
  byte incoming = shiftIn(dataIn, clockIn, LSBFIRST);
  digitalWrite(clockEnablePin, HIGH);
  // Print to serial monitor
  Serial.print("Pin States:\r\n");
  Serial.println(incoming, BIN);



  // Output Shift registers here:
  outputState += 1;
  outputState = outputState == 256 ? 0 : outputState;
  digitalWrite(latchPin, LOW);  
  shiftOut(dataPin,clockPin,MSBFIRST, outputState);  
  digitalWrite(latchPin, HIGH);


  // Watchable delay
  delay(1000);
}

