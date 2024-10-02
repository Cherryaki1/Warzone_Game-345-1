#include <iostream>
#include "Cards.h"
#include "vector"
using namespace std;

vector<string> cardTypeLookup = {"Bomb", "Reinforcement", "Blockade", "Airlift", "Diplomacy"};

//CARDS
Card::Card() { //Default constructor with a random card type
    setRandomType();
}
Card::Card(int type) { //Constructor that takes a type
    if(type<cardTypeLookup.size()){
        this->type = new string(cardTypeLookup[type]);
    } else {
        cout << type << " is not a correct card type!\n";
    }
}
Card::~Card() { //Destructor
    delete type;
    delete cardID;
}
string Card::getType() {
    return *this->type;
}

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
Deck::~Deck() {
//    delete cards;
    delete numCards;
}

void Deck::initialize() { //50 cards, 10 of each type by default
    this->numCards = new int(50);

    for (int i = 0; i<cardTypeLookup.size(); i++){
        for (int j=0; j < *numCards / cardTypeLookup.size(); j++){
            cards.push_back(new Card(i));
        }
    }
}
void Deck::initializeRand(int numCards) {}


void Deck::shuffle() {}
void Deck::returnToDeck(Card *card) {}
void Deck::display() {
    for (int i = 0 ; i<cards.size(); i++){
        cout << (i+1) << ": ";
        cards.at(i)->displayCard();
    }
}

Card* Deck::draw() {
    srand(time(0));
    int index = rand()%(*numCards+1);
    Card* drawn = cards.at(index);
    *numCards--;
    cards.erase(cards.begin()+index);
    return drawn;
}

//HAND
Hand::Hand() {}
Hand::~Hand() {}

void Hand::display() {}

void Hand::place(Card* card){

}

//void Hand::draw(Deck *deck) {}
