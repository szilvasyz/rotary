#ifndef CONFIG_H
#define CONFIG_H

#define ROTA_DDR  DDRD
#define ROTA_PORT PORTD
#define ROTA_PINS PIND
#define ROTA_PIN  2

#define ROTB_DDR  DDRD
#define ROTB_PORT PORTD
#define ROTB_PINS PIND
#define ROTB_PIN  3

#define ENCODER_INT_VECT    INT0_vect
#define ENCODER_INT_SETUP() { MCUCR |= _BV(ISC00); GICR |= _BV(INT0); }


#define ENABLE_SERIAL

#endif