/**
 * @file GameEngine.cpp
 * @brief This file contains the class and function implementations for the GameEngine.
 * 
 * This file is part of the Warzone Game Team Project for COMP 345 - D (Advanced Program Design, C++).
 * It contains the class and function implementations for Card, Deck, and Hand.
 * 
 * Team Members (Team 36):
 * - Amir Vala Khalilzadeh (40253211)
 * - Abdulah Ghulam Ali (40281857)
 * - Arturo Sanchez Escobar (40283236)
 * - Gregory Lajoie (40276231)
 * - Botao Yang (40213554)
 */
#include <iostream>
#include "Cards.h"
#include "vector"
using namespace std;

vector<string> cardTypeLookup = {"Bomb", "Reinforcement", "Blockade", "Airlift", "Diplomacy"}; //Vector for seamless lookup of card types

//**************************CARDS**************************

/**
 * @class Card
 * @brief Represents a card in the game.
 */

/**
 * @brief Default constructor for the Card class.
 * Initializes the card with a random type.
 */
Card::Card() { //Default constructor with a random card type
    setRandomType();
}

/**
 * @brief Parameterized constructor for the Card class.
 * @param type The type of the card.
 * @param origin The originating deck pointer.
 */
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

/**
 * @brief Destructor for the Card class.
 */
Card::~Card() { //Destructor
    if (type != nullptr) delete type;
    if (cardTypeID != nullptr) delete cardTypeID;
    origin = nullptr; //Nullifies the originating deck pointer
    hand = nullptr; //Nullifies the owning hand pointer
}

/**
 * @brief Copy constructor for the Card class.
 * @param other The Card object to copy from.
 */
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

/**
 * @brief Stream insertion operator for displaying a card.
 * @param os The output stream.
 * @param card The card to display.
 * @return The output stream.
 */
ostream& operator<<(ostream &os, const Card* card){ //Stream insertion operator - displays a card
    os << *card->type << " card\n";
    return os;
}

/**
 * @brief Gets the type of the card.
 * @return The type of the card.
 */
string Card::getType() { //Returns the type of the card
    return *this->type;
}

/**
 * @brief Sets a random type for the card.
 */
void Card::setRandomType() { //Randomly generates number from 0-4 and uses it to assign a random type
    int typeID = rand()%5;
    this->cardTypeID = new int(typeID);
    this->type = new string(cardTypeLookup[typeID]);
}

/**
 * @brief Sets the owning hand pointer for the card.
 * @param hand The owning hand pointer.
 */
void Card::setHand(Hand *hand) { //Assigns a owning hand ptr to a card
    this->hand = hand;
}

/**
 * @brief Plays the card.
 * Issues the respective order, removes the card from hand, and places it back in the deck.
 */
void Card::play() {
    cout << "\t" << this->getType() << " card played\n";

    // Return the card to the deck and remove it from the player's hand
    this->origin->returnToDeck(this);  // Returns card to deck
    this->hand->remove(this);  // Removes card from the player's hand
}

//**************************DECK**************************

/**
 * @class Deck
 * @brief Represents a deck of cards in the game.
 */

/**
 * @brief Default constructor for the Deck class.
 * Initializes the deck using the initialize() function.
 */
Deck::Deck() { srand(time(0)); initialize();} //Constructs a deck, using the initialize() function to do so.

/**
 * @brief Destructor for the Deck class.
 * Deletes each card pointer in the deck.
 */
Deck::~Deck() { //Destroys a deck, going through each card pointer and deleting it
    for (int i = 0; i<cards.size(); i++){
        delete cards.at(i);
    }
}

/**
 * @brief Copy constructor for the Deck class.
 * @param other The Deck object to copy from.
 */
Deck::Deck(const Deck &other){
    for(int i = 0; i<other.cards.size(); i++){
        this->cards.push_back(new Card(*other.cards.at(i)));
    }
}

/**
 * @brief Initializes the deck with a default number of cards.
 */
void Deck::initialize() { //Creates a default number of cards for the deck
    int numCards = 50;
    //50 cards, 10 of each type by default
    for (int i = 0; i<cardTypeLookup.size(); i++){
        for (int j=0; j < numCards / cardTypeLookup.size(); j++){
            cards.push_back(new Card(i, this));
        }
    }
}

/**
 * @brief Returns a card pointer to the deck.
 * @param card The card to return to the deck.
 */
void Deck::returnToDeck(Card *card) { //Returns a card pointer to the deck
    cards.push_back(card);
}

/**
 * @brief Stream insertion operator for displaying a deck.
 * @param os The output stream.
 * @param deck The deck to display.
 * @return The output stream.
 */
ostream& operator<<(ostream &os, const Deck* deck) { //Displays each card by iterating through the deck and printing each card.
    for (int i = 0 ; i<deck->cards.size(); i++){
        os << (i+1) << ": " << deck->cards.at(i);
    }
    return os;
}

/**
 * @brief Summarizes the deck by displaying the number of cards by type.
 */
void Deck::summarize(){ //Summarizes the deck by displaying the number of cards by type
    for (int i = 0; i<cardTypeLookup.size(); i++){
        int counter = 0;
        for(int j = 0; j<cards.size(); j++){
            if(cards.at(j)->getType()==cardTypeLookup.at(i)) counter++;
        }
        cout << "\t" << counter << " " <<cardTypeLookup.at(i) << " cards\n";
    }
}

/**
 * @brief Draws a card from the deck.
 * @return The pointer to the drawn card.
 */
Card* Deck::draw() { //Randomly draws from the deck of cards, returns the pointer to that card and removes it from the deck
    int index = rand()%(cards.size());
    Card* drawn = cards.at(index);
    cards.erase(cards.begin()+index);
    return drawn;
}

//**************************HAND**************************

/**
 * @class Hand
 * @brief Represents a hand of cards in the game.
 */

/**
 * @brief Constructs a Hand object with the given player.
 * @param player The player associated with this hand.
 */
Hand::Hand(Player* player) : owner(player) {}

/**
 * @brief Destructor for the Hand class.
 */
Hand::~Hand() {}

/**
 * @brief Copy constructor for the Hand class.
 * @param other The Hand object to copy from.
 */
Hand::Hand(const Hand &other){
    for(int i = 0; i<other.cards.size(); i++){
        Card *newCard = new Card(*other.cards.at(i)) ;
        newCard->setHand(this);
        this->cards.push_back(newCard);
    }
}

/**
 * @brief Stream insertion operator for displaying a hand.
 * @param os The output stream.
 * @param hand The hand to display.
 * @return The output stream.
 */
ostream& operator<<(ostream &os, const Hand* hand) { //Displays each card by iterating through the hand and calling Cards::display() for each.
    cout << "Cards in your hand: ("<< hand->cards.size() <<")\n";
    for (int i = 0; i<hand->cards.size(); i++){
        os << "\t" <<i+1 << ": " << hand->cards.at(i) << "";
    }
    return os;
}

/**
 * @brief Places a card into the hand.
 * @param card The card to place.
 */
void Hand::place(Card* card){ //Places the given card pointer into the hand
    cards.push_back(card);
    card->setHand(this);
}

/**
 * @brief Removes a card from the hand.
 * @param card The card to remove.
 */
void Hand::remove(Card *card) { //Removes card from hand by going through the hand until there is a match, then removing it.
    for (int i = 0; i<cards.size(); i++){
        if(cards.at(i)==card){
            cards.at(i)->setHand(nullptr);
            cards.erase(cards.begin()+i);
            break;
        }
    }
}

/**
 * @brief Gets the hand's card vector.
 * @return A pointer to the hand's card vector.
 */
vector<Card*>* Hand::getHand(){ //Returns a pointer to the hand's card vector
    return &cards;
}

/**
 * @brief Checks if the hand has a card of a certain type.
 * @param cardType The type of card to check for.
 * @return True if the hand has a card of the specified type, false otherwise.
 */
bool Hand::hasCard(string cardType) { //Checks if the hand has a card of a certain type
    for (int i = 0; i<cards.size(); i++){
        if(cards.at(i)->getType()==cardType) return true;
    }
    return false;
}

/**
 * @brief Gets the owner of the hand.
 * @return A pointer to the owner of the hand.
 */
Player* Hand::getOwner() {
    return owner;
}


