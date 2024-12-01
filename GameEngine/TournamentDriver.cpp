//
// Created by abdul on 2024-12-01.
//

//#include "TournamentDriver.h"

# include "GameEngine.h"
#include "PlayerStrategies/PlayerStrategies.h"
#include "Commands/CommandProcessing.h"

using namespace std;

void testTournament() {

    cout << "**** Thank you for playing our CLI Warzone! ****" << endl;
    cout<<"****** Testing Tournament Mode *****"<<endl;

    GameEngine engine;

    // Simulated command string for tournament mode
    string tournamentCommand = "tournament -M Map1,Map2,Map3 -P Aggressive,Benevolent,Neutral,Cheater -G 3 -D 20";

    // Pass the command string to setTournamentParameters
    cout << "Setting tournament parameters..." << endl;
    engine.setTournamentParameters(tournamentCommand);

    // Run the tournament
    cout << "Running the tournament..." << endl;
    engine.runTournament();

    cout << "***** Tournament Mode Test Complete *****" << endl;

}
