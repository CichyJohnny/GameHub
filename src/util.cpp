#include <Arduino.h>
#include "globals.h"
#include "memory_game.h"
#include "whack_game.h"
#include "order_game.h"
#include "duel_game.h"
#include "quiz_game.h"

#include "util.h"

void turnOffAllLeds(const uint8_t ledPins[], uint8_t numLeds) {
    for (uint8_t i = 0; i < numLeds; i++) {
        digitalWrite(ledPins[i], LOW); // Turn off LED
    }
}

int freeMemory() {
    extern int __heap_start, *__brkval;
    int v;
    return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

void showMenu() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(10, 10);
    display.println(F("== Select Game =="));

    display.setTextSize(0);
    display.setCursor(0, 50);
    display.print(freeMemory());

    display.setCursor(30, 35);
    display.setTextSize(2);
    display.println(games[selectedGame]);

    display.display();
}

void startGame(int index) {
    turnOffAllLeds(ledPins, MAX_BUTTONS); // Turn off all LEDs before starting a game

    switch (index) {
        case 0:
            memoryGame();
            break;
        case 1:
            whackGame();
            break;
        case 2:
            orderGame();
            break;
        case 3:
            duelGame();
            break;
        case 4:
            quizGame();
            break;

        default:
            break;
    }

    inMenu = true;
    showMenu();
}