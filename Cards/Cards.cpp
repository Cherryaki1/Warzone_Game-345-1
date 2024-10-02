#include <iostream>
#include "Cards.h"
using namespace std;

string cardTypeLookup[5] = {"Bomb", "Reinforcement", "Blockade", "Airlift", "Diplomacy"};

//CARDS
Card::Card() {
    setRandomType();
}
Card::~Card() {}
Card::Card(string type) {}
Card::Card(int type) {}

//void Card::setType(int type) {}
//void Card::setType(string type) {}

int Card::getTypeID() {}
string Card::getType() {}
void Card::setRandomType() {
//    srand(time(0));
    int typeID = rand()%5;
    this->type = new string(cardTypeLookup[typeID]);
}
bool Card::play() {}
void Card::displayCard() {
    cout << "This is a " << *type << " card!\n";
}


//DECK
Deck::Deck() {}
Deck::~Deck() {}

void Deck::initialize() {}
void Deck::initialize(int numCards) {}

Card *Deck::draw() {}
void Deck::shuffle() {}
void Deck::returnToDeck(Card *card) {}



//HAND
Hand::Hand() {}
Hand::~Hand() {}

void Hand::display() {}

void Hand::addToHand(Card *card) {}
