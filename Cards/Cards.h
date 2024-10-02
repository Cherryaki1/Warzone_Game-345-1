#ifndef CARDS_H
#define CARDS_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Deck;
class Hand;

class Card {
public:
    Card();
    ~Card();
    explicit Card(int type, Deck* origin);
    Card(string type);
    void setHand(Hand* hand);
    string getType();
    int getTypeID();
    void play();
    void setRandomType();
    void displayCard();
private:
    int* cardID; // 1. bomb, 2. reinforcement, 3. blockade, 4. airlift, 5. diplomacy.
    string* type;
    Deck* origin;
    Hand* hand;
};

class Deck {
public:
    Deck();
    ~Deck();
    void shuffle();
    void initialize();
    void returnToDeck(Card* card);
    Card* draw();
    void display();
    void summarize();
private:
    vector<Card*> cards;
};

class Hand {
public:
    Hand();
    ~Hand();
    void display();
    void place(Card* card);
    void remove(Card* card);
    vector<Card*>* getHand();
private:
    vector<Card*> cards;
};


#endif