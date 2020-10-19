#include <Arduino.h>
#include <Wire.h>
#include <FastLED.h>
#include <ArduinoTapTempo.h>

//define pins
#define b0pin PD5
#define b1pin PD7
#define b2pin PD2
#define b3pin PD3
#define b4pin PB0
#define b5pin PB1
#define b6pin PB2
#define fswpin PD4
#define ledpin PD6

//defines all the parameters for the footswitch
bool isTapTempo = false;
byte address = 0x00;
//led colors
int rgb[] = {0,0,0};

//define lib objects
CRGB led[1];
ArduinoTapTempo tap;

//initializes all of the pins
void configurePinStates(){
  pinMode(b0pin, INPUT_PULLUP);
  pinMode(b1pin, INPUT_PULLUP);
  pinMode(b2pin, INPUT_PULLUP);
  pinMode(b3pin, INPUT_PULLUP);
  pinMode(b4pin, INPUT_PULLUP);
  pinMode(b5pin, INPUT_PULLUP);
  pinMode(b6pin, INPUT_PULLUP);
  pinMode(fswpin, INPUT);
}

void setAddr(){
  address = digitalRead(b0pin) | (digitalRead(b1pin)<<1) | (digitalRead(b2pin)<<2) | (digitalRead(b3pin)<<3) | (digitalRead(b4pin)<<4) | (digitalRead(b5pin)<<5) | (digitalRead(b6pin)<<6);
}

void getConfig(){
  
}

void setup() {
  configurePinStates();
  FastLED.addLeds<NEOPIXEL, ledpin>(led, 1);
  Wire.begin(address);
}

void loop() {

}