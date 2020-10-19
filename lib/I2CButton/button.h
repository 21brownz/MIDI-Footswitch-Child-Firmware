#ifndef MY_I2CBUTTON
#define MY_I2CBUTTON
#include <Arduino.h>
#include <Wire.h>

class Button {
    private:
        int address;
        uint32_t rgb;
        bool isTapTempo;
        uint16_t tempo;
    public:
        Button(int address, bool isTapTempo, uint32_t rgb);
        void setColor(uint32_t rgb);
        uint16_t getTempo();
        uint32_t getColor();
        bool getSwitchState();
};
#endif