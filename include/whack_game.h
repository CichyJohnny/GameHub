#ifndef WHACK_GAME_H
#define WHACK_GAME_H

#include <Adafruit_SH110X.h>

void whackGame(const int buttonPins[], const int ledPins[], Adafruit_SH1106G& display);

#endif
