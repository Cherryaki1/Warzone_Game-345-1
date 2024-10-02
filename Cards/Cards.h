#ifndef CARDS_H
#define CARDS_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Card {
public:
    Card();
    ~Card();
    explicit Card(int type);
    Card(string type);
//    void setType(int type);
//    void setType(string type);
    string getType();
    int getTypeID();
    bool play();
    void setRandomType();
    void displayCard();
private:
    int* cardID; // 1. bomb, 2. reinforcement, 3. blockade, 4. airlift, 5. diplomacy.
    string* type;
};

class Deck {
public:
    Deck();
    ~Deck();
    void shuffle();
    void initializeRand(int numCards);
    void initialize();
    void returnToDeck(Card* card);
    Card* draw();
    void display();
private:
    vector<Card*> cards;
    int* numCards;
};

class Hand {
public:
    Hand();
    ~Hand();
//    void draw(Deck* deck);
    void display();
    void place(Card* card);

private:
    vector<Card*> cards;
};


#endif