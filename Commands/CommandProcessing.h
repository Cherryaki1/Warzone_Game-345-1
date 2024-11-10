
#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include "LogObserver/LoggingObserver.h"

using std::string;
using std::vector;
using std::list;

class Command : public Subject, public ILoggable {
private:
    string commandText;
    string effect;

public:
    Command(const string& commandText) : commandText(commandText) {}
    void saveEffect(const string& effect) {
        this->effect = effect;
        notify(this);  // Notify observers after saving the effect
    }
    string getCommandText() const { return commandText; }

    string stringToLog() const override {
        return "Command: " + commandText + ", Effect: " + effect;
    }
};

class CommandProcessor : public Subject, public ILoggable {
private:
    vector<Command*> commands;
    virtual void readCommand();

public:
    CommandProcessor() {}
    virtual ~CommandProcessor() {
        for (Command* cmd : commands) delete cmd;
    }
    Command* getCommand();
    void saveCommand(const string& commandText);
    void validate(Command* command);
    string stringToLog() const override;

    // Deleted copy constructor and assignment operator
    CommandProcessor(const CommandProcessor&) = delete;
    CommandProcessor& operator=(const CommandProcessor&) = delete;
};

class FileCommandProcessorAdapter : public CommandProcessor {
private:
    std::ifstream fileStream;

protected:
    void readCommand() override;

public:
    FileCommandProcessorAdapter(const string& filename);
    ~FileCommandProcessorAdapter();
    void processFileCommands() {
        readCommand();
    }
};

// Free Function
void testCommandProcessor();




#endif //COMMANDPROCESSING_H
