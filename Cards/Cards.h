// Amir Vala Khalilzadeh (40253211), Team 36
// COMP 345 - D (Advanced Program Design, C++)
// Warzone Game Team Project - Assignment 1
// October 4, 2024
// *******************************************
// This is a header file for Part 4 of the assignment.
// It contains the class and function signatures/declarations for Card, Deck, and Hand

#ifndef CARDS_H
#define CARDS_H

#include <string>
#include <vector>
#include "Player/Player.h"

using std::string;
using std::vector;

class Deck; //Pre-declaring Deck and Hand classes to be used in the Card class
class Hand;

class Card {
public:
    Card(); //Default constructor
    ~Card(); //Destructor
    explicit Card(int type, Deck* origin); //Parameter constructor (we always use this one)
    void setHand(Hand* hand); //Setter for the owning hand pointer of a Card
    string getType(); //Getter for the type of the card
    void play(); //Function for playing the card: issues the respective order, removes the card from hand and places it back in the deck
    void setRandomType(); //For potential use later: randomly sets the card type
    void displayCard(); //Prints out the card's information in a friendly manner
private:
    int* cardTypeID; // 1. bomb, 2. reinforcement, 3. blockade, 4. airlift, 5. diplomacy.
    string* type; //Type of the card (see above comment)
    Deck* origin; //Deck that the card originated from
    Hand* hand; //Hand that the card belongs to
};

class Deck {
public:
    Deck(); //Default constructor
    ~Deck(); //Destructor
    void initialize(); //Initializes deck for first use
    void returnToDeck(Card* card); //Returns a card to the deck
    Card* draw(); //Draws from the card and returns a card ptr
    void display(); //Displays all cards in the deck (one by one)
    void summarize(); // Displays the number of cards by type
private:
    vector<Card*> cards; //Vector of card pointers
};

class Hand {
public:
    Hand(Player* player); //Default constructor
    ~Hand(); //Destructor
    void display(); //Displays all cards in the hand
    void place(Card* card); //Places a card ptr into the hand
    void remove(Card* card); //Removes a card ptr from the hand
    vector<Card*>* getHand(); //Returns a ptr to the hand's cards vector
    Player* getOwner();

private:
    vector<Card*> cards; //Vector of card pointers
    Player* owner; // the player that owns the card
};

#endif //CARDS_H