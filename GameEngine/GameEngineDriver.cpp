# include <iostream>
# include "GameEngine.h"
#include "GameEngineDriver.h"

void testGameStates() {
    if(GameEngine::startUpPhase() == true) {
        std::cout << "Game Engine StartUpPhase Called" << std::endl;
    }
}