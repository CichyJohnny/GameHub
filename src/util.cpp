#include <Arduino.h>

#include "util.h"

void turnOffAllLeds(const uint8_t ledPins[], uint8_t numLeds) {
    for (uint8_t i = 0; i < numLeds; i++) {
        digitalWrite(ledPins[i], LOW); // Turn off LED
    }
}