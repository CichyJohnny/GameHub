#include <Arduino.h>

#include "util.h"

void turnOffAllLeds(const int ledPins[], int numLeds) {
    for (int i = 0; i < numLeds; i++) {
        digitalWrite(ledPins[i], LOW); // Turn off LED
    }
}