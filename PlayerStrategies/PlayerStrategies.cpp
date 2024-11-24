
#include "PlayerStrategies.h"

void Neutral::issueOrder(Order *o) {

}

vector<Territory *> Neutral::toAttack() {
    return vector<Territory *>();
}

vector<Territory *> Neutral::toDefend() {
    return vector<Territory *>();
}

void Cheater::issueOrder(Order *o) {

}

vector<Territory *> Cheater::toAttack() {
    return vector<Territory *>();
}

vector<Territory *> Cheater::toDefend() {
    return vector<Territory *>();
}

void Human::issueOrder(Order *o) {

}

vector<Territory *> Human::toAttack() {
    return vector<Territory *>();
}

vector<Territory *> Human::toDefend() {
    return vector<Territory *>();
}

void Aggressive::issueOrder(Order *o) {

}

vector<Territory *> Aggressive::toAttack() {
    return vector<Territory *>();
}

vector<Territory *> Aggressive::toDefend() {
    return vector<Territory *>();
}

void Benevolent::issueOrder(Order *o) {

}

vector<Territory *> Benevolent::toAttack() {
    return vector<Territory *>();
}

vector<Territory *> Benevolent::toDefend() {
    return vector<Territory *>();
}
