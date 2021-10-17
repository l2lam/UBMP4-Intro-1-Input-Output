# What is this project about?

This is a sample project using Microchip's MPLAB X IDE to demonstrate basic control of circuit components that on a [UBMP4](https://mirobo.tech) circuit board.
The program is a [Morse Code](https://en.wikipedia.org/wiki/Morse_code) Receiver and Transmitter. Buttons are used for mode switching and data input. Output is done via LEDs, speaker and eventually, an IR transmitter. At some point an IR receiver could also be used for input.

# Who is this project for?

Students or anyone interested in writing simple programs for the Microchip PIC16x microprocessor, and particularly the [UBMP4](https://mirobo.tech) circuit design.

# User Interface

SW1 is reserved for resetting the boarding into boot-loader mode.

## Program Modes

The program has 3 modes:

1. Sender - for taking user input (morse code) and transmitting it
   > In this mode (LE)D3 is on and D6 is off
2. Receiver - for receiving morse code signals (somehow) and playing it back on the device
   > In this mode D6 is on and D3 is off
3. Diagnostic - for debugging (future)
   > In this mode both D3 and D6 are on

The program starts in Sender mode. Users toggle between modes by simultaneously pressing SW2 and SW5

## Sender Mode

Sender mode has 2 sub-modes (states):

1. Accepting Input - lets the user input the morse code message
   > Users input a DOT using SW3; a DASH using SW4; and a letter boundary using SW5
   > Users can end the message and automatically switch to Transmitting by pressing SW3 and SW4 simultaneously
2. Transmitting - repeated sends the message

The program starts in the Accepting Input state. Users toggle between states by pressing SW2

## Receiver Mode

TODO

## Diagnostic Mode

TODO
