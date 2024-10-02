#include "Cards.h"
#include <iostream>
using namespace std;



void testCards(){
    // Create a deck of cards

    Deck *myDeck = new Deck();
    cout << "Deck created. Default deck contains 50 cards, 10 of each type - here are the card details:\n";
    myDeck->summarize();
    Hand *myHand = new Hand();
    for(int i = 0 ; i< 9; i++){
        myHand->place(myDeck->draw());
    }
    myHand->display();

    cout << "Deck now:\n";
    myDeck->summarize();

    cout<<"Playing the hand...";
    for(int i = 0; i<myHand->getHand()->size(); i++){
        Card* thisCard = myHand->getHand()->at(i);
        thisCard->play();
        myHand->remove(thisCard);
        i--;
    }


    cout << "Deck now:\n";
    myDeck->summarize();

    myHand->display();

//    cout << "Drawing a card...\n";
//    Card* drawnCard = myDeck->draw();
//    cout << "Drew this card: ";
//    drawnCard->displayCard();
//    cout << "Remaining...\n";
//    myDeck->display();
}