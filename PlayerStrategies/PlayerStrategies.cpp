
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

vector<Territory *> Neutral::toAttack() {
    return vector<Territory *>();
}

vector<Territory *> Neutral::toDefend() {
    return vector<Territory *>();
}

Neutral::Neutral(Player *player) {
    this->p = player;
    type= new string("neutral");
}

void Cheater::issueOrder(Order *o) {

}

vector<Territory *> Cheater::toAttack() {
    return vector<Territory *>();
}

vector<Territory *> Cheater::toDefend() {
    return vector<Territory *>();
}

Cheater::Cheater(Player *player) {
    this->p = player;
    type= new string("cheater");
}

void Human::issueOrder(Order *newOrder) {
    if (newOrder != nullptr) {
        p->addToOrderList(newOrder);
        std::cout << newOrder->getOrderType() << " order issued." << std::endl;
    } else {
        std::cout << "Error: Cannot issue a null order." << std::endl;
    }
}

vector<Territory *> Human::toAttack() {
    return vector<Territory *>();
}

vector<Territory *> Human::toDefend() {
    return vector<Territory *>();
}

Human::Human(Player *player) {
    this->p = player;
    type=new string("human");
}

void Aggressive::issueOrder(Order *o) {

}

vector<Territory *> Aggressive::toAttack() {
    return vector<Territory *>();
}

vector<Territory *> Aggressive::toDefend() {
    return vector<Territory *>();
}

Aggressive::Aggressive(Player *player) {
    this->p = player;
    type=new string("aggressive");
}

void Benevolent::issueOrder(Order *o) {

}

vector<Territory *> Benevolent::toAttack() {
    return vector<Territory *>();
}

vector<Territory *> Benevolent::toDefend() {
    return vector<Territory *>();
}

Benevolent::Benevolent(Player *player) {
    this->p = player;
    type=new string("benevolent");
}

