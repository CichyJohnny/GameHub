#include <Arduino.h>
#include "globals.h"

#include "order_game.h"

const uint8_t MAX_LENGTH = 10;
uint8_t sequence2[MAX_LENGTH];
const uint16_t TIME_LIMIT = 10000; // 10s per round
const uint8_t START_ROUND = 3;

void generateSequence2(uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        sequence2[i] = random(0, MAX_BUTTONS);
    }
}

void showSequence(uint8_t length) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println(F("Repeat the sequence:"));

    for (uint8_t i = 0; i < length; i++) {
        display.print(sequence2[i]);
        display.print(F(" "));
    }

    display.display();
}

bool getUserInput(uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        bool pressed = false;
        unsigned long start = millis();

        while (!pressed && millis() - start < 10000) {  // 10s timeout
        for (uint8_t j = 0; j < MAX_BUTTONS; j++) {
            if (!digitalRead(buttonPins[j])) {
                digitalWrite(ledPins[j], HIGH);
                delay(300);
                digitalWrite(ledPins[j], LOW);

                if (j != sequence2[i]) return false;

                pressed = true;
                delay(200);

                break;
            }
        }
        }
        if (!pressed) return false;
    }
    return true;
}

void orderGame() {
    uint8_t round2 = START_ROUND;

    while (round2 <= MAX_LENGTH) {
        generateSequence2(round2);
        showSequence(round2);
        delay(3000);

        display.clearDisplay();
        display.setCursor(0, 0);
        display.setTextSize(1);
        display.println(F("Repeat now!"));
        display.display();

        if (getUserInput(round2)) {
            display.clearDisplay();
            display.setCursor(0, 20);
            display.setTextSize(2);
            display.println(F("Correct!"));
            display.display();
            delay(1000);
            round2++;
        } else {
            display.clearDisplay();
            display.setCursor(0, 20);
            display.setTextSize(2);
            display.println(F("Wrong!"));
            display.display();
            delay(2000);
            break;
        }
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println(F("Game Over!"));
    display.print(F("Rounds passed: "));
    display.println(round2 - START_ROUND);
    display.display();
    delay(4000);
}
