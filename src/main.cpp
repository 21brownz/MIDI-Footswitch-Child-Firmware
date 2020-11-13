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
int address = 0x0;
uint32_t rgb = 0x0;
bool isTapTempo = 0;
float tempo = 120;
char state = '0'; 

//define library objects
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

void doOnRecieve(int numBytes){
  byte buffer[] = {0x0,0x0,0x0,0x0,0x0};
  switch (buffer[0]){
  case 'c':
    state = 'c';
    isTapTempo = buffer[1];
    rgb = buffer[2];
    break;
  
  case 'r':
    state = 'r';
    rgb = (buffer[1] << 24) | (buffer[2] << 16) | (buffer[3] << 8) | (buffer[4]);
    break;

  case 't':
    state = 't';
    break;
  
  case 'g':
    state = 'g';
    break;

  case 'b':
    state = 'b';
    break;

  default:
    break;
  }
}

void doOnRequest(){
  switch (state){
  case 't':
    Wire.write((uint16_t)tempo);
    break;
  
  case 'g':
    Wire.write(rgb);
    break;

  case 'b':
    Wire.write(digitalRead(fswpin));
    break;

  default:
    break;
  }
}

void setup() {
  setAddr();
  configurePinStates();
  FastLED.addLeds<NEOPIXEL, ledpin>(led, 1);
  Wire.begin(address);
  Wire.onReceive(doOnRecieve);
  Wire.onRequest(doOnRequest);
}

void loop() {

}