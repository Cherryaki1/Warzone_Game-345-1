# include <iostream>
# include "GameEngine.h"
#include "PlayerStrategies.h"
using namespace std;

void testPlayerStrategies(){
    // WELCOME MESSAGE
    cout << "**** Thank you for playing our CLI Warzone! ****" << endl;
    cout<<"****** Testing Player Strategies *****"<<endl;

    GameEngine engine;

    cout << "Select 1 to test tournament mode and 2 to test player strategies (play the game)" << endl;
    string choice =  engine.getCommandProcessor()->getCommand()->getCommandText();
    int mode = stoi(choice);
    int maps, gamesPerMap, rounds;
    switch(mode){
        case 1:
            cout << "Enter the tournament string. Example: -M test.txt,europe 4b.map -P aggressive neutral -G 2 -D 30" << endl;
            choice = engine.getCommandProcessor()->getCommand()->getCommandText();
            engine.getCommandProcessor()->parseTournamentCommand(choice);

            maps = stoi(engine.getCommandProcessor()->getCommand()->getCommandText());
            gamesPerMap = stoi(engine.getCommandProcessor()->getCommand()->getCommandText());
            rounds = stoi(engine.getCommandProcessor()->getCommand()->getCommandText());
            break;
        case 2:
            cout << "How many maps would you like to play with?" << endl;
            choice =  engine.getCommandProcessor()->getCommand()->getCommandText();
             maps = stoi(choice);

            cout << "How many times would you like to play with each map?" << endl;
            choice =  engine.getCommandProcessor()->getCommand()->getCommandText();
             gamesPerMap = stoi(choice);

            cout << "How many rounds should each game last?" << endl;
            choice =  engine.getCommandProcessor()->getCommand()->getCommandText();
             rounds = stoi(choice);

            break;
    }

    for (int j = 0; j < maps*gamesPerMap; j++){
        cout << "***********GAME " << (j+1) <<"***********"<< endl;
        engine.clear();
        engine.startUpPhase();
        for(int i = 0; i < rounds; i++){
            cout << "\n****ROUND " << (i+1) <<"****" <<endl;
            engine.reinforcementPhase();
            engine.ordersIssuingPhase2();
            if (engine.ordersExecutionPhase() || i == rounds-1){
                engine.endPhase();
                i = rounds;
            }
        }
    }






}

