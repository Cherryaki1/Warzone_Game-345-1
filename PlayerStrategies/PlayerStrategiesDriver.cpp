# include <iostream>
# include "GameEngine.h"
#include "PlayerStrategies.h"
using namespace std;

void testPlayerStrategies(){
    // WELCOME MESSAGE
    cout << "**** Thank you for playing our CLI Warzone! ****" << endl;
    cout<<"****** Testing Player Strategies *****"<<endl;

    GameEngine engine;

    cout << "How many maps would you like to play with?" << endl;
    string choice =  engine.getCommandProcessor()->getCommand()->getCommandText();
    int maps = stoi(choice);

    cout << "How many rounds should each game last?" << endl;
    choice =  engine.getCommandProcessor()->getCommand()->getCommandText();
    int rounds = stoi(choice);

    for (int j = 0; j < maps; j++){
        cout << "***********MAP " << (j+1) <<"***********"<< endl;
        engine.startUpPhase();
        for(int i = 0; i < rounds; i++){
            cout << "****ROUND " << (i+1) <<"****" <<endl;
            engine.reinforcementPhase();
            engine.ordersIssuingPhase2();
            if (engine.ordersExecutionPhase() || i == rounds-1){
                engine.endPhase();
                i = rounds;
            }
        }
    }





}

