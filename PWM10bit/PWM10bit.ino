#if !defined(__AVR_ATmega1280__)
  #error RTFM!!!
#endif

#include "wiring_private.h"

void setup() {
  uint8_t oldSREG = SREG;
  cli();
  DDRB = B00110000;
  SREG = oldSREG;

  //TIMER2A 8bit, 10pin
  // Модуляция Fast PWM (256 шагов)
  // Предделитель 8 (16МГц/256/8 ~ 7,8КГц)
  TCCR2A = B10000011;
  TCCR2B = B00000010;

  //TIMER1A 16bit, 11pin
  // Модуляция Fast PWM 10 бит (1024 шага)
  // Предделитель 8 (16МГц/1024/8 ~ 1,9КГц)
  TCCR1A = B10000011;
  TCCR1B = B00001010;


  //Стандартные настройки
  // PC PWM (256 шагов)
  // Предделитель 64 (16МГц/256/64/2 ~ 0,49КГц)
  analogWrite(8, 128);
  analogWrite(10, 128);
  analogWrite(11, 512);
  //OCR1A = 512;
}

void loop() {

}
