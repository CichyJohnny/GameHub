#ifndef GLOBALS_H
#define GLOBALS_H

#include <Adafruit_SH110X.h>

extern const uint8_t i2c_Address;
extern const uint8_t SCREEN_WIDTH;
extern const uint8_t SCREEN_HEIGHT;
extern const int8_t OLED_RESET;

extern Adafruit_SH1106G display;

extern const uint8_t ledPins[6];
extern const uint8_t buttonPins[6];

extern const uint8_t MAX_BUTTONS;

extern const uint8_t NUM_GAMES;
extern const char* games[5];

extern int selectedGame;
extern bool inMenu;

#endif