#include <Arduino.h>
#include "util.h"
#include "globals.h"


void setup() {
    for (int i = 0; i < 6; i++) {
        pinMode(ledPins[i], OUTPUT);
        pinMode(buttonPins[i], INPUT_PULLUP);
    }

    Serial.begin(9600);
    delay(250);

    display.begin(i2c_Address, true);
    display.display();
    delay(500);

    display.clearDisplay();

    showMenu();
}

void loop() {
    // Read buttons
    bool left = !digitalRead(buttonPins[0]);
    bool right = !digitalRead(buttonPins[1]);
    bool select = !digitalRead(buttonPins[2]);

    // LED feedback
    digitalWrite(ledPins[0], left ? LOW : HIGH);
    digitalWrite(ledPins[1], right ? LOW : HIGH);
    digitalWrite(ledPins[2], select ? LOW : HIGH);

    if (inMenu) {
        if (left) {
            selectedGame = (selectedGame - 1 + NUM_GAMES) % NUM_GAMES;
            showMenu();
            delay(200);  // debounce
        }
        if (right) {
            selectedGame = (selectedGame + 1) % NUM_GAMES;
            showMenu();
            delay(200);  // debounce
        }
        if (select) {
            inMenu = false;
            startGame(selectedGame);
            delay(500);  // debounce
        }
    }
}

