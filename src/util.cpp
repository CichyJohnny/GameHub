#include <Arduino.h>
#include "globals.h"
#include "memory_game.h"
#include "whack_game.h"

#include "util.h"

void turnOffAllLeds(const uint8_t ledPins[], uint8_t numLeds) {
    for (uint8_t i = 0; i < numLeds; i++) {
        digitalWrite(ledPins[i], LOW); // Turn off LED
    }
}

void showMenu() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(10, 10);
    display.println("== Select Game ==");

    display.setCursor(30, 35);
    display.setTextSize(2);
    display.println(games[selectedGame]);

    display.display();
}

void startGame(int index) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(10, 20);
    display.print("Starting: ");
    display.println(games[index]);
    display.display();

    turnOffAllLeds(ledPins, MAX_BUTTONS); // Turn off all LEDs before starting a game

    switch (index) {
        case 0:
            memoryGame();
            break;
        case 1:
            whackGame();
            break;
        default:
            break;
    }

    inMenu = true;
    showMenu();
}