#include <avr/io.h>
#include<avr/interrupt.h>
#include <util/delay.h>
#include "rot.h"
#include "config.h"
#include "serial.h"

volatile int c = 0;
volatile int encoder_position = 0;
char b[20];

volatile uint8_t laststate;

ISR(ENCODER_INT_VECT) {
  c += 1;

  uint8_t curstate;

  curstate = (!!(ROTA_PINS & _BV(ROTA_PIN)) << 1) | !!(ROTB_PINS & _BV(ROTB_PIN));

  // Encoder
  if ((laststate & 0b10) ^ (curstate & 0b10)) {
    if (!!(curstate & 0b10) == !!(curstate & 0b01)) {
      encoder_position--;
    } else {
      encoder_position++;
    }
    laststate = curstate;
  }

}


void rot_init() {
  serial_init();

  ROTA_DDR  &= ~_BV(ROTA_PIN);
  ROTA_PORT |=  _BV(ROTA_PIN);
  ROTB_DDR  &= ~_BV(ROTB_PIN);
  ROTB_PORT |=  _BV(ROTB_PIN);

  serial_println("Hello");
  ENCODER_INT_SETUP();
}

void rot_run() {

  
  serial_print(itoa(!(ROTA_PINS & _BV(ROTA_PIN)), b, 10));
  serial_print(itoa(!(ROTB_PINS & _BV(ROTB_PIN)), b, 10));
  serial_print(" ");  
  serial_print(itoa(c, b, 10));
  serial_print(" ");  
  serial_print(itoa(encoder_position, b, 10));
  serial_println(" ");  

  _delay_ms(200);
}