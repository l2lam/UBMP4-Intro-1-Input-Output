/*==============================================================================
 Project: Intro-1-Input-Output
 Date:    May 16, 2021
 
 This example UBMP4 input and output program demonstrates pushbutton input, LED
 (bit) output, port latch (byte) output, time delay functions, and simple 'if'
 condition structures.
 
 Additional program analysis and programming activities demonstrate byte output,
 logical condition operators AND and OR, using delay functions to create sound,
 and simulated start-stop button functionality.
==============================================================================*/

//#define USING_INTERRUPTS // Uncomment this to enable the interrupt handling

#include "xc.h"          // Microchip XC8 compiler include file
#include "stdint.h"      // Include integer definitions
#include "stdbool.h"     // Include Boolean (true/false) definition
#include "UBMP4.h"       // Include UBMP4 constants and functions
#include "convenience.h" // Include convenience utilities
#include "buzzer.h"      // Include Buzzer utilities
#include "senderMode.h"  // Include sender mode definitions

#define USING_INTERRUPTS 1

enum modeType
{
    Sender,
    Receiver,
    Diagnostic
};
enum modeType currentMode = Diagnostic;

#define NNOTES 26
void playTestSounds()
{
    // Test song: mary had a little lamb
    unsigned int song[NNOTES] = {B, A, G, A, B, B, B | FullNote, A, A, A | HalfNote, B, B, B | HalfNote, B, A, G, A, B, B, B, A, A, B, A, G | HalfNote, G | FullNote};
    //enum MusicalNote song[NNOTES] = {B, A, G, A, B, B, B};
    for (int i = 0; i < NNOTES; i++)
        playNote(song[i]);
}

void processMode(enum modeType mode)
{
    // Set mode indicators
    switch (mode)
    {
    case Receiver:
        TURN_ON_LED(6);
        TURN_OFF_LED(3);
        break;
    case Sender:
        processSenderMode();
        break;
    case Diagnostic:
        TURN_ON_LED(3);
        TURN_ON_LED(6);
        if (BUTTON_PRESSED(2) && !BUTTON_PRESSED(5))
            playTestSounds();
        else if (BUTTON_PRESSED(3))
        {
            FLASH_LED(4, UNIT_LENGTH_MS);
            PERIOD_SCALE -= 1;
        }
        else if (BUTTON_PRESSED(4))
        {
            FLASH_LED(5, UNIT_LENGTH_MS);
            PERIOD_SCALE += 1;
        }
        else if (BUTTON_PRESSED(5))
        {
            FLASH_LED(6, UNIT_LENGTH_MS);
            QUARTER_NOTE_DURATION_CYCLES = (QUARTER_NOTE_DURATION_CYCLES + 100) % 1000;
        }
        __delay_ms(200);
        break;
    }
}

void checkForModeChange()
{
    if (BUTTON_PRESSED(2) && BUTTON_PRESSED(5))
    {
        switch (currentMode)
        {
        case Sender:
            currentMode = Receiver;
            break;
        case Receiver:
            currentMode = Diagnostic;
            break;
        case Diagnostic:
            currentMode = Sender;
            break;
        }

        // Add a delay to reduce accidental rapid toggles
        __delay_ms(200);
    }
}

void checkForReset()
{
    if (BUTTON_PRESSED(1))
        RESET();
}

#if USING_INTERRUPTS
void setupInterrupts()
{
    SW1_INTERRUPT_ENABLE = 1;
    INTCONbits.IOCIE = 1;
    INTCONbits.GIE = 1;
}
void __interrupt() isr()
{
    if (INTCONbits.IOCIF == 1)
    {
        INTCONbits.IOCIF = 0;
        if (SW1_INTERRUPT_FLAG == 1)
        {
            SW1_INTERRUPT_FLAG = 0;
            FLASH_LED(6, 100);
            makeSound(400, 300, 1);
            checkForReset();
        }
    }
}
#endif
// TODO Set linker ROM ranges to 'default,-0-7FF' under "Memory model" pull-down.
// TODO Set linker code offset to '800' under "Additional options" pull-down.

// This is the entry point for the program
int main(void)
{
    // Configure oscillator and I/O ports. These functions run once at start-up.
    OSC_config();   // Configure internal oscillator for 48 MHz
    UBMP4_config(); // Configure on-board UBMP4 I/O devices

#if USING_INTERRUPTS
    setupInterrupts();
#endif

    resetMessage();

    // Code in this while loop runs repeatedly.
    while (1)
    {
        processMode(currentMode);
        checkForModeChange();
        checkForReset();
    }
}
