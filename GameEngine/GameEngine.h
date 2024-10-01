#ifndef GAMEENGINE_H
#define GAMEENGINE_H

class StartUp {
    public:
    static bool startUpPhase();
};

class Play {
    public:
    static bool reinforcementPhase();
    static bool ordersIssuingPhase();
    static bool ordersExecutionPhase();
    static bool endPhase();
};
#endif

