#include <iostream>
#include "GameEngine.h"

using namespace std;

// STARTUP CONSTRUCTOR
StartUp::StartUp() {
    invalidCommand = new bool(false); // Dynamically Allocate Memory
    command = nullptr; // To avoid dereferencing issues
}

// PLAY CONSTRUCTOR
Play::Play() {
    invalidCommand = new bool(false); // Dynamically Allocate Memory
    command = nullptr; // To avoid dereferencing issues
}

// DESTRUCTORS TO FREE ALLOCATED MEMORY
StartUp::~StartUp() {
    if (invalidCommand != nullptr) {
        delete invalidCommand;  // Free the allocated memory of new
    }
    if(command != nullptr) {
        delete command; // Free memory for command if it is allocated
    }
}

Play::~Play() {
    if (invalidCommand != nullptr) {
        delete invalidCommand;  // Free the allocated memory of new
    }
    if(command != nullptr) {
        delete command; // Free memory for command if it is allocated
    }
}


// AT THE END OF EACH METHOD, CHECK IF THE COMMAND ENTERED TO TRANSITION IS VALID, ELSE ERROR MSG
bool StartUp::startUpPhase() {
    cout << "... Starting up Phase ..." << endl;

    // Allocate memory for `command` before using it
    if(command == nullptr) {
        command = new string("");  // Allocate memory for command
    }

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

bool Play::ordersIssuingPhase() {
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

string Play::ordersExecutionPhase() {
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


bool Play::endPhase() {
    cout << "... End Phase ..." << endl;
    // Validate win
    return true;
}

// SETTERS AND GETTERS FOR STARTUP
string StartUp::getCommand() const {
    if(command == nullptr) {
        return ""; // Return empty string if command is initialized
    }
    return *command; // Dereference and return the actual value
}
void StartUp::setCommand(const string& cmd) {
    if(command == nullptr) {
        command = new string(cmd); // Allocate memory and set command if it is initialized
    }else {
        *command = cmd; // Assign new value if already allocated
    }
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

