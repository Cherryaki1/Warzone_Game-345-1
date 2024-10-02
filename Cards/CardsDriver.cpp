#include "Cards.h"
#include <iostream>
using namespace std;



void testCards(){
    // Create a deck of cards

    Deck *myDeck = new Deck();
    cout << "Deck created. Default deck contains 50 cards, 10 of each type - here are the card details:\n";
    myDeck->display();
    cout << "Drawing a card...\n";
    Card* drawnCard = myDeck->draw();
    cout << "Drew this card: ";
    drawnCard->displayCard();
    cout << "Remaining...\n";
    myDeck->display();
}