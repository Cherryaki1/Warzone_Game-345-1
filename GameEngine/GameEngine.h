#ifndef GAMEENGINE_H
#define GAMEENGINE_H

class GameEngine {
    public:
    // Phases of the game
    static bool startUpPhase();
    bool reinforcementPhase();
    bool ordersIssuingPhase();
    bool ordersExecutionPhase();
    bool endPhase();
    private:
    // Something maybe
};
#endif

