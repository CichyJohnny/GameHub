#include <Arduino.h>
#include "globals.h"
#include "direction_game.h"

const uint8_t MAX_LENGTH = 10;
uint8_t sequence2[MAX_LENGTH];
const uint16_t TIME_LIMIT = 10000; // 10s per round

void generateSequence2(uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        sequence2[i] = random(0, 6);
    }
}

void showSequence(uint8_t length) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Repeat the sequence:");

    for (uint8_t i = 0; i < length; i++) {
        display.print(sequence2[i]);
        display.print(" ");
    }

    display.display();
}

bool getUserInput(uint8_t length) {
    uint8_t index = 0;
    unsigned long start = millis();

    while (index < length && millis() - start < TIME_LIMIT) {
        // Show remaining time
        unsigned long remaining = (TIME_LIMIT - (millis() - start)) / 1000;

        display.fillRect(0, 30, 128, 10, SH110X_BLACK);
        display.setCursor(0, 30);
        display.print("Time left: ");
        display.print(remaining);
        display.print("s");
        display.display();

        for (uint8_t i = 0; i < 6; i++) {
            if (!digitalRead(buttonPins[i])) {
                while (!digitalRead(buttonPins[i])); // wait for release (simple debounce)

                if (i != sequence2[index]) return false;
                index++;
                delay(150);
            }
        }
    }

    return (index == length);
}

void directionGame() {
    uint8_t round = 1;
    bool playing = true;

    while (playing && round <= MAX_LENGTH) {
        generateSequence2(round);
        showSequence(round);
        delay(1500);

        display.clearDisplay();
        display.setCursor(0, 0);
        display.setTextSize(1);
        display.println("Repeat now!");
        display.display();

        if (getUserInput(round)) {
            display.clearDisplay();
            display.setCursor(0, 20);
            display.setTextSize(2);
            display.println("Correct!");
            display.display();
            delay(1000);
            round++;
        } else {
            display.clearDisplay();
            display.setCursor(0, 20);
            display.setTextSize(2);
            display.println("Wrong!");
            display.display();
            delay(2000);
            playing = false;
        }
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Game Over!");
    display.print("Rounds passed: ");
    display.println(round - 1);
    display.display();
    delay(4000);
}
