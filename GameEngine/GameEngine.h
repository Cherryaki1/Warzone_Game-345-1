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
#include <vector>
#include "Commands/CommandProcessing.h"
#include "LogObserver/LoggingObserver.h"
#include "Player.h"
#include "Cards.h"

using std::string;
using std::ostream;

class GameEngine : public Subject, public ILoggable {
    private:
    string* state; // Keeps track of current state
    string* command;
    bool* invalidCommand;
    vector<Player*> players;
    Deck* deck;
    Map* gameMap;
    CommandProcessor *processor;

    public:
    GameEngine();
    ~GameEngine(); // Destructor

    void mainGameLoop();

    // PHASES
    void startUpPhase();
    bool startUpPhase2(string mapFile);
    bool reinforcementPhase();
    bool ordersIssuingPhase();
    void ordersIssuingPhase2();
    string ordersExecutionPhase();
    bool endPhase();

    // SETTERS AND GETTERS FOR PLAY
    string getState() const;
    string getCommand() const;
    void setCommand(const string& cmd);
    bool getInvalidCommand()const;
    void setInvalidCommand(bool value);
    void addPlayer(Player *player);
    void transition(string newState);
    string stringToLog() override;


    // Stream insertion operator
    friend ostream& operator<<(ostream& out, const GameEngine& gameEngine);

};

void testGameStates();
void testStartUpPhase();
void testMainGameLoop();
void testOrderExecution();
void definePlayerStrategy(Player *player);

#endif

