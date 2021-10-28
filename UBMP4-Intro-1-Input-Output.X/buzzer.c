#include "xc.h"    // Microchip XC8 compiler include file
#include "UBMP4.h" // Include UBMP4 constants and functions
#include "convenience.h"
#include "buzzer.h"

#define MIN(x, y) x < y ? x : y
#define MAX(x, y) x < y ? y : x

// This is the definition of a function pointer type; so that we can pass in different functions to calculate
// the period given the current position in the cycle, the total # of cycles and the max period.
typedef unsigned int (*fPeriodCycleRelation)(unsigned int cycleIndex, unsigned int totalCycles, unsigned int maxPeriod);

// Returns a constant period
unsigned int constantPeriod(unsigned int cycleIndex, unsigned int totalCycles, unsigned int maxPeriod)
{
    return maxPeriod;
}

// Returns a period that rises as the cycleIndex rises (linear)
unsigned int risingPeriod(unsigned int cycleIndex, unsigned int totalCycles, unsigned int maxPeriod)
{
    return cycleIndex * maxPeriod / totalCycles;
}

// Returns a period that falls as the cycleIndex rises (linear)
unsigned int fallingPeriod(unsigned int cycleIndex, unsigned int totalCycles, unsigned int maxPeriod)
{
    return maxPeriod - cycleIndex * maxPeriod / totalCycles;
}

// Returns a falling, then rising parabolic period
unsigned int valleyPeriod(unsigned int cycleIndex, unsigned int totalCycles, unsigned int maxPeriod)
{
    unsigned int halfCycle = totalCycles / 2;
    unsigned int mainPart = cycleIndex - halfCycle;

    return mainPart * mainPart * maxPeriod / (halfCycle * halfCycle);
}

// Returns the opposite of the valleyPeriod
unsigned int hillPeriod(unsigned int cycleIndex, unsigned int totalCycles, unsigned int maxPeriod)
{
    return maxPeriod - valleyPeriod(cycleIndex, totalCycles, maxPeriod);
}

void _makeSound(unsigned int cycles, unsigned long period, unsigned int nTimes, fPeriodCycleRelation f)
{
    for (unsigned int i = 0; i < nTimes; i++)
    {
        for (unsigned int c = 0; c < cycles; c++)
        {
            BEEPER = !BEEPER;
            unsigned int n = (*f)(c, cycles, period);
            for (unsigned int p = 0; p < n; p++)
                ;
        }
        if (i > 0 && i < nTimes - 1)
            __delay_ms(300);
    }
}

void makeSound(unsigned int cycles, unsigned long period, unsigned int nTimes)
{
    return _makeSound(cycles, period, nTimes, &constantPeriod);
}

#define CLOCK_FREQ 48000000
void playNote(char notePlus)
{
    enum MusicalNote note = notePlus & MUSICAL_NOTE_MASK;
    unsigned int scalingValue = 0, frequency = 0, period = 0;

    switch (note)
    {
    case C:
        frequency = 33;
        period = CLOCK_FREQ / 33; //1454545;
        break;
    case D:
        frequency = 37;
        period = CLOCK_FREQ / 37; // 1297297; // clock frequency divided by note frequency
        break;
    case E:
        frequency = 41;
        period = CLOCK_FREQ / 41; // 1170731;
        break;
    case F:
        frequency = 44;
        period = CLOCK_FREQ / 44; // 1090909;
        break;
    case G:
        frequency = 49;
        period = CLOCK_FREQ / 49;
        break;
    case A:
        frequency = 55;
        period = CLOCK_FREQ / 55;
        break;
    case B:
        frequency = 62;
        period = CLOCK_FREQ / 62;
        break;
    case Ou:
        currentOctave = MIN(MAX_OCTAVE, currentOctave + 1);
        break;
    case Od:
        currentOctave = MAX(1, currentOctave - 1);
        break;
    case Or:
        currentOctave = DEFAULT_OCTAVE;
        break;
    default:
        // REST and unsupported notes
        period = 0;
    }

    enum MusicalNoteLength noteLength = notePlus & ~MUSICAL_NOTE_MASK;
    unsigned int length = EIGHTH_NOTE_DURATION_CYCLES;

    switch (noteLength)
    {
    case QuarterNote:
        length = length * 2;
        break;
    case ThreeEighthNote:
        length = length * 3;
        break;
    case HalfNote:
        length = length * 4;
        break;
    case SixEighthNote:
        length = length * 6;
        break;
    case FullNote:
        length = length * 8;
        break;
    }

    if (note == Rest)
        makeSound(1, length, 1);
    else
        makeSound(length, period / currentOctave / PERIOD_SCALE, 1);

    __delay_ms(50);
}

void playMorseCodeDotSound()
{
    _makeSound(MORSE_CODE_DOT_CYCLES, MORSE_CODE_DOT_PERIOD / PERIOD_SCALE, 1, &risingPeriod);
}

void playMorseCodeDashSound()
{
    _makeSound(MORSE_CODE_DOT_CYCLES * 3, MORSE_CODE_DOT_PERIOD / PERIOD_SCALE, 1, &valleyPeriod);
}

#define MAX_SONG_LENGTH 10
unsigned char testOctaveUp[] = {C | FullNote, Ou, C | FullNote, Ou, C | FullNote, TheEnd};
unsigned char testOctaveDown[] = {C | FullNote, Od, C | FullNote, Od, C | FullNote, TheEnd};
unsigned char testRest[] = {C, Rest, C | QuarterNote, Rest | QuarterNote, C | FullNote, Rest | FullNote, C | FullNote, TheEnd};
unsigned char westworldTheme[] = {E | QuarterNote, F, E | QuarterNote, F, E, D, C | ThreeEighthNote, D | FullNote, D | QuarterNote, E, D | QuarterNote, E, D, C, A | HalfNote, A | FullNote, TheEnd};
unsigned char maryHadALittleLamb[] = {B, A, G, A, B, B, B | QuarterNote, A, A, A | QuarterNote, B, C, C | QuarterNote, B, A, G, A, B, B, B | QuarterNote, A, A, B, A, G | QuarterNote, G | HalfNote, TheEnd};
//unsigned char *songs[] = {maryHadALittleLamb, westworldTheme};
unsigned char *songs[] = {testOctaveUp, testOctaveDown, testRest};
unsigned int currentSongIndex = 0;

void playTestSounds()
{
    unsigned char *song = songs[currentSongIndex];
    unsigned int i = 0;
    while (song[i] != TheEnd || i > MAX_SONG_LENGTH)
        playNote(song[i++]);

    currentSongIndex = (currentSongIndex + 1) % (sizeof(songs) / sizeof(songs[0]));
}
