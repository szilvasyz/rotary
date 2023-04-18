#if defined __AVR_ATmega16__\
 || defined __AVR_ATmega32__\
 || defined __AVR_ATmega324__\
 || defined __AVR_ATmega324P__\
 || defined __AVR_ATmega644__\
 || defined __AVR_ATmega644P__\
 || defined __AVR_ATmega1284__\
 || defined __AVR_ATmega1284P__
#define PIN_INT0 10
#define PIN_INT1 11
#elif defined __AVR_ATmega328__\
   || defined __AVR_ATmega328P__
#define PIN_INT0 2
#define PIN_INT1 3
#else
#error "Unknown chip!"
#endif


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
  {SL01, SL11, 0b11, 0},
  {SL11, SR10, 0b10, 1},
  {SL10, SX00, 0b00, 0},
  {SL01, SX00, 0b00, 0},
  {SL11, SX00, 0b00, 0},
  {SX00, SR10, 0b10, 0},
  {SR10, SR11, 0b11, 0},
  {SR11, SL01, 0b01, -1},
  {SR01, SX00, 0b00, 0},
  {SR10, SX00, 0b00, 0},
  {SR11, SX00, 0b00, 0}
};


t_state state = SX00;
volatile int c = 0;
volatile int encoder_position = 0;


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


void change_int() {
    c += 1;
    stateMachine((!digitalRead(PIN_INT0) << 1) | !digitalRead(PIN_INT1));
}

void setup() {
    pinMode(PIN_INT0, INPUT_PULLUP);
    pinMode(PIN_INT1, INPUT_PULLUP);

    attachInterrupt(0, change_int, CHANGE);
    attachInterrupt(1, change_int, CHANGE);

    Serial.begin(57600);
}

void loop() {
    Serial.print(c);
    Serial.print('\t');
    Serial.println(encoder_position);

    delay(200);
}