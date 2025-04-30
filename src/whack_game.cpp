#include <Arduino.h>
#include "globals.h"

#include "whack_game.h"


void whackGame() {
    const uint8_t rounds = 20;
    const uint16_t timeLimit = 1000; // ms to respond
    uint8_t score = 0;

    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println(F("Whack-a-Button!"));
    display.println(F("Hit the LED fast!"));
    display.display();
    delay(1500);

    for (uint8_t round = 1; round <= rounds; round++) {
        uint8_t target = random(0, MAX_BUTTONS);

        // Flash LED
        digitalWrite(ledPins[target], HIGH);
        unsigned long startTime = millis();
        bool hit = false;

        while (millis() - startTime < timeLimit) {
        for (uint8_t i = 0; i < MAX_BUTTONS; i++) {
            if (!digitalRead(buttonPins[i])) {
                if (i == target) {
                    score++;
                    hit = true;
                }
                break;
                }
            }
            if (hit) break;
        }

        digitalWrite(ledPins[target], LOW);
        delay(200);

        display.clearDisplay();
        display.setCursor(0, 40);
        display.setTextSize(1);
        display.print(F("Scored: "));
        display.println(score);
        display.display();
    }

    display.clearDisplay();
    display.setCursor(0, 20);
    display.setTextSize(2);
    display.println(F("Game Over!"));
    display.setCursor(0, 40);
    display.setTextSize(1);
    display.print(F("Scored: "));
    display.println(score);
    display.display();
    delay(4000);
}
