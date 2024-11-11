
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
    string* commandText;
    string* effect;

public:
    Command(const string& commandText);
    ~Command();

    void saveEffect(const string& effect);

    string getCommandText() const;

    string stringToLog() override;
};

class CommandProcessor : public Subject, public ILoggable {
private:
    vector<Command*> commands;
    virtual void readCommand();

    public:
    CommandProcessor();
    ~CommandProcessor() override;
    vector<Command*>* getCommands();
    void saveCommand(const string& commandText);
    void validate(Command* command);
    string stringToLog() override;

    void processCommands() {
        readCommand();
    }
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
};

// Free Function
void testCommandProcessor();

#endif //COMMANDPROCESSING_H
