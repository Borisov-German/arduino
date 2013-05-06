/*
  SSI.h - Seven Segment LED Indicator with CC library for Wiring/Arduino - Version 0.1
  
  Original library (0.1) by German Borisov.

*/
#include "Arduino.h"
#ifndef SSI_h
#define SSI_h

// library interface description
class SSI {
  public:
    SSI(uint8_t pin_a, uint8_t pin_b, uint8_t pin_c, uint8_t pin_d, uint8_t pin_e, uint8_t pin_f, uint8_t pin_g);
    void setDigit(uint8_t value);
    void setMask(uint8_t value);
    void off(void);
  private:
    uint8_t f_pins[7];
};

#endif

