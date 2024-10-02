#include <iostream>
#include "GameEngine.h"
using namespace std;

// AT THE END OF EACH METHOD, CHECK IF THE COMMAND ENTERED TO TRANSITION IS VALID, ELSE ERROR MSG
bool StartUp::startUpPhase() {
    cout << "Starting up Phase ..." << endl;
    return true; // True if phase is done
}

bool Play::reinforcementPhase() {
    cout << "Reinforcement Phase ..." << endl;
    return true;
}

bool Play::ordersExecutionPhase() {
    cout << "Orders Execution Phase ..." << endl;
    return true;
}

bool Play::ordersIssuingPhase() {
    cout << "Orders Issuing Phase ..." << endl;
    return true;
}

bool Play::endPhase() {
    cout << "End Phase ..." << endl;
    return true;
}



