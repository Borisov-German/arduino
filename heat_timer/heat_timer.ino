#include <SSI.h>

// Блок описания пинов
#define dot_pin    0 // точка для индикации секунд
#define enc_2_pin  1 // энкодер 2
#define enc_1_pin  2 // энкодер 1 (int0)
#define button_pin 3 // кнопка (int1)
#define led_1_a    4 // инд.1 A
#define led_1_b    5 // инд.1 B
#define led_1_c    6 // инд.1 C
#define led_1_d    7 // инд.1 D
#define led_1_e    8 // инд.1 E
#define led_1_f    9 // инд.1 F
#define led_1_g   10 // инд.1 G
#define led_2_a   11 // инд.2 A
#define led_2_b   12 // инд.2 B
#define relay_pin 13 // реле LED
//#define therm_pin A0 // терморезистор
#define led_2_c   A1 // инд.2 C
#define led_2_d   A2 // инд.2 D
#define led_2_e   A3 // инд.2 E
#define led_2_f   A4 // инд.2 F
#define led_2_g   A5 // инд.2 G

#define max_min 90

SSI D1(led_1_a, led_1_b, led_1_c, led_1_d, led_1_e, led_1_f, led_1_g);
SSI D2(led_2_a, led_2_b, led_2_c, led_2_d, led_2_e, led_2_f, led_2_g);

volatile uint8_t count_min;
volatile uint8_t count_sec;
volatile unsigned long curr_millis;
volatile unsigned long last_millis;

void setup() {
  pinMode(dot_pin, OUTPUT);
  pinMode(relay_pin, INPUT);
  pinMode(enc_1_pin, INPUT);
  pinMode(enc_2_pin, INPUT);
  pinMode(button_pin, INPUT);
  //pinMode(therm_pin, INPUT);
  digitalWrite(dot_pin, LOW);
  count_min = 0;
  count_sec = 0;
  last_millis = 0;
  attachInterrupt(0, enc_int, RISING); //enc_1_pin
  attachInterrupt(1, button_int, RISING); //button_pin
}

void displayNumber(byte number) {
  if (number < 10)
    D1.off();
  else
    D1.setDigit(number / 10);
  D2.setDigit(number % 10);
}

void displayEr(void) {
  D1.setMask(B01001111);
  D2.setMask(B00000101);
}

void displayC(void) {
  D1.setMask(B01100011);
  D2.setMask(B01001110);
}

void displayT(void) {
  D1.off();
  D2.setMask(B00001111);
}

void displayOff(void) {
  D1.off();
  D2.off();
}

void loop() {
  if(last_millis && count_min) {
    curr_millis = millis();
    if(curr_millis - last_millis > 1000) {
      --count_sec;
      if (!count_sec) {
        --count_min;
        count_sec = 60;
      }
      if (count_min)
        last_millis += 1000;
      else
        last_millis = 0;  
    }
    digitalWrite(dot_pin, count_sec & 1);
  }  
  displayNumber(count_min);
  digitalWrite(relay_pin, (count_min == 0 ? LOW : HIGH));
}

void enc_int() {
  if (digitalRead(enc_2_pin) == HIGH) {
    if(count_min < max_min)
      ++count_min;
    count_sec = 60;
  } 
  else {
    if(count_min > 0) {
      --count_min;
      count_sec = 60;
    } 
    else
      count_sec = 0;
  }
  last_millis = millis();
}

void button_int() {
  count_min = 0;
  count_sec = 0;
  last_millis = 0;
}

