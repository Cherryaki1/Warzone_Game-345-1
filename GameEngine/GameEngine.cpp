// Arturo Sanchez Escobar (40283236), Team 36
// COMP 345 - D (Advanced Program Design, C++)
// Warzone Game Team Project - Assignment 1
// October 4, 2024
// *******************************************
// This is a cpp file for Part 5 of the assignment.
// It contains the class and function implementations for the Game Engine composed of two objects, StartUp and Play

#include <iostream>
#include <algorithm>
#include <random>
#include "GameEngine.h"
#include <MapDriver.h>
#include "Cards.h"
#include "MapLoader.h"
#include "Map.h"
Map* globalMap = nullptr;
using namespace std;

// GAMEENGINE CONSTRUCTOR
GameEngine::GameEngine() {
    state = new string("StartUp");
    invalidCommand = new bool(false); // Dynamically Allocate Memory
    processor = new CommandProcessor();
    command = nullptr; // To avoid dereferencing issues
    deck = new Deck();
}

GameEngine::~GameEngine() {
    if (invalidCommand != nullptr) {
        delete invalidCommand;  // Free the allocated memory of new
    }
    if(command != nullptr) {
        delete command; // Free memory for command if it is allocated
    }
    if(state != nullptr) {
        delete state;
    }
    for (Player* player : players) {
        delete player;
    }
    delete processor;
    delete deck;
}

    // OPERATOR << FOR STARTUP
    ostream& operator<<(ostream& out, const GameEngine& gameEngine) {
        out << "StartUp State: \n";
        out << "Command: " << (gameEngine.command ? *gameEngine.command : "None") << "\n";
        out << "Invalid Command: " << (*gameEngine.invalidCommand ? "true" : "false") << "\n";
        return out;
    }

// AT THE END OF EACH METHOD, CHECK IF THE COMMAND ENTERED TO TRANSITION IS VALID, ELSE ERROR MSG

void GameEngine::startUpPhase() {
    cout << "... Starting up Phase ..." << endl;
    // Current State
    transition("start");
    Command *currentCommand;
    Map loadedMap;

    do {
        cout << "Please enter loadmap and the filename of the map (separated by space) " <<endl;
        currentCommand = processor->getCommand();
        if(!processor->validate(currentCommand, *state)){ //should not test whether the file is valid - only that the command is valid in current state
            cout << "Invalid command at this point! Try again" <<endl;
            continue;
        }

        string fileName;
        try{
            fileName = currentCommand->getCommandText().substr(8);
            loadedMap = loadMap(fileName);
            transition("maploaded");
            if(loadedMap.getTerritories()->empty()) *state="start";
        } catch (...){
            cout << "Error - non-existent file name"<<endl;
        }
    } while  (currentCommand == nullptr|| !processor->validate(currentCommand) || *state!="maploaded");

    do {
        cout<< "Please enter validatemap to proceed" << endl;
        currentCommand = processor->getCommand();
        if(!processor->validate(currentCommand, *state)){
            cout << "Invalid command at this point! Try again" <<endl;
            continue;
        }
        if(validateMap(loadedMap)){
            cout << "Map has been validated!" <<endl;
            transition("mapvalidated");
        }

    } while (!processor->validate(currentCommand));

    int playerCount= 0;
    do{
        cout << "Please enter addplayer and the player name (separated by space) - (2-6 players)" <<endl;
        cout << "To exit the adding players phase: type exit" << endl;
        cout << "You have " << playerCount << " player(s) so far" << endl;
        currentCommand = processor->getCommand();
        if(!processor->validate(currentCommand, *state)){
            cout << "Invalid command at this point! Try again" <<endl;
            continue;
        }

        try{
            string playerName = currentCommand->getCommandText().substr(10);
            auto *player = new Player(playerName);
            addPlayer(player);
            playerCount++;
            transition("playersadded");

            if(playerCount>=2){
                cout << "** Would you like to stop adding players? Enter Y to stop, enter any other key to continue" << endl;
                currentCommand = processor->getCommand();
                if (currentCommand->getCommandText() == "Y") break;
            }

        } catch (...){
            cout << "Error - non-existent player name"<<endl;
        }
    }while (playerCount <= 6);

    do {
        cout<< "Please enter gamestart to proceed" << endl;
        currentCommand = processor->getCommand();
        if(!processor->validate(currentCommand, *state)){
            cout << "Invalid command at this point! Try again" <<endl;
            continue;
        }

//        a) fairly distribute all the territories to the players
        // Get all territories from the map
        vector<Territory*> allTerritories = *globalMap->getTerritories();

        // Shuffle territories to randomize the assignment
        srand(time(0));  // Seed the random number generator
        random_shuffle(allTerritories.begin(), allTerritories.end());

        int playerIndex = 0;
        // Distribute the territories to players
        for (auto& territory : allTerritories) {
            players[playerIndex]->addOwnedTerritory(territory);

            // Move to the next player (round-robin)
            playerIndex = (playerIndex + 1) % players.size();
        }

        // Output the territories each player owns
        for (const auto& player : players) {
            cout << player->getPlayerName() << " owns the following territories:" << endl;
            for (const auto& territory : player->getOwnedTerritories()) {
                cout << "- " << territory->getName() << endl;
            }
            cout << endl;
        }
//        b) determine randomly the order of play of the players in the game
        // Randomize the order of players in the array
        // Seed a random number generator
        random_device rd;
        default_random_engine rng(rd());
        // Shuffle the vector
        shuffle(players.begin(), players.end(), rng);
        cout << "Players order has been randomized" << endl;

//        c) give 50 initial army units to the players, which are placed in their respective reinforcement pool
        // Done when you create a Player
//        d) let each player draw 2 initial cards from the deck using the deck’s draw() method
        for (auto player : players){
            player->getHand()->place(deck->draw());
            player->getHand()->place(deck->draw());
            cout << "Armies: " << player->getArmies() << endl; // Check if armies got done well
        }

//        e) switch the game to the play phase
        transition("play");

    } while (!processor->validate(currentCommand));

}


void GameEngine::mainGameLoop() {
    reinforcementPhase();
    ordersIssuingPhase();
    ordersExecutionPhase();
}

bool GameEngine::reinforcementPhase() {

    for (auto player : players)
    {
        // Check which continents player occupies
        /*
        vector<Continent> continentsOccupied;
        for (auto continent : *globalMap->getContinents())
        {
            // assume its occupied and go through the list
            bool occupied = true;
            for (auto territory : continent->getCTerritories())
            {
                if (territory->getOwner().compare(player->getPlayerName()) != 0)
                {
                    occupied = false;
                    break;
                }
            }

            if (occupied)
            {
                continentsOccupied.push_back(*continent);
            }
        }


        // Give player continent bonus(es)


        for (auto continent : continentsOccupied)
        {
            continentBonus += continent.getBonus();
        }
        */

        int continentBonus = 0;

        // Allocate units to player
        int units = player->getOwnedTerritories().size() / 3 + continentBonus;
        if (units >= 3)
        {
            std::cout << "+" << units << " units in " << player->getPlayerName() << "'s reinforcement pool" << std::endl;
            player->setReinforcementPool(units);
        }
        else
        {
            std::cout << "+3 units in " << player->getPlayerName() << "'s reinforcement pool" << std::endl;

            player->setReinforcementPool(3);
        }
    }
    return true;
}


bool GameEngine::ordersIssuingPhase() {
     for (auto player : players){
        vector<Territory *> territoriesToAttack = player->toAttack();

        vector<Territory *> territoriesToDefend = player->toDefend();
        /*
            Deploy units from reinforcement pool
        */
        string territoryList = "";
        for (int i = 0; i < territoriesToDefend.size(); i++)
        {
            territoryList += territoriesToDefend[i]->getName() + "( " + std::to_string(i) + " ), ";
        }

        int numUnits = player->getReinforcementPool();
        int unitsDeployed = 0;
        while (unitsDeployed < numUnits)
        {
            std::cout << "Deploy units to which territory? " << territoryList << std::endl;
            string territory;
            std::cin >> territory;
            int tIndex = std::stoi(territory);

            if (!(tIndex >= 0 && tIndex < territoriesToDefend.size()))
            {
                std::cout << "Invalid territory number/index" << std::endl;
            }

            std::cout << "How many units? " << std::endl;
            string units;
            std::cin >> units;
            int unitsI = std::stoi(units);

            if (unitsI > 0 && unitsI + unitsDeployed <= numUnits)
            {

                Order* deployOrder =  new DeployOrder(player, territoriesToDefend[tIndex], unitsI);
                player->issueOrder(deployOrder);
                unitsDeployed += unitsI;
            }
            else
            {
                std::cout << "Invalid number of units (1 - units left in pool) " << std::endl;
            }
        }

        /*
            Advance orders
        */

         // Advance to defend
         for (auto sourceTerritory : territoriesToDefend)
         {
             for (auto targetTerritory : territoriesToDefend)
             {
                 if (sourceTerritory->getName().compare(targetTerritory->getName()) != 0)
                 {
                     std::cout << "Advance units from " << sourceTerritory->getName() << " to " << targetTerritory->getName() << "? (y/n)" << std::endl;
                     string answer;
                     std::cin >> answer;
                     if (answer.compare("y") == 0)
                     {
                         std::cout << "How many units? " << std::endl;
                         string units;
                         std::cin >> units;
                         int unitsI = std::stoi(units);

                         Order* advanceOrder = new AdvanceOrder(player, sourceTerritory, targetTerritory, unitsI);
                         player->issueOrder(advanceOrder);
                         break;
                     }
                 }
             }
         }

         // Advance to attack
         for (auto sourceTerritory  : territoriesToDefend)
         {
             for (auto targetTerritory  : territoriesToAttack)
             {
                 if (sourceTerritory ->getName().compare(targetTerritory ->getName()) != 0)
                 {
                     std::cout << "Advance units from " << sourceTerritory ->getName() << " to " << targetTerritory->getName() << "? (y/n)" << std::endl;
                     string answer;
                     std::cin >> answer;
                     if (answer.compare("y") == 0)
                     {
                         std::cout << "How many units? " << std::endl;
                         string units;
                         std::cin >> units;
                         int unitsI = std::stoi(units);


                         Order* advanceOrder = new AdvanceOrder(player, sourceTerritory, targetTerritory, unitsI);
                         player->issueOrder(advanceOrder);
                         break;
                     }
                 }
             }
         }

        /*
            Issue order from one card in hand
        */
         // Advance to attack
         for (auto sourceTerritory  : territoriesToDefend)
         {
             for (auto targetTerritory  : territoriesToAttack)
             {
                 if (sourceTerritory ->getName().compare(targetTerritory ->getName()) != 0)
                 {
                     std::cout << "Advance units from " << sourceTerritory ->getName() << " to " << targetTerritory->getName() << "? (y/n)" << std::endl;
                     string answer;
                     std::cin >> answer;
                     if (answer.compare("y") == 0)
                     {
                         std::cout << "How many units? " << std::endl;
                         string units;
                         std::cin >> units;
                         int unitsI = std::stoi(units);


                         Order* advanceOrder = new AdvanceOrder(player, sourceTerritory, targetTerritory, unitsI);
                         player->issueOrder(advanceOrder);
                         break;
                     }
                 }
             }
         }
    }
    return true;
}

string GameEngine::ordersExecutionPhase() {
    for (auto player : players)
    {
        OrdersList *orderList = player->getOrdersList();
        Order *nextOrder = orderList->getNextOrder();
        while (nextOrder != nullptr)
        {
            nextOrder->execute();
        }
    }
    return getCommand();
}


bool GameEngine::endPhase() {
    cout << "... End Phase ..." << endl;
    // Validate win
    *state = "win";
    return true;
}

// SETTERS AND GETTERS FOR PLAY
string GameEngine::getState() const {
    if(state == nullptr) {
        return "start";
    }
    return *state;
}
void GameEngine::transition(std::string newState) {
    if(state == nullptr) {
        state = new string("start");
    }else {
        *state = newState;
    }
    notify(this);
}
string GameEngine::getCommand() const {
    if(command == nullptr) {
        return ""; // Return empty string if command is initialized
    }
    return *command; // Dereference and return the actual value
}
void GameEngine::setCommand(const string& cmd) {
    if(command == nullptr) {
        command = new string(cmd); // Allocate memory and set command if it is initialized
    }else {
        *command = cmd; // Assign new value if already allocated
    }
}
bool GameEngine::getInvalidCommand() const {
    return *invalidCommand;     // Dereference and get value
}
void GameEngine::setInvalidCommand(bool value){
    *invalidCommand = value;        // Dereference and assign new value
}

void GameEngine::addPlayer(Player *player) {
    players.push_back(player);
    cout << player->getPlayerName() << " has been added to the game!" << endl;
}

string GameEngine::stringToLog() {
    return "Game Engine new state: " + *state;
}

