#include "xc.h"    // Microchip XC8 compiler include file
#include "UBMP4.h" // Include UBMP4 constants and functions

void makeSound(unsigned int cycles, unsigned int period, unsigned int nTimes)
{
    for (unsigned int i = 0; i < nTimes; i++)
    {
        for (unsigned int c = 0; c < cycles; c++)
        {
            BEEPER = !BEEPER;
            for (unsigned int p = 0; p < period; p++)
                ;
        }
        if (nTimes > 1)
            __delay_ms(300);
    }
}
