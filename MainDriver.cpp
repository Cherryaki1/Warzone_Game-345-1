#include <iostream>
#include "MainDriver.h"
//#include "GameEngine.h"
#include "MapDriver.h"
#include "Player.h"
using namespace std;

extern void testCard();

int main() {
  testLoadMap();
}
// Main Class
/*
int main(){
  //testGameStates();
  //testPlayers();
  //testCard();

  // WELCOME MESSAGE
  cout << "**** Welcome to our CLI Warzone! ****" << endl;

  // PROMPT FOR MAP SELECTION
  while(menuLoop) {
    cout << "To begin, choose your map...  Map 1: Test , Map 2: Canada, Map 3: Invalid" << endl;
    cout << "Enter the number of the map as your choice: ";
    cin >> chosenMap;
    switch(chosenMap) {
      case 1:
        mapName = "Test.txt";
      // Load map passing the name and returning boolean value
      cout << mapName << " successfully loaded..." << endl;
      menuLoop = false;
      break;
      case 2:
        mapName = "Canada.txt";
      // Load map passing the name and returning boolean value
      cout << mapName << " successfully loaded." << endl;
      menuLoop = false;
      break;
      case 3:
        mapName = "Invalid.txt";
        // Load map passing the name and returning boolean value
        cout << mapName << " successfully loaded..." << endl;
        menuLoop = false;
        break;
      default: cout << "Invalid choice! Try Again" << endl;
    }

    // PROMPT FOR PLAYERS START UP
    cout << "Enter the number of players (MAX: 4): ";
    cin >> numOfPlayers;
    switch(numOfPlayers) {
      case 1:
        cout << "You need more players!" << endl;
      break;
      case 2:
        cout << "2 Players chosen! Do stuff..." << endl;
      break;
      case 3:
        cout << "3 Players chosen! Do stuff..." << endl;
      break;
      case 4:
        cout << "4 Players chosen! Do stuff..." << endl;
      break;
      default: cout << "Invalid choice! Try Again" << endl;
    }
  }



  return 0;
}
*/
