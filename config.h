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

#if defined __AVR_ATmega16__\
 || defined __AVR_ATmega32__
#define ENCODER_INTA_VECT    INT0_vect
#define ENCODER_INTA_SETUP() { MCUCR |= _BV(ISC00); GICR |= _BV(INT0); }
#define ENCODER_INTB_VECT    INT1_vect
#define ENCODER_INTB_SETUP() { MCUCR |= _BV(ISC10); GICR |= _BV(INT1); }
#else
#define ENCODER_INTA_VECT    INT0_vect
#define ENCODER_INTA_SETUP() { EICRA |= _BV(ISC00); EIMSK |= _BV(INT0); }
#define ENCODER_INTB_VECT    INT1_vect
#define ENCODER_INTB_SETUP() { EICRA |= _BV(ISC10); EIMSK |= _BV(INT1); }
#endif

#if defined __AVR_ATmega164P__\
 || defined __AVR_ATmega324P__\
 || defined __AVR_ATmega644__\
 || defined __AVR_ATmega644P__\
 || defined __AVR_ATmega1284__\
 || defined __AVR_ATmega1284P__
#define USART_RX_vect USART0_RX_vect
#define USART_UDRE_vect USART0_UDRE_vect
#endif

#define ENABLE_SERIAL

#endif