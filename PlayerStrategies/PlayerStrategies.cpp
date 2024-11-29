
#include "PlayerStrategies.h"
#include "Cards.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Player;
class Territory;
class Order;

string PlayerStrategy::getType() {return *type;}

// ****************************** Neutral Player ******************************
/*
 * Neutral Player Constructor
 */
Neutral::Neutral(Player *player) {
    this->player = player;
    type= new string("neutral");
}
/*
 * Neutral Player issues a specific order
 */
void Neutral::issueOrder(Order *o) {

}
/*
 * Neutral Player issues an order
 */
void Neutral::issueOrder() {
    cout << player->getPlayerName() << " is a neutral player. No actions taken during this turn." << endl;
}
/*
 * Neutral Player: Does not attack
*/
vector<Territory *> Neutral::toAttack() {
    return {}; //Neutral player does not attack unprovoked
}
/*
 * Neutral Player: Does not defend
 */
vector<Territory *> Neutral::toDefend() {
    return {}; //Neutral player does not defend unprovoked
}

// ****************************** Cheater Player ******************************
/*
 * Cheater Player Constructor
 */
Cheater::Cheater(Player *player) {
    this->player = player;
    type= new string("cheater");
}

void Cheater::issueOrder(Order *o) {

}

void Cheater::issueOrder() {

}

vector<Territory *> Cheater::toAttack() {
    return vector<Territory *>();
}

vector<Territory *> Cheater::toDefend() {
    return vector<Territory *>();
}


// ****************************** Human Player ******************************
/*
 * Human Player Constructor
 */
Human::Human(Player *player) {
    this->player = player;
    type=new string("human");
}

void Human::issueOrder(Order *newOrder) {
    if (newOrder != nullptr) {
        player->addToOrderList(newOrder);
        std::cout << newOrder->getOrderType() << " order issued." << std::endl;
    } else {
        std::cout << "Error: Cannot issue a null order." << std::endl;
    }
}
/*
 * Neutral Player issues an order
 */
void Human::issueOrder() {
    cout << "\n*****\n" <<player->getPlayerName() << ": What are your orders?" << endl;
    cout << "---You have " << player->getReinforcementPool() << " armies available for deployment\nOPTIONS (enter the number):" << endl;
    cout << "1 - Deploy Armies\n2 - Advance Armies\n3 - Play a card\n4 - End your turn\n--Enter your choice: " << endl;
    string choice;
    choice = processor->getCommand()->getCommandText();
    if(choice == "1"){ //Deploy
        try{
            cout << "Deployment chosen\n\tWhere would you like to deploy your armies?"<<endl;
            for(int i = 0; i<player->toDefend().size(); i++){
                cout<<"\t" << (i+1) << "\t" << player->toDefend().at(i)->getName() << endl;
            }
            choice = processor->getCommand()->getCommandText();
            int choiceNum = stoi(choice);
            Territory *chosenTerr = player->toDefend().at((choiceNum - 1));
            string chosenTerrStr = chosenTerr->getName();
            cout << "How many units would you like to deploy to " << chosenTerrStr << "?" << "  Total maximum of " <<
                    player->getReinforcementPool() << ", otherwise order will be invalid upon execution" << endl;
            choice = processor->getCommand()->getCommandText();
            choiceNum = stoi(choice);
            if (choiceNum>0){
                Order* deployOrder = new DeployOrder(player, chosenTerr, choiceNum);
                player->addToOrderList(deployOrder);
                cout << "Order deploying " <<choiceNum<< " armies to " << chosenTerrStr << " added to " << player->getPlayerName() << "'s orderlist!" <<endl;
            } else {
                cout << "\nNumber of units must be an integer greater than 0." << endl;
            }
        } catch(...){
            cout << "\nInvalid entry - enter a valid option" <<endl;
        }
        this->issueOrder();
    }
    else if (choice == "2"){ //Advance
        try{
            cout << "Advancement chosen\n\tWhat is the source territory?"<<endl;
            for(int i = 0; i<player->getOwnedTerritories().size(); i++){
                cout<<"\t" << (i+1) << "\t" << player->getOwnedTerritories().at(i)->getName() << endl;
            }
            choice = processor->getCommand()->getCommandText();
            int choiceNum = stoi(choice);
            Territory *sourceTerr = player->getOwnedTerritories().at((choiceNum - 1));
            string sourceTerrStr = sourceTerr->getName();

            cout << "Advancement chosen\n\tWhat is the target territory?"<<endl;
            for(int i = 0; i<sourceTerr->adjacentTerritories.size(); i++){
                    cout<<"\t" << (i+1) << "\t" << sourceTerr->adjacentTerritories.at(i)->getName() << endl;
            }
            choice = processor->getCommand()->getCommandText();
            choiceNum = stoi(choice);
            Territory *targetTerr = sourceTerr->adjacentTerritories.at(choiceNum-1);
            string targetTerrStr = targetTerr->getName();

        } catch(...){
            cout << "\nInvalid entry - enter a valid option" <<endl;
        }
        this->issueOrder();
    }
    else if (choice == "3"){ //Play Card
        auto playerHand = player->getHand();
        cout << "Which card would you like to play?"<<endl;
        cout << playerHand <<endl;
        try{
            choice = processor->getCommand()->getCommandText();
            int choiceNum = stoi(choice);

            auto toPlay = playerHand->getHand()->at(choiceNum-1);
            string type = toPlay->getType();
            //"Bomb", "Reinforcement", "Blockade", "Airlift", "Diplomacy"
            if (type == "Bomb"){
                cout << toPlay << endl;
                cout << "Choose a territory to bomb (your own are excluded)";
                for (int i = 0; i<player->toAttack().size(); i++){
                    cout << "\t" << (i+1) << player->toAttack().at(i)->getName() << endl;
                }
            }
            else if (type == "Reinforcement"){
                cout << toPlay << endl;
            }
            else if (type == "Blockade"){
                cout << toPlay << endl;
            }
            else if (type == "Airlift"){
                cout << toPlay << endl;
            }
            else if (type == "Diplomacy"){
                cout << toPlay << endl;
            }
            else {throw runtime_error("Incorrect Card!");}

        } catch(...){
            cout << "\nInvalid entry - enter a valid option" <<endl;
            }

        this->issueOrder();
    }
    else if (choice == "4"){ //End turn
        cout << "End of this turn."<<endl;
    }
    else {
        cout << "Invalid option!"<<endl;
        this->issueOrder();
    }

}

vector<Territory *> Human::toAttack() {
    return vector<Territory *>();
}

vector<Territory *> Human::toDefend() {
    return vector<Territory *>();
}


// ****************************** Aggressive Player ******************************
/*
 * Aggressive Player Constructor
 */
Aggressive::Aggressive(Player *player) {
    this->player = player;
    type=new string("aggressive");
}

void Aggressive::issueOrder(Order *o) {

}
/*
 * Neutral Player issues an order
 */
void Aggressive::issueOrder() {

}

vector<Territory *> Aggressive::toAttack() {
    return vector<Territory *>();
}

vector<Territory *> Aggressive::toDefend() {
    return vector<Territory *>();
}


// ****************************** BenevolentPlayer ******************************
/*
 * Benevolent Player Constructor
 */
Benevolent::Benevolent(Player *player) {
    this->player = player;
    type=new string("benevolent");
}

void Benevolent::issueOrder(Order *o) {

}
/*
 * Neutral Player issues an order
 */
void Benevolent::issueOrder() {
    // Deploy armies on the weakest countries

    // Will use cards but non harming ones (Blockade, Diplomacy, Reinforcement)

}

vector<Territory *> Benevolent::toAttack() {
    return {}; // Never advances on enemy territory
}

vector<Territory *> Benevolent::toDefend() {
    return vector<Territory *>(); // Only defends its territories
}


