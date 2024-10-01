#include <iostream>
#include "Cards.h"
using namespace std;

string cardTypeLookup[5] = {"Bomb", "Reinforcement", "Blockade", "Airlift", "Diplomacy"};

//CARDS
Card::Card() {}
Card::~Card() {}
Card::Card(string type) {}
Card::Card(int type) {}

void Card::setType(int type) {}
void Card::setType(string type) {}

int Card::getTypeID() {}
string Card::getType() {}

bool Card::play() {}


//DECK
Deck::Deck() {}
Deck::~Deck() {}

void Deck::initialize() {}
void Deck::initialize(int numCards) {}

Card *Deck::draw() {}
void Deck::shuffle() {}



//HAND
Hand::Hand() {}
Hand::~Hand() {}

void Hand::display() {}

void Hand::addToHand(Card *card) {}
