// Arturo Sanchez Escobar (40283236), Team 36
// COMP 345 - D (Advanced Program Design, C++)
// Warzone Game Team Project - Assignment 1
// October 4, 2024
// *******************************************
// This is a cpp file for Part 5 of the assignment.
// It contains the class and function declarations for the Game Engine header composed of two objects, StartUp and Play and a free function

#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <string>
#include <iostream>
using std::string;
using std::ostream;

class GameEngine {
    private:
    string* state; // Keeps track of current state
    string* command;
    bool* invalidCommand;

    public:
    GameEngine();
    ~GameEngine(); // Destructor

    // PHASES
    bool testStartUpPhase();
    bool reinforcementPhase();
    bool ordersIssuingPhase();
    string ordersExecutionPhase();
    bool endPhase();

    // SETTERS AND GETTERS FOR PLAY
    string getCommand() const;
    void setCommand(const string& cmd);
    bool getInvalidCommand()const;
    void setInvalidCommand(bool value);

    // Stream insertion operator
    friend ostream& operator<<(ostream& out, const GameEngine& gameEngine);
};

void testGameStates();
#endif

