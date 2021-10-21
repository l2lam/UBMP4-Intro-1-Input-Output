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
