#include "Cards.h"
#include <iostream>
using namespace std;



void testCards(){
    // Create a deck of cards

    Deck *myDeck = new Deck();
    cout << "Deck created. Default deck contains 50 cards, 10 of each type - here are the card details:\n";
    myDeck->summarize();
    Hand *myHand = new Hand(new Player("bob"));
    for(int i = 0 ; i< 9; i++){
        myHand->place(myDeck->draw());
    }
    cout << myHand;

    cout << "Deck now:\n";
    myDeck->summarize();

    cout<<"Playing the hand...\n";
    for(int i = 0; i<myHand->getHand()->size(); i++){
        Card* thisCard = myHand->getHand()->at(i);
        thisCard->play();
        i--;
    }

    cout << "Deck now:\n";
    myDeck->summarize();
    cout << myHand;
}