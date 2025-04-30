#ifndef QUIZ_DATA_H
#define QUIZ_DATA_H

#include <Arduino.h>

struct Question {
    const char* question;
    const char* answers[4];
    uint8_t correctIndex;
};

extern const Question quiz[] PROGMEM;
extern const uint8_t NUM_QUESTIONS;

#endif