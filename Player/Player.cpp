#include <iostream>
#include "Player.h"

using namespace std;

Player::Player() {
    playerName = "";
    //playerHand = new Hand();
    //ordersList = new OrdersList();

}

Player::Player(string name) {
    playerName = name;
    //playerHand = new Hand();
    //ordersList = new OrdersList();

}

void Player::toAttack() {
}

void Player::toDefend() {
}

void Player::issueOrder() {
}

