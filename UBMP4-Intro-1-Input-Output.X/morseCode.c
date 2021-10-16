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

#define BUTTON_PRESSED(n) (SW##n == 0)
#define TURN_ON_LED(n) LED##n = 1
#define TURN_OFF_LED(n) LED##n = 0
//#define NELEMS(x) (sizeof(x) / sizeof((x)[0]))

#include "xc.h"      // Microchip XC8 compiler include file
#include "stdint.h"  // Include integer definitions
#include "stdbool.h" // Include Boolean (true/false) definition
#include "UBMP4.h"   // Include UBMP4 constants and functions
//#include "morse.h"

#define UNIT_LENGTH_MS 500
/*
const char *CHAR2MORSE = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
                          "....", "..", ".---", "-.-", ".-..", "--", "-.", "---",
                          ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--",
                          "-..-", "-.--", "--.."};
                          */

enum modeType
{
    Sender,
    Receiver,
    Diagnostic
};
enum modeType currentMode = Sender;

enum senderState
{
    AcceptingInput,
    Transmitting
};
enum senderState currentSenderState = Transmitting;
char *message = ".-";
#define MAX_MESSAGE_LENGTH 100

void transmitDot()
{
    TURN_ON_LED(4);
    __delay_ms(UNIT_LENGTH_MS);
    TURN_OFF_LED(4);
}
void transmitDash()
{
    TURN_ON_LED(5);
    __delay_ms(UNIT_LENGTH_MS * 3);
    TURN_OFF_LED(5);
}
void transmitCharSeparator()
{
    __delay_ms(UNIT_LENGTH_MS);
}
void transmitWordSeparator()
{
    __delay_ms(UNIT_LENGTH_MS * 2);
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
        TURN_ON_LED(3);
        TURN_OFF_LED(6);
        switch (currentSenderState)
        {
        case AcceptingInput:
            break;
        case Transmitting:
        {
            for (int i = 0; i < MAX_MESSAGE_LENGTH; i++)
            {
                char code = message[i];
                if (code != '\0')
                {
                    switch (code)
                    {
                    case '.':
                        transmitDot();
                        break;
                    case '-':
                        transmitDash();
                        break;
                    default:
                        transmitWordSeparator();
                        break;
                    }
                    transmitCharSeparator();
                }
                else
                    break;
            }
        }
        }
        break;
    case Diagnostic:
        TURN_ON_LED(3);
        TURN_ON_LED(6);
        break;
    }
}

void processModeToggles()
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

// TODO Set linker ROM ranges to 'default,-0-7FF' under "Memory model" pull-down.
// TODO Set linker code offset to '800' under "Additional options" pull-down.

// The main function is required, and the program begins executing from here.

int main(void)
{
    // Configure oscillator and I/O ports. These functions run once at start-up.
    OSC_config();   // Configure internal oscillator for 48 MHz
    UBMP4_config(); // Configure on-board UBMP4 I/O devices

    IOCBNbits.IOCBN7 = 1;
    INTCONbits.IOCIE = 1;
    INTCONbits.GIE = 1;

    // Code in this while loop runs repeatedly.
    while (1)
    {
        processMode(currentMode);
        processModeToggles();
        checkForReset();
    }
}
///*
void __interrupt() isr()
{
    if (INTCONbits.IOCIF == 1)
    {
        INTCONbits.IOCIF = 0;
        if (IOCBFbits.IOCBF7 == 1)

            if (IOCBFbits.IOCBF7 == 1)
            {
                /*
            TURN_ON_LED(6);
            IOCBFbits.IOCBF7 = 0;
            BEEPER = 1;
            for (int i = 0; i < 200; i++)
                ;
            BEEPER = 0;
            */
                processModeToggles();
            }
    }
}
//*/