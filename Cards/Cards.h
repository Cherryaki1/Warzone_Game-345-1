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
    int cardID; // 1. bomb, 2. reinforcement, 3. blockade, 4. airlift, 5. diplomacy.

};

class Deck {

public:
    void initailize();
    bool draw();
private:
    vector<Card>* cards;
};

class Hand {
public:
private:
    vector<Card>* cards;
};


#endif