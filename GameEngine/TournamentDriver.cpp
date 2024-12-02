# include <iostream>
# include "GameEngine.h"
#include "PlayerStrategies/PlayerStrategies.h"
using namespace std;

void testTournament(){
    // WELCOME MESSAGE
    std::ofstream file; //Clear the game log file
    file.open("../gamelog.txt", std::ios::trunc);
    file.flush();
    file.close();


    cout<<"****** Testing Tournament Mode *****"<<endl;

    GameEngine engine;

    int maps, gamesPerMap, rounds;

    cout << "Enter the tournament string. Example: -M test.txt,europe 4b.map -P aggressive neutral -G 2 -D 30" << endl;
    string choice = engine.getCommandProcessor()->getCommand()->getCommandText();
    engine.getCommandProcessor()->parseTournamentCommand(choice);

    maps = stoi(engine.getCommandProcessor()->getCommand()->getCommandText());
    gamesPerMap = stoi(engine.getCommandProcessor()->getCommand()->getCommandText());
    rounds = stoi(engine.getCommandProcessor()->getCommand()->getCommandText());

    for (int j = 0; j < maps; j++){
        for(int k =0; k<gamesPerMap; k++){
            string winInfo = "";
            cout << "***********GAME " << (j+1) <<"***********"<< endl;
            engine.clear();
            engine.startUpPhase();
            for(int i = 0; i < rounds; i++){
                cout << "\n****GAME " << (j+1) << " | ROUND " << (i+1) <<"****" <<endl;
                engine.reinforcementPhase();
                engine.ordersIssuingPhase2();
                if (engine.ordersExecutionPhase() || i == rounds-1){
                    winInfo = engine.endPhase();
                    i = rounds;
                }
            }
            engine.logTournament(winInfo, k+1, j+1);
            cout << "\033[31m" <<"Tournament results have been logged in gamelog.txt." << "\033[0m" <<endl;
        }
    }

}