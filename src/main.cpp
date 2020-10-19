#include <Arduino.h>
#include <Wire.h>
#include <FastLED.h>

const int b0pin = PD5;
const int b1pin = PD7;
const int b2pin = PD2;
const int b3pin = PD3;
const int fswpin = PD4;
const int ledpin = PD6;
CRGB led[1];

void configurePinStates(){
  pinMode(b0pin, INPUT_PULLUP);
  pinMode(b1pin, INPUT_PULLUP);
  pinMode(b2pin, INPUT_PULLUP);
  pinMode(b3pin, INPUT_PULLUP);
  pinMode(fswpin, INPUT);
}

byte getAddr(){
  return digitalRead(b0pin) | (digitalRead(b1pin)<<1) | (digitalRead(b2pin)<<2) | (digitalRead(b3pin)<<3);
}

void sendSwitchData(){
  Wire.write(digitalRead(fswpin));
}

void updateLED(int bytesRead){
  byte bufferarray[bytesRead];
  int i = 0;
  while(Wire.available()){
    bufferarray[i] = Wire.read();
    i++;
  }
  led[0] = CRGB(bufferarray[0],bufferarray[1],bufferarray[2]);
  FastLED.show();
}

void setup() {
  configurePinStates();
  FastLED.addLeds<NEOPIXEL, ledpin>(led, 1);
  Wire.begin(getAddr());
  Wire.onRequest(sendSwitchData);
  Wire.onReceive(updateLED);
}

void loop() {
  //interrupt driven programming YEET
}