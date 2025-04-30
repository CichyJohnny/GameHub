#include <Arduino.h>

#include "quiz_data.h"

// Question 1
const char question1[] PROGMEM = "Capital of France?";
const char q1a1[] PROGMEM = "Paris";
const char q1a2[] PROGMEM = "London";
const char q1a3[] PROGMEM = "Berlin";
const char q1a4[] PROGMEM = "Rome";

// Question 2
const char question2[] PROGMEM = "2 + 2 = ?";
const char q2a1[] PROGMEM = "3";
const char q2a2[] PROGMEM = "4";
const char q2a3[] PROGMEM = "5";
const char q2a4[] PROGMEM = "6";

// Question 3
const char question3[] PROGMEM = "Boiling point of water?";
const char q3a1[] PROGMEM = "100C";
const char q3a2[] PROGMEM = "90C";
const char q3a3[] PROGMEM = "80C";
const char q3a4[] PROGMEM = "120C";

// Question 4
const char question4[] PROGMEM = "Who painted Mona Lisa?";
const char q4a1[] PROGMEM = "Van Gogh";
const char q4a2[] PROGMEM = "Da Vinci";
const char q4a3[] PROGMEM = "Picasso";
const char q4a4[] PROGMEM = "Michelangelo";

// Question 5
const char question5[] PROGMEM = "Largest planet?";
const char q5a1[] PROGMEM = "Mars";
const char q5a2[] PROGMEM = "Saturn";
const char q5a3[] PROGMEM = "Jupiter";
const char q5a4[] PROGMEM = "Earth";

// Question 6
const char question6[] PROGMEM = "Speed of light (km/s)?";
const char q6a1[] PROGMEM = "300000";
const char q6a2[] PROGMEM = "150000";
const char q6a3[] PROGMEM = "100000";
const char q6a4[] PROGMEM = "250000";

// Question 7
const char question7[] PROGMEM = "Author of 1984?";
const char q7a1[] PROGMEM = "Orwell";
const char q7a2[] PROGMEM = "Tolkien";
const char q7a3[] PROGMEM = "Huxley";
const char q7a4[] PROGMEM = "Hemingway";

// Question 8
const char question8[] PROGMEM = "Binary of 5?";
const char q8a1[] PROGMEM = "101";
const char q8a2[] PROGMEM = "110";
const char q8a3[] PROGMEM = "111";
const char q8a4[] PROGMEM = "100";

// Question 9
const char question9[] PROGMEM = "Atomic no. of Oxygen?";
const char q9a1[] PROGMEM = "6";
const char q9a2[] PROGMEM = "8";
const char q9a3[] PROGMEM = "10";
const char q9a4[] PROGMEM = "12";

// Question 10
const char question10[] PROGMEM = "Mount Everest is in?";
const char q10a1[] PROGMEM = "India";
const char q10a2[] PROGMEM = "China";
const char q10a3[] PROGMEM = "Nepal";
const char q10a4[] PROGMEM = "Bhutan";

// Define the quiz array
const Question quiz[] PROGMEM = {
    { question1, { q1a1, q1a2, q1a3, q1a4 }, 0 },
    { question2, { q2a1, q2a2, q2a3, q2a4 }, 1 },
    { question3, { q3a1, q3a2, q3a3, q3a4 }, 0 },
    { question4, { q4a1, q4a2, q4a3, q4a4 }, 1 },
    { question5, { q5a1, q5a2, q5a3, q5a4 }, 2 },
    { question6, { q6a1, q6a2, q6a3, q6a4 }, 0 },
    { question7, { q7a1, q7a2, q7a3, q7a4 }, 0 },
    { question8, { q8a1, q8a2, q8a3, q8a4 }, 0 },
    { question9, { q9a1, q9a2, q9a3, q9a4 }, 1 },
    { question10, { q10a1, q10a2, q10a3, q10a4 }, 2 }
};


const uint8_t NUM_QUESTIONS = sizeof(quiz) / sizeof(quiz[0]);
