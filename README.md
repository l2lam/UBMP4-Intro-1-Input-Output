# What is this project about?

This is a sample project using Microchip's MPLAB X IDE to demonstrate basic control of circuit components that on a [UBMP4](https://mirobo.tech) circuit board.
The program is a [Morse Code](https://en.wikipedia.org/wiki/Morse_code) Receiver and Transmitter. Buttons are used for mode switching and data input. Output is done via LEDs, speaker and eventually, an IR transmitter. At some point an IR receiver could also be used for input.

# Who is this project for?

Anyone interested in writing simple programs for the Microchip PIC16x microprocessor, and particularly the [UBMP4](https://mirobo.tech) circuit design.

# User Interface

SW1 is reserved for resetting the boarding into boot-loader mode.

## Program Modes

The program has 3 modes:

1. Sender - for taking user input (morse code) and transmitting it.
2. Receiver - for receiving morse code signals (somehow) and playing it back on the device.
3. Diagnostic - for debugging (future)

The program starts in Sender mode. Users toggle between modes by simultaneously pressing SW2 and SW5.
