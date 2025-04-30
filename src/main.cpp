#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SH110X.h>

#include "util.h"
#include "globals.h"

#include "memory_game.h"
#include "whack_game.h"


// === Helpers ===
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
            memoryGame(buttonPins, ledPins, display);
            break;
        case 1:
            whackGame(buttonPins, ledPins, display);
            break;
        default:
            break;
    }

    inMenu = true;
    showMenu();
}

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

