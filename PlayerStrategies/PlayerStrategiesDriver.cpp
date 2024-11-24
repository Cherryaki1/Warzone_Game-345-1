# include <iostream>
# include "GameEngine.h"
#include "PlayerStrategies.h"
using namespace std;

void testPlayerStrategies(){
    cout<<"****** Testing Player Strategies *****"<<endl;

    GameEngine engine;
    engine.startUpPhase();
    engine.reinforcementPhase();
    engine.ordersIssuingPhase2();
}

