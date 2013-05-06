#include "Arduino.h"
#include "SSI.h"

//                        segment: A,B,C,D,E,F,G
const uint8_t SSI_digits[][7] = { { 1,1,1,1,1,1,0 },  // = 0
                                  { 0,1,1,0,0,0,0 },  // = 1
                                  { 1,1,0,1,1,0,1 },  // = 2
                                  { 1,1,1,1,0,0,1 },  // = 3
                                  { 0,1,1,0,0,1,1 },  // = 4
                                  { 1,0,1,1,0,1,1 },  // = 5
                                  { 1,0,1,1,1,1,1 },  // = 6
                                  { 1,1,1,0,0,0,0 },  // = 7
                                  { 1,1,1,1,1,1,1 },  // = 8
                                  { 1,1,1,1,0,1,1 }   // = 9
#ifdef SSI_hex
                                  { 1,1,1,0,1,1,1 },  // = A
                                  { 0,0,1,1,1,1,1 },  // = b
                                  { 1,0,0,1,1,1,0 },  // = C
                                  { 0,1,1,1,1,0,1 },  // = d
                                  { 1,0,0,1,1,1,1 },  // = E
                                  { 1,0,0,0,1,1,1 },  // = F
#endif
                                                    };
#ifdef SSI_hex
#define SSI_max 15
#else
#define SSI_max 9
#endif

SSI::SSI(uint8_t pin_a, uint8_t pin_b, uint8_t pin_c, uint8_t pin_d, uint8_t pin_e, uint8_t pin_f, uint8_t pin_g)
{
  f_pins[0] = pin_a;
  f_pins[1] = pin_b;
  f_pins[2] = pin_c;
  f_pins[3] = pin_d;
  f_pins[4] = pin_e;
  f_pins[5] = pin_f;
  f_pins[6] = pin_g;
  
  for(uint8_t i=0; i<7; ++i)
  {
    pinMode(f_pins[i], OUTPUT);
    digitalWrite(f_pins[i], LOW);
  }
}

void SSI::setDigit(uint8_t value)
{
  if (value <= SSI_max)
    for(uint8_t i=0; i<7; ++i)
      digitalWrite(f_pins[i], SSI_digits[value][i]);
  else
    off();
}

void SSI::setMask(uint8_t value)
{
  for(uint8_t i=0, mask=B01000000; i<7; mask>>=1,++i)
    digitalWrite(f_pins[i], value&mask);
}

void SSI::off(void)
{
  for(uint8_t i=0; i<7; ++i)
    digitalWrite(f_pins[i], LOW);
}