#include <iostream>
#include "GameEngine.h"

#include <set>
using namespace std;

// STARTUP CONSTRUCTOR
StartUp::StartUp() {
    invalidCommand = new bool(false); // Dynamically Allocate Memory
}

// PLAY CONSTRUCTOR
Play::Play() {
    invalidCommand = new bool(false); // Dynamically Allocate Memory
    command = nullptr; // To avoid dereferencing issues
}

// DESTRUCTORS TO FREE ALLOCATED MEMORY
StartUp::~StartUp() {
    delete invalidCommand;  // Free the allocated memory of new
}

Play::~Play() {
    delete invalidCommand; // Free the allocated memory of new
    if(command != nullptr) {
        delete command; // Free memory for command if it is allocated
    }
}


// AT THE END OF EACH METHOD, CHECK IF THE COMMAND ENTERED TO TRANSITION IS VALID, ELSE ERROR MSG
bool StartUp::startUpPhase() {
    cout << "... Starting up Phase ..." << endl;
    setInvalidCommand(false);
    while(!getInvalidCommand()){
        cout << "Type \"loadmap\" to transition to the next state"<< endl;
        cin >> *command;
        if(getCommand() == "loadmap") {
            // Call loadmap function
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
    return true;
}

bool Play::reinforcementPhase() {
    cout << "... Reinforcement Phase ..." << endl;
    setInvalidCommand(false);
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
    setInvalidCommand(false);
    while(!getInvalidCommand()) {
        cout << "Type \"hi\" to transition to the next state" << endl;
        cin >> *command;
        if(getCommand() == "hi") {
            setInvalidCommand(true);
        }else {
            cerr << "Invalid command!" << endl;
        }
    }
    return true;
}

bool Play::ordersIssuingPhase() {
    cout << "... Orders Issuing Phase ..." << endl;
    setInvalidCommand(false);
    // Call to issueOrder Function
    while(!getInvalidCommand()) {
        cout << "Type \"execorder\" to transition to the next state" << endl;
        cin >> *command;
        if(getCommand() == "execorder") {
            setInvalidCommand(true);
        }else {
            cerr << "Invalid command!" << endl;
        }
    }
    return true;
}

bool Play::ordersExecutionPhase() {
    cout << "... Orders Execution Phase ..." << endl;
    setInvalidCommand(false);
    // Call to executeOrders Function
    while(!getInvalidCommand()) {
        cout << "Type \"endexecorders\" to keep playing or \"win\" to end the game" << endl;
        cin >> *command;
        if(getCommand() == "execorder") {
            setInvalidCommand(true);
        }
        if(getCommand() == "win"){
            if(endPhase() == true) {
                cout << "Congratulations, a player has won!" << endl;
                cout << "Thank you for playing!" << endl;
                setInvalidCommand(true);
            }else {
                //cerr << "The win conditions have not been met yet!" << endl;
            }
        }else {
            cerr << "Invalid command!" << endl;
        }
    }
    return true;
}


bool Play::endPhase() {
    cout << "... End Phase ..." << endl;
    // Validate win
    return true;
}

// SETTERS AND GETTERS FOR STARTUP
string StartUp::getCommand() const {
    return *command;        // Dereference and get value
}
void StartUp::setCommand(string* value) {
    command = value;        // Assign new value
}
bool StartUp::getInvalidCommand() const {
    return *invalidCommand;     // Dereference and get value
}
void StartUp::setInvalidCommand(bool value){
    *invalidCommand = value;        // Dereference and assign new value
}

// SETTERS AND GETTERS FOR PLAY
string Play::getCommand() const {
    if(command == nullptr) {
        return ""; // Return empty string if command is initialized
    }
    return *command; // Dereference and return the actual value
}
void Play::setCommand(const string& cmd) {
    if(command == nullptr) {
        command = new string(cmd); // Allocate memory and set command if it is initialized
    }else {
        *command = cmd; // Assign new value if already allocated
    }
}
bool Play::getInvalidCommand() const {
    return *invalidCommand;     // Dereference and get value
}
void Play::setInvalidCommand(bool value){
    *invalidCommand = value;        // Dereference and assign new value
}

