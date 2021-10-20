#define BUTTON_PRESSED(n) (SW##n == 0)
#define TURN_ON_LED(n) LED##n = 1
#define TURN_OFF_LED(n) LED##n = 0
#define FLASH_LED(n, duration) \
    TURN_ON_LED(n);            \
    __delay_ms(duration);      \
    TURN_OFF_LED(n)
#define FLASH_2_LEDS(first, second, duration) \
    TURN_ON_LED(first);                       \
    TURN_ON_LED(second);                      \
    __delay_ms(duration);                     \
    TURN_OFF_LED(first);                      \
    TURN_OFF_LED(second)

unsigned int PERIOD_SCALE = 80;

enum MusicalNote
{
    A,
    B,
    C,
    C2,
    D,
    E,
    F,
    G,
    REST,
};
#define MUSICAL_NOTE_BITS 5 // number of bits reserved for mustical note
#define MUSICAL_NOTE_MASK 0b00011111
unsigned int QUARTER_NOTE_DURATION_CYCLES = 700;

enum MusicalNoteLength
{
    //QuarterNote = 0 << MUSICAL_NOTE_BITS, // This the default
    OneThirdNote = 1 << MUSICAL_NOTE_BITS,
    HalfNote = 2 << MUSICAL_NOTE_BITS,
    TwoThirdNote = 3 << MUSICAL_NOTE_BITS,
    ThreeQuarterNote = 4 << MUSICAL_NOTE_BITS,
    FullNote = 5 << MUSICAL_NOTE_BITS
};

/**
 * Play a musical note
 * 
 * @param notePlus a combined value that represent the MusicalNote and MusicalNoteLength
 */
void playNote(unsigned int notePlus);

/**
 * Make a noise on the buzzer with the given params a number of times (nTimes)
 **/
void makeSound(unsigned int cycles, unsigned long period, unsigned int nTimes);
