#include "xc.h"      // Microchip XC8 compiler include file
#include "stdbool.h" // Definitions for boolean symbols
#include "UBMP4.h"   // Include UBMP4 constants and functions
#include "convenience.h"
#include "buzzer.h"

#define MIN(x, y) x < y ? x : y
#define MAX(x, y) x < y ? y : x
unsigned long pow(unsigned long x, char y)
{
    unsigned long result = 1;
    for (char i = 0; i < y; i++)
        result *= x;
    return result;
}

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

    return pow(mainPart, 2) * maxPeriod / pow(halfCycle, 2);
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

#define CLOCK_FREQ 48000000
unsigned long lowerNotePeriods[] = {
    // These period values must align with the MusicalNote indexes
    // Note frequency values attained from https://pages.mtu.edu/~suits/notefreqs.html
    // The period is calculated by dividing the clock frequency the by note frequency
    CLOCK_FREQ / 1635 * 100, // C
    CLOCK_FREQ / 1732 * 100, // Cs
    CLOCK_FREQ / 1835 * 100, // D
    CLOCK_FREQ / 1945 * 100, // Ds
    CLOCK_FREQ / 2060 * 100, // E
    CLOCK_FREQ / 2183 * 100, // F
    CLOCK_FREQ / 2312 * 100, // Fs
    CLOCK_FREQ / 2450 * 100, // G
    CLOCK_FREQ / 2596 * 100, // Gs
    CLOCK_FREQ / 2750 * 100, // A
    CLOCK_FREQ / 2914 * 100, // As
    CLOCK_FREQ / 3087 * 100, // B
};

void playNote(char notePlus)
{
    enum MusicalNote note = notePlus & MUSICAL_NOTE_MASK;
    unsigned long period = 0;

    switch (note)
    {
    case Ou:
        currentOctave = MIN(MAX_OCTAVE, currentOctave + 1);
        return;
    case Od:
        currentOctave = MAX(1, currentOctave - 1);
        return;
    case Or:
        currentOctave = DEFAULT_OCTAVE;
        return;
    case Rest:
        // It shouldn't matter what the period is, as long as the total cycles normalizes to the proper
        // note length.  We just want the Rest to be silent for the correct length of time.
        period = CLOCK_FREQ / 62;
        break;
    default:
        if (note <= B)
            period = lowerNotePeriods[note];
        break;
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
    unsigned long adjustedPeriod = period / pow(2, currentOctave) / PERIOD_SCALE;
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

#define MAX_SONG_LENGTH 200
//unsigned char testScale[] = {Or, A | FullNote, B | FullNote, Ou, C | FullNote, D | FullNote, E | FullNote, D | FullNote, C | FullNote, Od, B | FullNote, A | FullNote, TheEnd};
//unsigned char testOctaveUp[] = {Or, C | HalfNote, Ou, C | HalfNote, Ou, C | HalfNote, Ou, C | HalfNote, Ou, C | HalfNote, TheEnd};
//unsigned char testOctaveDown[] = {Or, C | FullNote, Od, C | FullNote, Od, C | FullNote, TheEnd};
//unsigned char testRest[] = {Or, C, Rest, C | QuarterNote, Rest | QuarterNote, C | FullNote, Rest | FullNote, C | FullNote, TheEnd};
unsigned char westworldTheme[] = {Or, E | QuarterNote, F, E | QuarterNote, F, E, D, C | ThreeEighthNote, D | FullNote, D | QuarterNote, E, D | QuarterNote, E, D, C, Od, G | HalfNote, Ou, A | FullNote, TheEnd};
unsigned char maryHadALittleLamb[] = {Or, B, A, G, A, B, B, B | QuarterNote, A, A, A | QuarterNote, B, Ou, D, D | QuarterNote, Rest | QuarterNote, Od, B, A, G, A, B, B, B | QuarterNote, A, A, B, A, G | QuarterNote, G | HalfNote, TheEnd};
unsigned char furElise[] = {Or, E, Ds, E, Ds, E, Od, B, Ou, D, C, Od, A | QuarterNote, Rest,
                            C, E, A, B | QuarterNote, Rest,
                            E, Gs, B, Ou, C | QuarterNote, Rest,
                            Od, E, Ou, E, Ds, E, Ds, E, Od, B, Ou, D, C, Od, A | QuarterNote, Rest,
                            C, E, A, B | QuarterNote, Rest,
                            E, Ou, C, Od, B, A | QuarterNote,
                            B, Ou, C, D, E | QuarterNote, Rest,
                            Od, G, Ou, F, E, D | QuarterNote, Rest,
                            Od, F, Ou, E, D, C | QuarterNote, Rest,
                            Od, E, Ou, D, C, Od, B | SixEighthNote, Rest | HalfNote,
                            Ou, E, Ds, E, Ds, E, Od, B, Ou, D, C, Od, A | QuarterNote, Rest,
                            C, E, A, B | QuarterNote, Rest,
                            E, Gs, B, Ou, C | QuarterNote, Rest,
                            Od, E, Ou, E, Ds, E, Ds, E, Od, B, Ou, D, C, Od, A | QuarterNote, Rest,
                            C, E, A, B | QuarterNote, Rest, E, Ou, C, Od, B, A | SixEighthNote, Rest | HalfNote,
                            TheEnd};
unsigned char *songs[] = {furElise, maryHadALittleLamb, westworldTheme};
//unsigned char *songs[] = {testScale, testOctaveUp}; //, maryHadALittleLamb, westworldTheme};
unsigned int currentSongIndex = 0;

void playTestSounds()
{
    unsigned char *song = songs[currentSongIndex];
    unsigned char i = 0;
    while (song[i] != TheEnd && i < MAX_SONG_LENGTH)
        playNote(song[i++]);

    currentSongIndex = (currentSongIndex + 1) % (sizeof(songs) / sizeof(songs[0]));
}
