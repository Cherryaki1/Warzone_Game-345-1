// Arturo Sanchez Escobar (40283236), Team 36
// COMP 345 - D (Advanced Program Design, C++)
// Warzone Game Team Project - Assignment 1
// October 4, 2024
// *******************************************
// This is a cpp file for Part 5 of the assignment.
// It contains the class and function implementations for the Game Engine composed of two objects, StartUp and Play

#include <iostream>
#include "GameEngine.h"

#include <MapDriver.h>

#include "MapLoader.h"
#include "Map.h"

using namespace std;

// GAMEENGINE CONSTRUCTOR
GameEngine::GameEngine() {
    state = new string("StartUp");
    invalidCommand = new bool(false); // Dynamically Allocate Memory
    command = nullptr; // To avoid dereferencing issues
}

GameEngine::~GameEngine() {
    if (invalidCommand != nullptr) {
        delete invalidCommand;  // Free the allocated memory of new
    }
    if(command != nullptr) {
        delete command; // Free memory for command if it is allocated
    }
    if(state != nullptr) {
        delete state;
    }
}

    // OPERATOR << FOR STARTUP
    ostream& operator<<(ostream& out, const GameEngine& gameEngine) {
        out << "StartUp State: \n";
        out << "Command: " << (gameEngine.command ? *gameEngine.command : "None") << "\n";
        out << "Invalid Command: " << (*gameEngine.invalidCommand ? "true" : "false") << "\n";
        return out;
    }

// AT THE END OF EACH METHOD, CHECK IF THE COMMAND ENTERED TO TRANSITION IS VALID, ELSE ERROR MSG
bool GameEngine::testStartUpPhase(string mapFile) {
    cout << "... Starting up Phase ..." << endl;

    // Call Loadmap
    Map& loadedNap = loadMap(mapFile);

    /*
    // Allocate memory for `command` before using it
    if(command == nullptr) {
        command = new string("");  // Allocate memory for command
    }

    setInvalidCommand(false);
    while(!getInvalidCommand()){
        cout << "Type \"loadmap\" to transition to the next state"<< endl;
        cin >> *command;
        if(getCommand() == "loadmap") {
            // Call loadmap
            setInvalidCommand(true);
        }else {
            cerr << "Invalid command!" << endl;
        }
    }
    setInvalidCommand(false);
    while(!getInvalidCommand()) {
        cout << "Type \"validatemap\" to transition to the next state" << endl;
        cin >> *command;
        if(getCommand() == "validatemap") {
            // Call validateMap Function

            // validate call function

            setInvalidCommand(true);
        }else {
            cerr << "Invalid command!" << endl;
        }
    }
    setInvalidCommand(false);
    while(!getInvalidCommand()) {
        cout << "Type \"addplayer\" to transition to the next state" << endl;
        cin >> *command;
        if(getCommand() == "addplayer") {
            // Call to addPlayer Function

            // addplayer <playername> inside a function that loops till i-1 players
            // 50 armies for everyplayer
            // Set Random palyer order
            // Each player draws two cards

            setInvalidCommand(true);
        }else {
            cerr << "Invalid command!" << endl;
        }
    }
    setInvalidCommand(false);
    while(!getInvalidCommand()) {
        cout << "Type \"assigncountries\" to transition to the next state" << endl;
        cin >> *command;
        if(getCommand() == "assigncountries") {
            setInvalidCommand(true);
        }else {
            cerr << "Invalid command!" << endl;
        }
    }
    */
    return true;
}

bool GameEngine::reinforcementPhase() {
    cout << "... Reinforcement Phase ..." << endl;
    setInvalidCommand(false);

    if(command == nullptr) {
        command = new string("");  // Allocate memory for command
    }

    // Call to assignCountries Function which assign troops to countries
    while(!getInvalidCommand()) {
        cout << "Type \"issueorder\" to transition to the next state" << endl;
        cin >> *command;
        if(getCommand() == "issueorder") {
            setInvalidCommand(true);
        }else {
            cerr << "Invalid command!" << endl;
        }
    }
    return true;
}


bool GameEngine::ordersIssuingPhase() {
    cout << "... Orders Issuing Phase ..." << endl;
    setInvalidCommand(false);

    if(command == nullptr) {
        command = new string("");  // Allocate memory for command
    }

    // Call to issueOrder Function
    while(!getInvalidCommand()) {
        cout << "Type \"endissueorders\" to transition to the next state" << endl;
        cin >> *command;
        if(getCommand() == "endissueorders") {
            setInvalidCommand(true);
        }else {
            cerr << "Invalid command!" << endl;
        }
    }
    return true;
}

string GameEngine::ordersExecutionPhase() {
    cout << "... Orders Execution Phase ..." << endl;
    setInvalidCommand(false);

    if(command == nullptr) {
        command = new string("");  // Allocate memory for command
    }

    // Call to executeOrders Function
    while(!getInvalidCommand()) {
        cout << "Type \"endexecorders\" to keep playing or \"win\" to end the game" << endl;
        cin >> *command;
        if(getCommand() == "endexecorders" || getCommand() == "win") {
            setInvalidCommand(true);
        }else {
            cerr << "Invalid command!" << endl;
        }
    }
    return getCommand();
}


bool GameEngine::endPhase() {
    cout << "... End Phase ..." << endl;
    // Validate win
    return true;
}

// SETTERS AND GETTERS FOR PLAY
string GameEngine::getCommand() const {
    if(command == nullptr) {
        return ""; // Return empty string if command is initialized
    }
    return *command; // Dereference and return the actual value
}
void GameEngine::setCommand(const string& cmd) {
    if(command == nullptr) {
        command = new string(cmd); // Allocate memory and set command if it is initialized
    }else {
        *command = cmd; // Assign new value if already allocated
    }
}
bool GameEngine::getInvalidCommand() const {
    return *invalidCommand;     // Dereference and get value
}
void GameEngine::setInvalidCommand(bool value){
    *invalidCommand = value;        // Dereference and assign new value
}

