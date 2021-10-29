#include "xc.h"      // Microchip XC8 compiler include file
#include "stdbool.h" // Definitions for boolean symbols
#include "UBMP4.h"   // Include UBMP4 constants and functions
#include "convenience.h"
#include "buzzer.h"

#define MIN(x, y) x < y ? x : y
#define MAX(x, y) x < y ? y : x

// This is the definition of a function pointer type; so that we can pass in different functions to calculate
// the period given the current position in the cycle, the total # of cycles and the max period.
typedef unsigned long (*fPeriodCycleRelation)(unsigned int cycleIndex, unsigned long totalCycles, unsigned long maxPeriod);

// Returns a constant period
unsigned long constantPeriod(unsigned int cycleIndex, unsigned long totalCycles, unsigned long maxPeriod)
{
    return maxPeriod;
}

// Returns a period that rises as the cycleIndex rises (linear)
unsigned long risingPeriod(unsigned int cycleIndex, unsigned long totalCycles, unsigned long maxPeriod)
{
    return cycleIndex * maxPeriod / totalCycles;
}

// Returns a period that falls as the cycleIndex rises (linear)
unsigned long fallingPeriod(unsigned int cycleIndex, unsigned long totalCycles, unsigned long maxPeriod)
{
    return maxPeriod - cycleIndex * maxPeriod / totalCycles;
}

// Returns a falling, then rising parabolic period
unsigned long valleyPeriod(unsigned int cycleIndex, unsigned long totalCycles, unsigned long maxPeriod)
{
    unsigned long halfCycle = totalCycles / 2;
    unsigned long mainPart = cycleIndex - halfCycle;

    return mainPart * mainPart * maxPeriod / (halfCycle * halfCycle);
}

// Returns the opposite of the valleyPeriod
unsigned long hillPeriod(unsigned int cycleIndex, unsigned long totalCycles, unsigned long maxPeriod)
{
    return maxPeriod - valleyPeriod(cycleIndex, totalCycles, maxPeriod);
}

void _makeSound(unsigned long cycles, unsigned long period, fPeriodCycleRelation f, bool silent)
{
    for (unsigned int c = 0; c < cycles; c++)
    {
        if (!silent)
            BEEPER = !BEEPER;
        unsigned long n = (*f)(c, cycles, period);
        for (unsigned long p = 0; p < n; p++)
            ;
    }
}

void makeSound(unsigned long cycles, unsigned long period)
{
    _makeSound(cycles, period, &constantPeriod, false);
}

void makeMultipleSound(unsigned long cycles, unsigned long period, unsigned char nTimes)
{
    for (unsigned int i = 0; i < nTimes; i++)
    {
        makeSound(cycles, period);
        if (i > 0 && i < nTimes - 1)
            __delay_ms(300);
    }
}

#define FREQUENCE_SCALE 1000
#define CLOCK_FREQ 48000000 // * FREQUENCY_SCALE ... doing this to avoid large numbers
void playNote(char notePlus)
{
    enum MusicalNote note = notePlus & MUSICAL_NOTE_MASK;
    unsigned long scalingValue = 0, frequency = 0, period = 0;

    switch (note)
    {
    case C:
        frequency = 33;
        period = CLOCK_FREQ / 33; // * FREQUENCE_SCALE; //1454545;
        break;
    case D:
        frequency = 37;
        period = CLOCK_FREQ / 37; // * FREQUENCE_SCALE; // 1297297; // clock frequency divided by note frequency
        break;
    case E:
        frequency = 41;
        period = CLOCK_FREQ / 41; // * FREQUENCE_SCALE; // 1170731;
        break;
    case F:
        frequency = 44;
        period = CLOCK_FREQ / 44; // * FREQUENCE_SCALE; // 1090909;
        break;
    case G:
        frequency = 49;
        period = CLOCK_FREQ / 49; //  * FREQUENCE_SCALE;
        break;
    case A:
        frequency = 55;
        period = CLOCK_FREQ / 55; //  * FREQUENCE_SCALE;
        break;
    case B:
        frequency = 62;
        period = CLOCK_FREQ / 62; //  * FREQUENCE_SCALE;
        break;
    case Ou:
        currentOctave = MIN(MAX_OCTAVE, currentOctave + 1);
        return;
    case Od:
        currentOctave = MAX(1, currentOctave - 1);
        return;
    case Or:
        currentOctave = DEFAULT_OCTAVE;
        return;
    default:
        // REST and unsupported notes
        period = CLOCK_FREQ / 62;
    }

    enum MusicalNoteLength noteLength = notePlus & ~MUSICAL_NOTE_MASK;
    unsigned long length = EIGHTH_NOTE_DURATION_CYCLES;

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

    // We need to adjust the period by the octave (and a preferred scaling value)
    // Also, we want the note to play for the precise length of time regardless of the period
    // so we have to adjust the number of cycles by the period
    unsigned long adjustedPeriod = period * currentOctave / PERIOD_SCALE;
    _makeSound(length / adjustedPeriod, adjustedPeriod, constantPeriod, note == Rest ? true : false);

    __delay_ms(50);
}

void playMorseCodeDotSound()
{
    _makeSound(MORSE_CODE_DOT_CYCLES, MORSE_CODE_DOT_PERIOD / PERIOD_SCALE, &risingPeriod, false);
}

void playMorseCodeDashSound()
{
    _makeSound(MORSE_CODE_DOT_CYCLES * 3, MORSE_CODE_DOT_PERIOD / PERIOD_SCALE, &valleyPeriod, false);
}

#define MAX_SONG_LENGTH 100
unsigned char testOctaveUp[] = {C | FullNote, Ou, C | FullNote, Ou, C | FullNote, TheEnd};
unsigned char testOctaveDown[] = {C | FullNote, Od, C | FullNote, Od, C | FullNote, TheEnd};
unsigned char testRest[] = {C, Rest, C | QuarterNote, Rest | QuarterNote, C | FullNote, Rest | FullNote, C | FullNote, TheEnd};
unsigned char westworldTheme[] = {E | QuarterNote, F, E | QuarterNote, F, E, D, C | ThreeEighthNote, D | FullNote, D | QuarterNote, E, D | QuarterNote, E, D, C, Od, G | HalfNote, Ou, A | FullNote, TheEnd};
unsigned char maryHadALittleLamb[] = {B, A, G, A, B, B, B | QuarterNote, A, A, A | QuarterNote, B, C, C | QuarterNote, Rest | QuarterNote, B, A, G, A, B, B, B | QuarterNote, A, A, B, A, G | QuarterNote, G | HalfNote, TheEnd};
//unsigned char *songs[] = {maryHadALittleLamb, westworldTheme};
unsigned char *songs[] = {testOctaveUp, testOctaveDown, testRest, maryHadALittleLamb};
unsigned int currentSongIndex = 0;

void playTestSounds()
{
    unsigned char *song = songs[currentSongIndex];
    unsigned char i = 0;
    while (song[i] != TheEnd && i < MAX_SONG_LENGTH)
        playNote(song[i++]);

    currentSongIndex = (currentSongIndex + 1) % (sizeof(songs) / sizeof(songs[0]));
}
