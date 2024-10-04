# include <iostream>
# include "GameEngine.h"
using namespace std;


void testGameStates() {
    StartUp start;
    Play play;
    if(start.startUpPhase() == true) {
        cout << "Game Engine StartUpPhase Completed, proceeding to Reinforcement Phase" << std::endl;
        if(play.reinforcementPhase() == true) {
            cout << "Reinforcement Phase Completed, proceeding to Orders Execution" << endl;
            if(play.ordersIssuingPhase() == true) {
                cout << "Orders Issuing Phase Completed, proceeding to Orders Execution" << endl;
                if(play.ordersExecutionPhase() == "endexecorders") {
                    cout << "Orders Execution Phase Completed, checking End Phase" << endl;
                    testGameStates();
                }else {
                    if(play.endPhase() == true) {
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