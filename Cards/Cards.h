#ifndef CARDS_H
#define CARDS_H
using namespace std;

#include <string>
#include <vector>


class Card {
public:
    Card();
    ~Card();
    Card(int type);
    Card(string type);
    void setType(int type);
    void setType(string type);
    string getType();
    int getTypeID();
    bool play();
private:
    int* cardID; // 1. bomb, 2. reinforcement, 3. blockade, 4. airlift, 5. diplomacy.
    string* type;
};

class Deck {
public:
    Deck();
    ~Deck();
    void shuffle();
    void initialize(int numCards);
    void initialize();
    Card* draw();
private:
    vector<Card>* cards;
    int* numCards;
};

class Hand {
public:
    Hand();
    ~Hand();
    void addToHand(Card* card);
private:
    vector<Card>* cards;
};


#endif