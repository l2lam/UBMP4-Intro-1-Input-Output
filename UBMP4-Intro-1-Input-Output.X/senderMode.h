#define EOS '\0'
#define DOT '.'
#define DASH '-'
#define WORD_SEPARATOR ' '
#define UNIT_LENGTH_MS 300
#define MAX_MESSAGE_LENGTH 100

/*
const char *CHAR2MORSE = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
                          "....", "..", ".---", "-.-", ".-..", "--", "-.", "---",
                          ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--",
                          "-..-", "-.--", "--.."};
                          */

char message[MAX_MESSAGE_LENGTH];
unsigned int currentMessageIndex = 0;

enum senderState
{
    AcceptingInput,
    Transmitting
};
enum senderState currentSenderState = AcceptingInput;

void transmitDot();
void transmitDash();
void transmitCharSeparator();
void transmitWordSeparator();
void resetMessage();
void transmitMessage();
void pushToMessage(char c);
void endMessage();
void checkForSenderStateChange();
void processSenderMode();
