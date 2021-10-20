// This magic number is used to scale the calculated period of a note down
// in order to make the sound audible.
unsigned int PERIOD_SCALE = 80;

// We use lower 5 bits of an integer to encode the note
#define MUSICAL_NOTE_BITS 5

// This bit mask is used to decode the note
#define MUSICAL_NOTE_MASK 0b00011111

// Here are the enumerated values for the notes for convenience
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

// Here are the enumerated values for the standard lengths of a notes.
// Note that a quarter note is the default length so does not need to expressed explicitly.
enum MusicalNoteLength
{
    //QuarterNote = 0 << MUSICAL_NOTE_BITS, // This the default
    OneThirdNote = 1 << MUSICAL_NOTE_BITS,
    HalfNote = 2 << MUSICAL_NOTE_BITS,
    TwoThirdNote = 3 << MUSICAL_NOTE_BITS,
    ThreeQuarterNote = 4 << MUSICAL_NOTE_BITS,
    FullNote = 5 << MUSICAL_NOTE_BITS
};
// This is the duration of a quarter note expressed in program-execution cycles.
// The actual duration of the note played will depend on the processor speed/frequency.
unsigned int QUARTER_NOTE_DURATION_CYCLES = 700;

/**
 * Play a musical note
 * 
 * @param notePlus a combined value that represent the MusicalNote and MusicalNoteLength.  
 * For example, a half note G can be encoded as notePlus = G | HalfNote
 */
void playNote(unsigned int notePlus);

/**
 * Make a noise on the buzzer with the given params a number of times (nTimes)
 **/
void makeSound(unsigned int cycles, unsigned long period, unsigned int nTimes);
