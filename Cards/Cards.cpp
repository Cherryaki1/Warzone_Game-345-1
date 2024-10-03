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
    } else {
        cout << type << " is not a correct card type!\n";
    }
}
Card::~Card() { //Destructor
    delete type; //Deletes the card type pointer
    delete cardTypeID; //Deletes the card type ID pointer
    origin = nullptr; //Nullifies the originating deck pointer
    hand = nullptr; //Nullifies the owning hand pointer
}
string Card::getType() { //Returns the type of the card
    return *this->type;
}

void Card::setRandomType() { //Randomly generates number from 0-4 and uses it to assign a random type
    int typeID = rand()%5;
    this->type = new string(cardTypeLookup[typeID]);
}

void Card::setHand(Hand *hand) { //Assigns a owning hand ptr to a card
    this->hand = hand;
}

void Card::play() { //Creates the corresponding order of the card, removes it from Player's hand and returns it to the deck
    // PLAY THE CARD, special order etc.
    cout << "\t" <<this->getType() << " card played\n";
    this->origin->returnToDeck(this); //Returns card to deck
    this->hand->remove(this);
}
void Card::displayCard() { //Displays the card's type in a friendly manner
    cout << "This is a " << *type << " card!\t\n";
}

//**************************DECK**************************
Deck::Deck() { initialize();} //Constructs a deck, using the initialize() function to do so.
Deck::~Deck() { //Destroys a deck, going through each card pointer and deleting it
    for (int i = 0; i<cards.size(); i++){
        delete cards.at(i);
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
void Deck::display() { //Displays each card by iterating through the deck and calling Cards::display() for each.
    for (int i = 0 ; i<cards.size(); i++){
        cout << (i+1) << ": ";
        cards.at(i)->displayCard();
    }
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
    srand(time(0));
    int index = rand()%(cards.size());
    Card* drawn = cards.at(index);
    cards.erase(cards.begin()+index);
    return drawn;
}

//**************************HAND**************************
Hand::Hand() {}
Hand::~Hand() {}

void Hand::display() { //Displays each card by iterating through the hand and calling Cards::display() for each.
    cout << "Cards in your hand: ("<< cards.size() <<")\n";
    for (int i = 0; i<cards.size(); i++){
        cout << "\t" <<i+1 << ": ";
        cards.at(i)->displayCard();
    }
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
