#include <Arduino.h>
#include "memory_game.h"

const uint8_t MAX_BUTTONS = 3;
const uint8_t MAX_SEQUENCE = 32;
uint8_t sequence[MAX_SEQUENCE];

void generateSequence(uint8_t length) {
  for (uint8_t i = 0; i < length; i++) {
    sequence[i] = random(0, MAX_BUTTONS);
  }
}

void playSequence(const int ledPins[], uint8_t length) {
  for (uint8_t i = 0; i < length; i++) {
    int index = sequence[i];

    digitalWrite(ledPins[index], LOW);
    delay(400);
    digitalWrite(ledPins[index], HIGH);
    delay(200);
  }
}

bool getPlayerInput(const int buttonPins[], const int ledPins[], uint8_t length) {
  for (uint8_t i = 0; i < length; i++) {
    bool pressed = false;
    unsigned long start = millis();

    while (!pressed && millis() - start < 10000) {  // 10s timeout
      for (uint8_t j = 0; j < MAX_BUTTONS; j++) {
        if (!digitalRead(buttonPins[j])) {
          digitalWrite(ledPins[j], LOW);
          delay(300);
          digitalWrite(ledPins[j], HIGH);

          if (j != sequence[i]) return false;

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

void memoryGame(const int buttonPins[], const int ledPins[], Adafruit_SH1106G& display) {
  uint8_t currentLength = 1;
  generateSequence(MAX_SEQUENCE);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Memory Game");
  display.println("Repeat LED sequence");
  display.display();
  delay(1500);

  while (currentLength < MAX_SEQUENCE) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.print("Round: ");
    display.println(currentLength);
    display.display();

    delay(1000);
    playSequence(ledPins, currentLength);

    if (!getPlayerInput(buttonPins, ledPins, currentLength)) {
      display.clearDisplay();
      display.setCursor(0, 20);
      display.setTextSize(2);
      display.println("Game Over!");
      display.setCursor(0, 40);
      display.setTextSize(1);
      display.print("Scored: ");
      display.println(currentLength - 1);
      display.display();
      delay(4000);
      
      break;
    }

    currentLength++;
    delay(800);
  }
}
