# include <iostream>
# include "GameEngine.h"
#include "PlayerStrategies.h"
using namespace std;

void testPlayerStrategies(){
    // WELCOME MESSAGE
    cout<<"****** Testing Player Strategies *****"<<endl;

    GameEngine engine;

    int maps, gamesPerMap, rounds;

    cout << "How many maps would you like to play with?" << endl;
    string choice =  engine.getCommandProcessor()->getCommand()->getCommandText();
    maps = stoi(choice);

    cout << "How many times would you like to play with each map?" << endl;
    choice =  engine.getCommandProcessor()->getCommand()->getCommandText();
    gamesPerMap = stoi(choice);

    cout << "How many rounds should each game last?" << endl;
    choice =  engine.getCommandProcessor()->getCommand()->getCommandText();
    rounds = stoi(choice);


    for (int j = 0; j < maps*gamesPerMap; j++){
        cout << "***********GAME " << (j+1) <<"***********"<< endl;
        engine.clear();
        engine.startUpPhase();
        for(int i = 0; i < rounds; i++){
            cout << "\n****GAME " << (j+1) << " | ROUND " << (i+1) <<"****" <<endl;
            engine.reinforcementPhase();
            engine.ordersIssuingPhase2();
            if (engine.ordersExecutionPhase() || i == rounds-1){
                engine.endPhase();
                i = rounds;
            }
        }
    }

}

