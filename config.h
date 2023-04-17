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

#define ENCODER_INTA_VECT    INT0_vect
#define ENCODER_INTA_SETUP() { MCUCR |= _BV(ISC00); GICR |= _BV(INT0); }
#define ENCODER_INTB_VECT    INT1_vect
#define ENCODER_INTB_SETUP() { MCUCR |= _BV(ISC10); GICR |= _BV(INT1); }


#define ENABLE_SERIAL

#endif