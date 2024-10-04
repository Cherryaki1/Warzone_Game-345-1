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
using std::string;



class StartUp {
    private:
    string* command;
    bool* invalidCommand;
    public:
    StartUp();
    ~StartUp(); // Destructor

    // PHASE
    bool startUpPhase();

    // SETTERS ANG GETTERS FOR STARTUP
    string getCommand() const;
    void setCommand(const string& cmd);
    bool getInvalidCommand()const;
    void setInvalidCommand(bool value);
};

class Play {
    private:
    string* command;
    bool* invalidCommand;
    public:
    Play();
    ~Play(); // Destructor

    // PHASES
    bool reinforcementPhase();
    bool ordersIssuingPhase();
    string ordersExecutionPhase();
    bool endPhase();

    // SETTERS AND GETTERS FOR PLAY
    string getCommand() const;
    void setCommand(const string& cmd);
    bool getInvalidCommand()const;
    void setInvalidCommand(bool value);
};

void testGameStates();
#endif

