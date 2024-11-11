// Arturo Sanchez Escobar (40283236), Team 36
// COMP 345 - D (Advanced Program Design, C++)
// Warzone Game Team Project - Assignment 1
// October 4, 2024
// *******************************************
// This is a cpp file for Part 5 of the assignment.
// It contains the logic the Game Engine follows, to move from one state to another, loop and end

# include <iostream>
# include "GameEngine.h"
using namespace std;


void testGameStates() {
    GameEngine gameEngine;
    if(gameEngine.testStartUpPhase() == true) {
        cout << "Game Engine StartUpPhase Completed, proceeding to Reinforcement Phase" << std::endl;
        if(gameEngine.reinforcementPhase() == true) {
            cout << "Reinforcement Phase Completed, proceeding to Orders Execution" << endl;
            if(gameEngine.ordersIssuingPhase() == true) {
                cout << "Orders Issuing Phase Completed, proceeding to Orders Execution" << endl;
                if(gameEngine.ordersExecutionPhase() == "endexecorders") {
                    cout << "Orders Execution Phase Completed, checking End Phase" << endl;
                    testGameStates();
                }else {
                    if(gameEngine.endPhase() == true) {
                        cout << "Congratulations, a player has won!" << endl;
                        cout << "Thank you for playing!" << endl;
                    }else {
                        cout << "The win conditions have not been met yet!" << endl;
                        testGameStates();
                    }

                }
            }
        }
    }
}