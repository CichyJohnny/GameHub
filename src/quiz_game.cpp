#include <Arduino.h>
#include "globals.h"
#include "quiz_data.h"

#include "quiz_game.h"

// Function to read a question from program memory
void getQuestionFromProgmem(uint8_t index, Question& questionBuffer) {
    // Copy the entire question struct from program memory
    memcpy_P(&questionBuffer, &quiz[index], sizeof(Question));
}

void showQuestion(uint8_t index) {
    Question q;
    getQuestionFromProgmem(index, q);
    
    // Buffer for storing strings read from program memory
    char buffer[64];
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    
    // Read question text from program memory
    strcpy_P(buffer, (PGM_P)q.question);
    display.println(buffer);
    
    // Show each answer
    for (int i = 0; i < 4; i++) {
        display.print(i);
        display.print(F(": "));
        strcpy_P(buffer, (PGM_P)q.answers[i]);
        display.println(buffer);
    }
    display.display();
}

int waitForAnswer() {
    while (true) {
        for (int i = 0; i < 4; i++) {
            if (!digitalRead(buttonPins[i])) {
                digitalWrite(ledPins[i], HIGH);
                delay(300);
                digitalWrite(ledPins[i], LOW);
                return i;
            }
        }
        delay(50);
    }
}

void showResult(bool correct) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(10, 20);
    if (correct) {
        display.println(F("Correct!"));
    } else {
        display.println(F("Wrong!"));
    }
    display.display();
    delay(1500);
}

#include <Arduino.h>
#include "globals.h"
#include "quiz_data.h"
#include "quiz_game.h"

// Fisher-Yates shuffle
void shuffleArray(uint8_t* array, uint8_t size) {
    for (uint8_t i = size - 1; i > 0; i--) {
        uint8_t j = random(i + 1);
        uint8_t temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void quizGame() {
    uint8_t score = 0;

    // Create and shuffle index array
    uint8_t indices[NUM_QUESTIONS];
    for (uint8_t i = 0; i < NUM_QUESTIONS; i++) {
        indices[i] = i;
    }
    shuffleArray(indices, NUM_QUESTIONS);

    delay(500);

    for (uint8_t i = 0; i < NUM_QUESTIONS; i++) {
        uint8_t qIndex = indices[i];
        showQuestion(qIndex);
        int answer = waitForAnswer();
        
        // Get correct answer
        Question q;
        getQuestionFromProgmem(qIndex, q);
        bool correct = (answer == q.correctIndex);
        
        if (correct) {
            score++;
        }

        showResult(correct);
    }

    // Final score display
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 20);
    display.println(F("Quiz Finished!"));
    display.print(F("Score: "));
    display.print(score);
    display.print(F("/"));
    display.println(NUM_QUESTIONS);
    display.display();
    delay(3000);
}
