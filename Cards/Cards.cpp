#include <iostream>
#include "Cards.h"
#include "vector";
using namespace std;

vector<string> cardTypeLookup = {"Bomb", "Reinforcement", "Blockade", "Airlift", "Diplomacy"};

//CARDS
Card::Card() {
    setRandomType();
}
Card::~Card() {}
Card::Card(string type) {}
Card::Card(int type) {
    if(type<cardTypeLookup.size()){
        this->type = new string(cardTypeLookup[type]);
    } else {
        cout << type << " is not a correct card type!\n";
    }

}

//void Card::setType(int type) {}
//void Card::setType(string type) {}

int Card::getTypeID() {}
string Card::getType() {}
void Card::setRandomType() {
    int typeID = rand()%5;
    this->type = new string(cardTypeLookup[typeID]);
}
bool Card::play() {}
void Card::displayCard() {
    cout << "This is a " << *type << " card!\n";
}


//DECK
Deck::Deck() { initialize();}
Deck::~Deck() {}

void Deck::initialize() { //50 cards, 10 of each type by default
    int numCards = 50;
    for (int i = 0; i<cardTypeLookup.size(); i++){
        for (int j=0; j<numCards/cardTypeLookup.size(); j++){
            cards.push_back(*new Card(i));
        }
    }
}
void Deck::initializeRand(int numCards) {}

Card *Deck::draw() {}
void Deck::shuffle() {}
void Deck::returnToDeck(Card *card) {}
void Deck::display() {
    for (int i = 0 ; i<cards.size(); i++){
        cout << (i+1) << ": ";
        cards[i].displayCard();
    }
}



//HAND
Hand::Hand() {}
Hand::~Hand() {}

void Hand::display() {}

void Hand::addToHand(Card *card) {}
