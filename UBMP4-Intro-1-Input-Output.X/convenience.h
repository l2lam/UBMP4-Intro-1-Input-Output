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

//#define NOTE_DURATION_CYCLES = 300
unsigned int NOTE_DURATION_CYCLES = 700;
unsigned int PERIOD_SCALE = 80;

enum Note
{
    A,
    B,
    C,
    C2,
    D,
    E,
    F,
    G
};
void playNote(enum Note note, unsigned int length);

/**
 * Make a noise on the buzzer with the given params a number of times (nTimes)
 **/
void makeSound(unsigned int cycles, unsigned long period, unsigned int nTimes);
