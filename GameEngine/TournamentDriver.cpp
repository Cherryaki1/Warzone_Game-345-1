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

    string tournamentCommand = "tournament -M test.txt,europe 4b.map -P aggressive neutral benevolant -G 2 -D 30";

    GameEngine engine;

    engine.getCommandProcessor()->parseTournamentCommand(tournamentCommand);

    // Pass the command string to setTournamentParameters
    cout << "Setting tournament parameters..." << endl;
    engine.setTournamentParameters(engine.getCommandProcessor());

    // Run the tournament
    cout << "Running the tournament..." << endl;
    engine.runTournament();

    cout << "***** Tournament Mode Test Complete *****" << endl;

}
