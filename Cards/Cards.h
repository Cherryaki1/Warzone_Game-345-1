#ifndef CARDS_H
#define CARDS_H
using namespace std;

#include <string>
#include <vector>


class Card {
    int cardID; // 1. bomb, 2. reinforcement, 3. blockade, 4. airlift, 5. diplomacy.
public:
    bool play();
private:
};

class Deck {
    vector<Card> cards;
public:
    bool draw();

private:
};

class Hand {
    vector<Card> cards;
public:

private:
};


#endif