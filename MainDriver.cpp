// Arturo Sanchez Escobar (40283236), Team 36
// Abdulah Ghulam Ali (40281857), Team 36
// Amir Vala Khalilzadeh (40253211), Team 36
// Gregory Lajoie (40276231), Team 36
// Botao Yang (40213554), Team 36
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
extern void testLoggingObserver();
extern void testOrderExecution();
extern void testPlayerStrategies();
extern void testTournament();

// Main Class
int main(){

  // ************** Assignment 1 **************
  //testLoadMap("Test.txt");
  //testGameStates();
  //testPlayers();
  //testOrdersLists();s
  //testCards();


  // ************** Assignment Part 2 **************
  // testCommandProcessor();     // Part 1
  //testStartUpPhase();         // Part 2
//  testMainGameLoop();      // Part 3
  //testOrderExecution();       //Part 4
  //testLoggingObserver();      //Part 5

  // ************** Assignment 3 **************
    //testPlayerStrategies();
    testTournament();




  return 0;
}




