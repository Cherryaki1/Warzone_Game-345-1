// Amir Vala Khalilzadeh (40253211), Team 36
// COMP 345 - D (Advanced Program Design, C++)
// Warzone Game Team Project - Assignment 1
// October 4, 2024
// *******************************************
// This is a cpp file for Part 4 of the assignment.
// It contains the class and function implementations for Card, Deck, and Hand

#include <iostream>
#include "Cards.h"
#include "vector"
using namespace std;

vector<string> cardTypeLookup = {"Bomb", "Reinforcement", "Blockade", "Airlift", "Diplomacy"}; //Vector for seamless lookup of card types

//**************************CARDS**************************
Card::Card() { //Default constructor with a random card type
    setRandomType();
}
Card::Card(int type, Deck* origin) { //Constructor that takes a type and originating deck pointer
    if(type<cardTypeLookup.size()){ //If the given card type index is valid, give the card the type and assign the originating deck ptr
        this->type = new string(cardTypeLookup[type]);
        this->origin = origin;
        this->cardTypeID = new int(type);  // Initialize with given type
    } else {
        cout << type << " is not a correct card type!\n";
        this->cardTypeID = nullptr;  // Set to nullptr if invalid
    }
}
Card::~Card() { //Destructor
    if (type != nullptr) delete type;
    if (cardTypeID != nullptr) delete cardTypeID;
    origin = nullptr; //Nullifies the originating deck pointer
    hand = nullptr; //Nullifies the owning hand pointer
}
Card::Card(const Card &other){
    delete type; //Deletes the card type pointer
    type = nullptr;
    if (cardTypeID) {  // Check if cardTypeID is not nullptr
        delete cardTypeID;
        cardTypeID = nullptr; // Set to nullptr after deletion
    }
    origin=other.origin;
    hand=other.hand;
}

ostream& operator<<(ostream &os, const Card* card){ //Stream insertion operator - displays a card
    os << *card->type << " card\n";
    return os;
}

string Card::getType() { //Returns the type of the card
    return *this->type;
}

void Card::setRandomType() { //Randomly generates number from 0-4 and uses it to assign a random type
    int typeID = rand()%5;
    this->cardTypeID = new int(typeID);
    this->type = new string(cardTypeLookup[typeID]);
}

void Card::setHand(Hand *hand) { //Assigns a owning hand ptr to a card
    this->hand = hand;
}

void Card::play() {
    cout << "\t" << this->getType() << " card played\n";

    // Return the card to the deck and remove it from the player's hand
    this->origin->returnToDeck(this);  // Returns card to deck
    this->hand->remove(this);  // Removes card from the player's hand
}


//**************************DECK**************************
Deck::Deck() { srand(time(0)); initialize();} //Constructs a deck, using the initialize() function to do so.
Deck::~Deck() { //Destroys a deck, going through each card pointer and deleting it
    for (int i = 0; i<cards.size(); i++){
        delete cards.at(i);
    }
}
Deck::Deck(const Deck &other){
    for(int i = 0; i<other.cards.size(); i++){
        this->cards.push_back(new Card(*other.cards.at(i)));
    }
}

void Deck::initialize() { //Creates a default number of cards for the deck
    int numCards = 50;
    //50 cards, 10 of each type by default
    for (int i = 0; i<cardTypeLookup.size(); i++){
        for (int j=0; j < numCards / cardTypeLookup.size(); j++){
            cards.push_back(new Card(i, this));
        }
    }
}

void Deck::returnToDeck(Card *card) { //Returns a card pointer to the deck
    cards.push_back(card);
}
ostream& operator<<(ostream &os, const Deck* deck) { //Displays each card by iterating through the deck and printing each card.
    for (int i = 0 ; i<deck->cards.size(); i++){
        os << (i+1) << ": " << deck->cards.at(i);
    }
    return os;
}
void Deck::summarize(){ //Summarizes the deck by displaying the number of cards by type
    for (int i = 0; i<cardTypeLookup.size(); i++){
        int counter = 0;
        for(int j = 0; j<cards.size(); j++){
            if(cards.at(j)->getType()==cardTypeLookup.at(i)) counter++;
        }
        cout << "\t" << counter << " " <<cardTypeLookup.at(i) << " cards\n";
    }
}

Card* Deck::draw() { //Randomly draws from the deck of cards, returns the pointer to that card and removes it from the deck
    int index = rand()%(cards.size());
    Card* drawn = cards.at(index);
    cards.erase(cards.begin()+index);
    return drawn;
}

//**************************HAND**************************
Hand::Hand(Player* player) : owner(player) {}
Hand::~Hand() {}
Hand::Hand(const Hand &other){
    for(int i = 0; i<other.cards.size(); i++){
        Card *newCard = new Card(*other.cards.at(i)) ;
        newCard->setHand(this);
        this->cards.push_back(newCard);
    }
}

ostream& operator<<(ostream &os, const Hand* hand) { //Displays each card by iterating through the hand and calling Cards::display() for each.
    cout << "Cards in your hand: ("<< hand->cards.size() <<")\n";
    for (int i = 0; i<hand->cards.size(); i++){
        os << "\t" <<i+1 << ": " << hand->cards.at(i) << "";
    }
    return os;
}

void Hand::place(Card* card){ //Places the given card pointer into the hand
    cards.push_back(card);
    card->setHand(this);
}

void Hand::remove(Card *card) { //Removes card from hand by going through the hand until there is a match, then removing it.
    for (int i = 0; i<cards.size(); i++){
        if(cards.at(i)==card){
            cards.at(i)->setHand(nullptr);
            cards.erase(cards.begin()+i);
            break;
        }
    }
}

vector<Card*>* Hand::getHand(){ //Returns a pointer to the hand's card vector
    return &cards;
}

bool Hand::hasCard(string cardType) { //Checks if the hand has a card of a certain type
    for (int i = 0; i<cards.size(); i++){
        if(cards.at(i)->getType()==cardType) return true;
    }
    return false;
}

Player* Hand::getOwner() {
    return owner;
}


