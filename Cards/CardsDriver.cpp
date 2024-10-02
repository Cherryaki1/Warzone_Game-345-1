#include "Cards.h"
#include <iostream>
using namespace std;

void testCard(){
    srand(time(0));
    for(int i = 0; i< 10; i++){
        Card *thisCard = new Card();
        cout << i <<" ";
        thisCard->displayCard();
        delete thisCard;
    }
}