#include <Arduino.h>
#include "globals.h"
#include "duel_game.h"

#define MAX_PLAYERS 3
#define ROUNDS 5

void duelGame() {
    // Variables to track game state
    int numPlayers = 0;
    int playerScores[MAX_PLAYERS] = {0};
    unsigned long totalReactionTimes[MAX_PLAYERS] = {0};
    int validRounds[MAX_PLAYERS] = {0};
    int currentRound = 1;
    
    // Player selection phase
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println(F("Reaction Time Game"));
    display.println(F("Select # of players:"));
    display.println(F("Press 1-3 buttons"));
    display.display();

    delay(500);
    
    // Wait for player selection (buttons 1-3)
    while (numPlayers == 0) {
        for (int i = 0; i < 3; i++) {
            if (!digitalRead(buttonPins[i])) {
                numPlayers = i + 1;
                digitalWrite(ledPins[i], HIGH);
                delay(300);
                digitalWrite(ledPins[i], LOW);
                break;
            }
        }
    }
    
    // Show selected player count
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(F("Players: "));
    display.println(numPlayers);
    display.println(F("Get ready!"));
    display.println(F("Wait for LEDs..."));
    display.display();
    delay(2000);
    
    // Main game loop for rounds
    while (currentRound <= ROUNDS) {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print(F("Round: "));
        display.println(currentRound);
        display.println(F("Wait for LEDs..."));
        display.display();
        
        // Random wait time before LEDs turn on
        delay(random(1000, 5000));
        
        // Turn on all LEDs for player count
        for (int i = 0; i < numPlayers; i++) {
            digitalWrite(ledPins[i], HIGH);
        }
        
        // Timestamp when LEDs were turned on
        unsigned long startTime = millis();
        bool roundCompleted = false;
        int winningPlayer = -1;
        
        // Wait for player input
        while (!roundCompleted) {
            for (int i = 0; i < numPlayers; i++) {
                if (!digitalRead(buttonPins[i])) {
                    // Player i pressed their button
                    unsigned long endTime = millis();
                    unsigned long reactionTime = endTime - startTime;
                    
                    // Record reaction time
                    totalReactionTimes[i] += reactionTime;
                    validRounds[i]++;
                    playerScores[i]++;
                    winningPlayer = i;
                    roundCompleted = true;
                    break;
                }
            }
        
            // Timeout after 2 seconds if no one presses
            if (millis() - startTime > 2000 && !roundCompleted) {
                roundCompleted = true;
            }
        }
        
        // Turn off all LEDs
        for (int i = 0; i < numPlayers; i++) {
            digitalWrite(ledPins[i], LOW);
        }
        
        // Show round results
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print(F("Round "));
        display.print(currentRound);
        display.println(F(" complete!"));
        
        if (winningPlayer >= 0) {
            display.print(F("Player "));
            display.print(winningPlayer + 1);
            display.println(F(" wins!"));
            display.print(F("Reaction: "));
            display.print(totalReactionTimes[winningPlayer] / validRounds[winningPlayer]);
            display.println(F("ms"));
        } else {
            display.println(F("No one reacted!"));
        }
        display.display();
        delay(2000);
        
        currentRound++;
    }
    
    // Calculate and display final results
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(F("Final Results:"));
    
    // Find winner (most rounds won)
    int maxScore = 0;
    int winner = -1;
    
    for (int i = 0; i < numPlayers; i++) {
        if (playerScores[i] > maxScore) {
        maxScore = playerScores[i];
        winner = i;
        }
    }
    
    // Display winner info
    if (winner >= 0) {
        display.print(F("Winner: Player "));
        display.println(winner + 1);
        display.print(F("Rounds won: "));
        display.println(playerScores[winner]);
        
        if (validRounds[winner] > 0) {
            display.print(F("Avg time: "));
            display.print(totalReactionTimes[winner] / validRounds[winner]);
            display.println(F("ms"));
        }
    } else {
        display.println(F("No winner!"));
    }
    
    // Show all player stats
    display.println("--------------");
    for (int i = 0; i < numPlayers; i++) {
        if (validRounds[i] > 0) {
        display.print(F("P"));
        display.print(i + 1);
        display.print(F(": "));
        display.print(totalReactionTimes[i] / validRounds[i]);
        display.println(F("ms"));
        }
    }
    
    display.display();
    delay(5000);  // Show results for 5 seconds
}