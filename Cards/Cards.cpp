#include <iostream>
#include "Cards.h"
#include "vector"
using namespace std;

vector<string> cardTypeLookup = {"Bomb", "Reinforcement", "Blockade", "Airlift", "Diplomacy"};

//CARDS
Card::Card() { //Default constructor with a random card type
    setRandomType();
}
Card::Card(int type, Deck* origin) { //Constructor that takes a type
    if(type<cardTypeLookup.size()){
        this->type = new string(cardTypeLookup[type]);
        this->origin = origin;
    } else {
        cout << type << " is not a correct card type!\n";
    }
}
Card::~Card() { //Destructor
    delete type;
    delete cardID;
    origin = nullptr;
    hand = nullptr;
}
string Card::getType() {
    return *this->type;
}

void Card::setRandomType() {
    int typeID = rand()%5;
    this->type = new string(cardTypeLookup[typeID]);
}

void Card::setHand(Hand *handO) {
    hand = handO;
}

void Card::play() {
    // PLAY THE CARD, special order etc.
    cout << "\t" <<this->getType() << " card played\n";
    this->origin->returnToDeck(this); //Returns card to deck
    this->hand->remove(this);
}
void Card::displayCard() {
    cout << "This is a " << *type << " card!\t\n";
}

//DECK
Deck::Deck() { initialize();}
Deck::~Deck() {
    for (int i = 0; i<cards.size(); i++){
        delete cards.at(i);
    }
}

void Deck::initialize() { //50 cards, 10 of each type by default
    int numCards = 50;

    for (int i = 0; i<cardTypeLookup.size(); i++){
        for (int j=0; j < numCards / cardTypeLookup.size(); j++){
            cards.push_back(new Card(i, this));
        }
    }
}

void Deck::shuffle() {}
void Deck::returnToDeck(Card *card) {
    cards.push_back(card);
}
void Deck::display() {
    for (int i = 0 ; i<cards.size(); i++){
        cout << (i+1) << ": ";
        cards.at(i)->displayCard();
    }
}
void Deck::summarize(){
    for (int i = 0; i<cardTypeLookup.size(); i++){
        int counter = 0;
        for(int j = 0; j<cards.size(); j++){
            if(cards.at(j)->getType()==cardTypeLookup.at(i)) counter++;
        }
        cout << "\t" << counter << " " <<cardTypeLookup.at(i) << " cards\n";
    }
}

Card* Deck::draw() {
    srand(time(0));
    int index = rand()%(cards.size());
    Card* drawn = cards.at(index);
    cards.erase(cards.begin()+index);
    return drawn;
}

//HAND
Hand::Hand() {}
Hand::~Hand() {}

void Hand::display() {
    cout << "Cards in your hand: ("<< cards.size() <<")\n";
    for (int i = 0; i<cards.size(); i++){
        cout << "\t" <<i+1 << ": ";
        cards.at(i)->displayCard();
    }
}

void Hand::place(Card* card){
    cards.push_back(card);
    card->setHand(this);
}

void Hand::remove(Card *card) {
    for (int i = 0; i<cards.size(); i++){
        if(cards.at(i)==card){
            cards.at(i)->setHand(nullptr);
            cards.erase(cards.begin()+i);
            break;
        }
    }
}

vector<Card*>* Hand::getHand(){
    return &cards;
}
