#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "rot.h"
#include "config.h"
#include "serial.h"

typedef enum {
  SX00,
  SL01,
  SL11,
  SL10,
  SR10,
  SR11,
  SR01
} t_state;

typedef struct t_stateChange {
  t_state srcState;
  t_state dstState;
  uint8_t input;
  int step;
} t_stateChange;

t_stateChange stateTab[] = {
  {SX00, SL01, 0b01, 0},
  {SL01, SL11, 0b11, 1},
  {SL11, SL10, 0b10, 0},
  {SL10, SX00, 0b00, 0},
  {SL01, SX00, 0b00, 0},
  {SL11, SX00, 0b00, 0},
  {SX00, SR10, 0b10, 0},
  {SR10, SR11, 0b11, -1},
  {SR11, SR01, 0b01, 0},
  {SR01, SX00, 0b00, 0},
  {SR10, SX00, 0b00, 0},
  {SR11, SX00, 0b00, 0}
};

t_state state = SX00;

volatile int c = 0;
volatile int encoder_position = 0;
char b[20];
volatile uint8_t laststate;


t_state stateMachine(uint8_t input) {
  uint8_t p;

  for (p = 0; p < sizeof(stateTab) / sizeof(stateTab[0]); p++) {
    if ((stateTab[p].srcState == state) && (stateTab[p].input == input)) {
      state = stateTab[p].dstState;
      encoder_position += stateTab[p].step;
      break;
    }
  }
}

void doStateChange() {
  stateMachine((!!(ROTA_PINS & _BV(ROTA_PIN)) << 1) | !!(ROTB_PINS & _BV(ROTB_PIN)));
}

ISR(ENCODER_INTA_VECT) {
  c += 1;
  doStateChange();
}

ISR(ENCODER_INTB_VECT) {
  c += 1;
  doStateChange();
}


void rot_init() {
  serial_init();

  ROTA_DDR  &= ~_BV(ROTA_PIN);
  ROTA_PORT |=  _BV(ROTA_PIN);
  ROTB_DDR  &= ~_BV(ROTB_PIN);
  ROTB_PORT |=  _BV(ROTB_PIN);

  serial_println("Hello");
  ENCODER_INTA_SETUP();
  ENCODER_INTB_SETUP();
  serial_println(itoa(sizeof(stateTab) / sizeof(stateTab[0]), b, 10));
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