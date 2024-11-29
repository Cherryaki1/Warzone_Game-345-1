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
    gameMap = nullptr;
}

GameEngine::~GameEngine() {
    if (state != nullptr) {
        delete state;
        state = nullptr;
    }

    for (Player* player : players) {
        if (player != nullptr) {
            delete player;
            player = nullptr;
        }
    }

    if (processor != nullptr) {
        delete processor;
        processor = nullptr;
    }

    if (deck != nullptr) {
        delete deck;
        deck = nullptr;
    }


    if (gameMap != nullptr) {
        delete gameMap;
        gameMap = nullptr;
    }

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
            gameMap = &loadMap(fileName);
            transition("maploaded");
            if(gameMap->getTerritories()->empty()) transition("start");
        } catch (...){
            cout << "Error - non-existent file name"<<endl;
        }
    } while  (*state!="maploaded");

    do {
        cout<< "Please enter validatemap to proceed" << endl;
        currentCommand = processor->getCommand();
        if(!processor->validate(currentCommand, *state)){
            cout << "Invalid command at this point! Try again" <<endl;
            continue;
        }
        if(validateMap(*gameMap)){
            cout << "Map has been validated!" <<endl;
            transition("mapvalidated");
        }

    } while (*state!="mapvalidated");

    int playerCount= 0;
    do{
        cout << "Please enter addplayer and the player name (separated by space) - (2-6 players)" <<endl;
        cout << "You have " << playerCount << " player(s) so far" << endl;
        currentCommand = processor->getCommand();
        if(!processor->validate(currentCommand, *state)){
            cout << "Invalid command at this point! Try again" <<endl;
            continue;
        }

        try{
            string playerName = currentCommand->getCommandText().substr(10);
            auto *player = new Player(playerName);
            definePlayerStrategy(player);
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
    }while (playerCount <= 6 || *state!="playersadded");

    do {
        cout<< "Please enter gamestart to proceed" << endl;
        currentCommand = processor->getCommand();
        if(!processor->validate(currentCommand, *state)){
            cout << "Invalid command at this point! Try again" <<endl;
            continue;
        }

//        a) fairly distribute all the territories to the players
        // Get all territories from the map
        vector<Territory*> allTerritories = *gameMap->getTerritories();

        // Shuffle territories to randomize the assignment
        srand(time(0));  // Seed the random number generator
        random_shuffle(allTerritories.begin(), allTerritories.end());

        int playerIndex = 0;
        // Distribute the territories to players
        for (auto& territory : allTerritories) {
            players[playerIndex]->addOwnedTerritory(territory);

            // Set the owner of the territory to the player's name
            territory->setOwner(players[playerIndex]->getPlayerName());

            cout << "Territory: " << territory->getName() << " is now owned by: " << territory->getOwner() << endl;

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

    } while (*state != "play");

}


void GameEngine::mainGameLoop() {
    reinforcementPhase();
    ordersIssuingPhase();
    ordersExecutionPhase();
}

bool GameEngine::reinforcementPhase() {
    std::cout << "Starting reinforcement phase..." << std::endl;

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

void GameEngine::ordersIssuingPhase2() { //Trying something new
    std::cout << "Starting orders execution phase..." << std::endl;

    for(auto player : players){
        player->issueOrder();
    }

}

bool GameEngine::ordersIssuingPhase() {
    std::cout << "Starting orders issuing phase..." << std::endl;

     for (auto player : players){
         std::cout << player->getPlayerName() << "'s orders issue phase" << std::endl;
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
            std::cout << "Deploy units to which territory? (You have " << (numUnits-unitsDeployed) << " units left in your pool): " << territoryList << std::endl;
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
                std::cout << "Invalid number of units ( " << (numUnits-unitsDeployed)  << " units left in pool) " << std::endl;
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

         /*
            Issue order from one card in hand

         // Get the cards in the player's hand
         auto handCards = player->getHand()->getHand();

         // Check if there are cards to play
         if (handCards->empty()) {
             std::cout << "No cards in hand to play." << std::endl;
         } else {
             std::cout << "Cards in your hand:" << std::endl;
             for (size_t i = 0; i < handCards->size(); ++i) {
                 std::cout << i << ": " << handCards->at(i)->getType() << " card" << std::endl;
             }

             // Prompt the player to select a card to play
             int cardIndex = -1;
             std::cout << "Enter the number of the card you want to play, or -1 to skip: ";
             std::cin >> cardIndex;

             // Validate the choice
             if (cardIndex >= 0 && cardIndex < static_cast<int>(handCards->size())) {
                 Card* selectedCard = handCards->at(cardIndex);
                 selectedCard->play();// Optionally remove the card after playing
                 std::cout << "Card played successfully." << std::endl;
             } else if (cardIndex == -1) {
                 std::cout << "You chose not to play any card." << std::endl;
             } else {
                 std::cout << "Invalid choice. No card played." << std::endl;
             }
         }
         */

    }
    return true;
}

string GameEngine::ordersExecutionPhase() {
    std::cout << "\nStarting orders execution phase..." << std::endl;

    // Loop through each player
    for (auto player : players) {
        std::cout << "Executing orders for player: " << player->getPlayerName() << std::endl;
        OrdersList* orderList = player->getOrdersList();
        int position = 0;

        // Execute orders as long as the list is not empty
        while (!orderList->isEmpty()) {
            Order* currentOrder = orderList->getOrders().front(); // Get the first order

            std::cout << "Executing order: " << currentOrder->getOrderType() << " for player: " << player->getPlayerName() << std::endl;

            // Execute the order
            currentOrder->execute();

            // Check if the order was executed successfully
            if (currentOrder->isExecuted()) {
                std::cout << "Order executed successfully." << std::endl;
                orderList->remove(position);  // Remove the order from the list
            } else {
                std::cout << "Skipping invalid order for player " << player->getPlayerName() << std::endl;
//                position++;  // Move to the next position for the next iteration
                orderList->remove(position);  // Remove the order from the list
            }
            cout << "\n" << endl;
        }

        std::cout << "Finished executing orders for player: " << player->getPlayerName() << "\n" << std::endl;
    }

    std::cout << "Orders execution phase completed." << std::endl;
    return getCommand();  // Return the current command, if applicable
}




bool GameEngine::endPhase() {
    cout << "... End Phase ..." << endl;
    // Validate win
    transition("win");
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
    cout << player->getPlayerName() << " (" << player->getStrategyType() << ")"<<" has been added to the game!" << endl;
}

string GameEngine::stringToLog() {
    return "Game Engine new state: " + *state;
}

void GameEngine::definePlayerStrategy(Player *player) {
    cout << "What type of player will this be? Type:" << endl;
    string strategy = "";
    int strat = 0;
    cout << "1  human" << "\n" << "2  cheater" << "\n" << "3  aggressive" << "\n" << "4  neutral" << "\n" << "5  benevolent" << endl;
    strategy = processor->getCommand()->getCommandText();
    try {
        strat = stoi(strategy);
    }catch(exception &err){
        cout << "Invalid strategy, human strategy has been set by default" << endl;
        strat = 1;
    }

    bool done = false;
    while (!done) {
        switch (strat) {
            case 1:
                cout << "Human Chosen" << endl;
                done = true;
                break;
                case 2:
                    cout << "Cheater Chosen" << endl;
                    player->setStrategy("cheater");
                    done = true;
                    break;
                case 3:
                    cout << "Aggressive Chosen" << endl;
                    player->setStrategy("aggressive");
                    done = true;
                break;
                case 4:
                    cout << "Neutral Chosen" << endl;
                    player->setStrategy("neutral");
                    done = true;
                break;
                case 5:
                    cout << "Benevolent Chosen" << endl;
                    player->setStrategy("benevolent");
                    done = true;
                break;
                default:
                    cout << "Unknown Type was chosen, try again" << endl;
        }
    }
}

vector<Player *> *GameEngine::getPlayerList() {
    return &players;
}

