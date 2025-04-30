#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SH110X.h>
#include "memory_game.h"

#define i2c_Address 0x3c
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Buttons: 0 = LEFT, 1 = RIGHT, 2 = SELECT, others unused for now
const int ledPins[6] = {2, 4, 6, 8, 10, 12};
const int buttonPins[6] = {3, 5, 7, 9, 11, 13};

// === Game System ===
const int NUM_GAMES = 3;
const char* games[NUM_GAMES] = {"Memory", "Snake", "Tetris"};

int selectedGame = 0;
bool inMenu = true;

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

  delay(1000);  // simulate load

  if (index == 0) {
    memoryGame(buttonPins, ledPins, display);
    inMenu = true;
    showMenu();
  }
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
      digitalWrite(ledPins[2], HIGH);  // turn on select LED
      startGame(selectedGame);
      delay(500);  // debounce
    }
  } else {
    // Placeholder for game logic
    display.clearDisplay();
    display.setCursor(10, 20);
    display.println("Game running...");
    display.setCursor(10, 40);
    display.println("BTN3 to exit");
    display.display();

    // Button 3 to go back to menu
    if (!digitalRead(buttonPins[3])) {
      inMenu = true;
      showMenu();
      delay(500);  // debounce
    }
  }
}

