# include <iostream>
# include "GameEngine.h"
using namespace std;

void testGameStates() {
    if(StartUp::startUpPhase() == true) {
        cout << "Game Engine StartUpPhase Called, proceeding to Reinforcement Phase" << std::endl;
        if(Play::reinforcementPhase() == true) {
            cout << "Reinforcement Phase Called, proceeding to Orders Execution" << endl;
            if(Play::ordersExecutionPhase() == true) {
                cout << "Orders Execution Phase Called, proceeding to End Phase" << endl;
                if(Play::endPhase() == true) {
                    cout << "End Phase Called, Game is over" << endl;
                }else {
                    testGameStates();
                }
            }
        }
    }
}