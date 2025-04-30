#ifndef WHACK_GAME_H
#define WHACK_GAME_H

#include <Adafruit_SH110X.h>

void whackGame(const uint8_t buttonPins[], const uint8_t ledPins[], Adafruit_SH1106G& display);

#endif
