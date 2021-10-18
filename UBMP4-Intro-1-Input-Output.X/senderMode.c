#include "xc.h"          // Microchip XC8 compiler include file
#include "UBMP4.h"       // Include UBMP4 constants and functions
#include "convenience.h" // Include convenience utilities
#include "senderMode.h"

void transmitDot()
{
    TURN_ON_LED(4);
    __delay_ms(UNIT_LENGTH_MS);
    TURN_OFF_LED(4);
}
void transmitDash()
{
    TURN_ON_LED(4);
    __delay_ms(UNIT_LENGTH_MS * 3);
    TURN_OFF_LED(4);
}
void transmitCharSeparator()
{
    __delay_ms(UNIT_LENGTH_MS);
}
void transmitWordSeparator()
{
    __delay_ms(UNIT_LENGTH_MS * 2);
}
void resetMessage()
{
    currentMessageIndex = 0;
    for (int i; i < MAX_MESSAGE_LENGTH; i++)
        message[i] = EOS;
}
void transmitMessage()
{
    currentSenderState = Transmitting;
    currentMessageIndex = 0;
    makeSound(600, 50, 4);
}
void pushToMessage(char c)
{
    message[currentMessageIndex++] = c;
}
void endMessage()
{
    message[currentMessageIndex] = EOS;
}
void checkForSenderStateChange()
{
    if (BUTTON_PRESSED(2))
    {
        switch (currentSenderState)
        {
        case Transmitting:
            currentSenderState = AcceptingInput;
            FLASH_2_LEDS(4, 6, UNIT_LENGTH_MS);
            makeSound(500, 100, 2);
            break;
        case AcceptingInput:
            currentSenderState = Transmitting;
            FLASH_2_LEDS(5, 6, UNIT_LENGTH_MS);
            makeSound(800, 100, 3);
            break;
        }
        currentMessageIndex = 0;
    }
}
void processSenderMode()
{
    TURN_ON_LED(3);
    TURN_OFF_LED(6);
    switch (currentSenderState)
    {
    case AcceptingInput:
        if (currentMessageIndex >= MAX_MESSAGE_LENGTH)
        {
            // When the max length is reach then send the message
            transmitMessage();
        }
        else if (BUTTON_PRESSED(3) && BUTTON_PRESSED(4))
        {
            // When user ends input then send the message
            endMessage();
            transmitMessage();
        }
        else if (BUTTON_PRESSED(3))
        {
            pushToMessage(DOT);
            FLASH_LED(4, UNIT_LENGTH_MS);
        }
        else if (BUTTON_PRESSED(4))
        {
            pushToMessage(DASH);
            FLASH_LED(5, UNIT_LENGTH_MS);
        }
        else if (BUTTON_PRESSED(5))
        {
            pushToMessage(WORD_SEPARATOR);
            FLASH_LED(6, UNIT_LENGTH_MS);
        }

        // Add a delay to reduce detecting redundant button press states
        __delay_ms(500);
        break;
    case Transmitting:
        if (currentMessageIndex < MAX_MESSAGE_LENGTH)
        {
            char code = message[currentMessageIndex];
            if (code != EOS)
            {
                switch (code)
                {
                case DOT:
                    transmitDot();
                    break;
                case DASH:
                    transmitDash();
                    break;
                default:
                    transmitWordSeparator();
                    break;
                }
                transmitCharSeparator();
                currentMessageIndex++;
            }
            else
                currentMessageIndex = 0;
        }
        else
            currentMessageIndex = 0;
        break;
    }
    checkForSenderStateChange();
}
