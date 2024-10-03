#include <iostream>
#include <fstream>
#include <string>
#include "MainDriver.h"
//#include "GameEngine.h"
#include "MapDriver.h"
#include "Player.h"
#include "Orders.h"
using namespace std;

extern void testCards();

// Main Class

int main(){
  //testLoadMap();
  //testGameStates();
  //testPlayers();
  //testOrdersLists();
  //testCards();

  // WELCOME MESSAGE
  cout << "**** Welcome to our CLI Warzone! ****" << endl;

  // PROMPT FOR MAP SELECTION
  while(menuLoop) {
    cout << "To begin, choose your map...  Map 1: Test , Map 2: World 2007, Map 3: InvalidPlaceHolder" << endl;
    cout << "Enter the number of the map as your choice: ";
    cin >> chosenMap;
    cout << chosenMap << endl;
    switch(chosenMap) {
      case 1:
        mapName = "Test.txt";
      // Load map passing the name and returning boolean value
      cout << mapName << " successfully loaded..." << endl;
      menuLoop = false;
      break;
      case 2:
        mapName = "World 2007.map";
      // Load map passing the name and returning boolean value
      cout << mapName << " successfully loaded." << endl;
      menuLoop = false;
      break;
      case 3:
        mapName = "InvalidPlaceHolder.txt";
      // Load map passing the name and returning boolean value
      cout << mapName << " successfully loaded..." << endl;
      menuLoop = false;
      break;
      default: cout << "Invalid choice! Try Again" << endl;
    }
  }

  menuLoop = true;

  while(menuLoop) {
    // PROMPT FOR PLAYERS START UP
    cout << "Enter the number of players (MAX: 4): ";
    cin >> numOfPlayers;
    switch(numOfPlayers) {
      case 1:
        cout << "You need more players!" << endl;
      break;
      case 2:
        cout << "2 Players chosen! Do stuff..." << endl;
      menuLoop = false;
      break;
      case 3:
        cout << "3 Players chosen! Do stuff..." << endl;
      menuLoop = false;
      break;
      case 4:
        cout << "4 Players chosen! Do stuff..." << endl;
      menuLoop = false;
      break;
      default: cout << "Invalid choice! Try Again" << endl;
    }
  }

  // MAX 32 CONTINENTS
  // MAX 10 ADJACENT TERRITORIES
  // MAX 255 TERRITORIES

  return 0;
}




