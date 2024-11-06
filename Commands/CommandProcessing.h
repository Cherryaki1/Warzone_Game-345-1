
#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H

#include <string>
#include <vector>
#include <list>
#include "LogObserver/LoggingObserver.h"

using std::string;
using std::vector;
using std::list;

class Command: public Subject, ILoggable{
private:
    string effect;
    string command;
public:
    void saveEffect();
};

class CommandProcessor: public Subject, ILoggable{
private:
    vector<Command*> commands;
    void readCommand();
public:
    string getCommand();
    void validate();
};




#endif //COMMANDPROCESSING_H
