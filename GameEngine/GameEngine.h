#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <string>
using std::string;



class StartUp {
    private:
    string* command;
    bool* invalidCommand;
    public:
    StartUp();
    ~StartUp(); // Destructor

    // PHASE
    bool startUpPhase();

    // SETTERS ANG GETTERS FOR STARTUP
    string getCommand() const;
    void setCommand(const string& cmd);
    bool getInvalidCommand()const;
    void setInvalidCommand(bool value);
};

class Play {
    private:
    string* command;
    bool* invalidCommand;
    public:
    Play();
    ~Play(); // Destructor

    // PHASES
    bool reinforcementPhase();
    bool ordersIssuingPhase();
    string ordersExecutionPhase();
    bool endPhase();

    // SETTERS AND GETTERS FOR PLAY
    string getCommand() const;
    void setCommand(const string& cmd);
    bool getInvalidCommand()const;
    void setInvalidCommand(bool value);
};

void testGameStates();
#endif

