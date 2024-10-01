#include "Player.h"
#include <iostream>
using namespace std;

void testPlayers() {
    // Creating a player using the default constructor
    Player player1;
    cout << "Player 1 (default): " << player1 << endl;

    // Creating a player using the overloaded constructor
    Player player2("Alice");
    cout << "Player 2 (overloaded constructor): " << player2 << endl;

    // Using the setPlayerName method
    player1.setPlayerName("Bob");
    cout << "Player 1 (after setPlayerName): " << player1 << endl;

    // Demonstrating the copy constructor
    Player player3 = player2;  // Invokes copy constructor
    cout << "Player 3 (copy of Player 2): " << player3 << endl;

    // Demonstrating the assignment operator
    player1 = player2;  // Invokes assignment operator
    cout << "Player 1 (after assigning Player 2 to it): " << player1 << endl;

    // Demonstrating self-assignment (should not cause any issues)
    player1 = player1;
    cout << "Player 1 (after self-assignment): " << player1 << endl;

    // Destructor will be called automatically when player objects go out of scope
}


