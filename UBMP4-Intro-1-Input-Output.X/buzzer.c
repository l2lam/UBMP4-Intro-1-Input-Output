#include "xc.h"    // Microchip XC8 compiler include file
#include "UBMP4.h" // Include UBMP4 constants and functions
#include "convenience.h"
#include "buzzer.h"

typedef unsigned int (*fPeriodCycleRelation)(unsigned int cycleIndex, unsigned int totalCycles, unsigned int maxPeriod);
unsigned int constantPeriod(unsigned int cycleIndex, unsigned int totalCycles, unsigned int maxPeriod) {
    return maxPeriod;
}
unsigned int risingPeriod(unsigned int cycleIndex, unsigned int totalCycles, unsigned int maxPeriod) {
    return cycleIndex * maxPeriod / totalCycles;
}
unsigned int fallingPeriod(unsigned int cycleIndex, unsigned int totalCycles, unsigned int maxPeriod) {
    return maxPeriod - cycleIndex * maxPeriod / totalCycles;
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

void playNote(unsigned int notePlus)
{
    enum MusicalNote note = notePlus & MUSICAL_NOTE_MASK;
    unsigned int scalingValue = 0, frequency = 0, period = 0;

    switch (note)
    {
    case C:
        scalingValue = 255;
        frequency = 2441;
        period = 19664;
        break;
    case D:
        scalingValue = 227;
        frequency = 2741;
        period = 17512; // clock frequency divided by note frequency
        break;
    case E:
        scalingValue = 204;
        frequency = 3048;
        period = 15748;
        break;
    case F:
        scalingValue = 191;
        frequency = 3255;
        period = 14747;
        break;
    case G:
        scalingValue = 170;
        frequency = 3654;
        period = 13136;
        break;
    case A:
        scalingValue = 153;
        frequency = 4058;
        period = 11828;
        break;
    case B:
        scalingValue = 136;
        frequency = 4562;
        period = 10522;
        break;
    case C2:
        scalingValue = 127;
        frequency = 4882;
        period = 9832;
        break;
    default:
        // REST and unsupported notes
        period = 0;
    }

    enum MusicalNoteLength noteLength = notePlus & ~MUSICAL_NOTE_MASK;
    unsigned int length = QUARTER_NOTE_DURATION_CYCLES;

    switch (noteLength)
    {
    case OneThirdNote:
        length = length * 4 / 3;
        break;
    case HalfNote:
        length = length * 2;
        break;
    case TwoThirdNote:
        length = length * 8 / 3;
        break;
    case ThreeQuarterNote:
        length = length * 3;
        break;
    case FullNote:
        length = length * 4;
        break;
    }

    makeSound(length, period / PERIOD_SCALE, 1);
    __delay_ms(50);
}

void playMorseCodeDotSound()
{
    _makeSound(MORSE_CODE_DOT_CYCLES, MORSE_CODE_DOT_PERIOD / PERIOD_SCALE, 1, &risingPeriod);
}

void playMorseCodeDashSound()
{
    _makeSound(MORSE_CODE_DOT_CYCLES * 3, MORSE_CODE_DOT_PERIOD / PERIOD_SCALE, 1, &fallingPeriod);
}
