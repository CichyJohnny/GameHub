#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SH110X.h>

#include "globals.h"

const uint8_t i2c_Address = 0x3c;
const uint8_t SCREEN_WIDTH = 128;
const uint8_t SCREEN_HEIGHT = 64;
const int8_t OLED_RESET = -1;

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const uint8_t ledPins[6] = {2, 4, 6, 8, 10, 12};
const uint8_t buttonPins[6] = {3, 5, 7, 9, 11, 13};

const uint8_t MAX_BUTTONS = 3;

const uint8_t NUM_GAMES = 3;
const char* games[3] = {"Memory", "Whack", "Tetris"};

int selectedGame = 0;
bool inMenu = true;