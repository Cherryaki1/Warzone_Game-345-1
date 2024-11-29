# include <iostream>
# include "GameEngine.h"
#include "PlayerStrategies.h"
using namespace std;

void testPlayerStrategies(){
    // WELCOME MESSAGE
    cout << "**** Thank you for playing our CLI Warzone! ****" << endl;
    cout<<"****** Testing Player Strategies *****"<<endl;

    GameEngine engine;
    engine.startUpPhase();
    engine.reinforcementPhase();
    engine.ordersIssuingPhase2();
    engine.ordersExecutionPhase();
}

