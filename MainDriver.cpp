// Arturo Sanchez Escobar (40283236), Team 36
// Abdulah Ghulam Ali (40281857), Team 36
// Amir Vala Khalilzadeh (40253211), Team 36
// Gregory Lajoie (ID), Team 36
// Botao Yang (ID), Team 36
// COMP 345 - D (Advanced Program Design, C++)
// Warzone Game Team Project - Assignment 1
// October 4, 2024
// *******************************************
// This is a cpp file which tests all parts of the assignment
// This file runs all the test methods created to test each part of the assignment, a menu has also been implemented

#include <iostream>
#include <fstream>
#include <string>
#include "MainDriver.h"
#include "GameEngine.h"
#include "Player.h"
#include "Orders.h"
#include "Cards.h"
#include "MapDriver.h"
#include "Commands/CommandProcessing.h"

using namespace std;

// Main Class
int main(){
  // Assignment 1
  //testLoadMap();
  //testGameStates();
  //testPlayers();
  //testOrdersLists();
  //testCards();

  // Assignment Part 2
  //testCommandProcessor();
  /*testLoadMap();
  testGameStates();
  testPlayers();
  testOrdersLists();
  testCards();


  // WELCOME MESSAGE
  cout << "**** Welcome to our CLI Warzone! ****" << endl;




  /*
  // PROMPT FOR MAP SELECTION
  while(menuLoop) {
    cout << "To begin, choose your map...  Map 1: Test , Map 2: World 2007 (Invalid), Map 3: Europe 4B/" << endl;
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
        mapName = "Europe 4B.map";
      // Load map passing the name and returning boolean value
      cout << mapName << " successfully loaded..." << endl;
      menuLoop = false;
      break;
      default: cout << "Invalid choice! Try Again" << endl;
    }
  }
  */

  // MAX 32 CONTINENTS
  // MAX 10 ADJACENT TERRITORIES
  // MAX 255 TERRITORIES

  return 0;
}




