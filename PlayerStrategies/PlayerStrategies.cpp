
#include "PlayerStrategies.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Player;
class Territory;
class Order;

void Neutral::issueOrder(Order *o) {

}

void Neutral::issueOrder() {
    cout << player->getPlayerName() << " is a neutral player. No actions taken during this turn." << endl;
}

vector<Territory *> Neutral::toAttack() {
    return {}; //Neutral player does not attack unprovoked
}

vector<Territory *> Neutral::toDefend() {
    return {}; //Neutral player does not defend unprovoked
}

Neutral::Neutral(Player *player) {
    this->player = player;
    type= new string("neutral");
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

Cheater::Cheater(Player *player) {
    this->player = player;
    type= new string("cheater");
}

void Human::issueOrder(Order *newOrder) {
    if (newOrder != nullptr) {
        player->addToOrderList(newOrder);
        std::cout << newOrder->getOrderType() << " order issued." << std::endl;
    } else {
        std::cout << "Error: Cannot issue a null order." << std::endl;
    }
}

void Human::issueOrder() {
    cout << "\n*****\n" <<player->getPlayerName() << ": What are your orders?" << endl;
    cout << "---You have " << player->getReinforcementPool() << " armies available for deployment\nOPTIONS (enter the number):" << endl;
    cout << "1 - Deploy Armies\n2 - Advance Armies\n3 - Play a card\n4 - End your turn\n--Enter your choice: " << endl;
    string choice;
    cin >> choice;
    if(choice == "1"){ //Deploy
        cout << "Deployment chosen"<<endl;
    }
    else if (choice == "2"){ //Advance
        cout << "Advancement chosen"<<endl;
    }
    else if (choice == "3"){ //Play Card
        cout << "Playing a carding"<<endl;
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

Human::Human(Player *player) {
    this->player = player;
    type=new string("human");
}

void Aggressive::issueOrder(Order *o) {

}

void Aggressive::issueOrder() {

}

vector<Territory *> Aggressive::toAttack() {
    return vector<Territory *>();
}

vector<Territory *> Aggressive::toDefend() {
    return vector<Territory *>();
}

Aggressive::Aggressive(Player *player) {
    this->player = player;
    type=new string("aggressive");
}

void Benevolent::issueOrder(Order *o) {

}

void Benevolent::issueOrder() {

}

vector<Territory *> Benevolent::toAttack() {
    return vector<Territory *>();
}

vector<Territory *> Benevolent::toDefend() {
    return vector<Territory *>();
}

Benevolent::Benevolent(Player *player) {
    this->player = player;
    type=new string("benevolent");
}

