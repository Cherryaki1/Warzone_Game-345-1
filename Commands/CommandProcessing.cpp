#include "CommandProcessing.h"

// Command methods
Command::Command(const string& commandText)
    : commandText(new string(commandText)), effect(new string("")) {}

Command::~Command() {
    delete commandText;  // Clean up allocated memory for commandText
    delete effect;       // Clean up allocated memory for effect
}

void Command::saveEffect(const string& effectText) {
    *effect = effectText;  // Set the effect value
    notify(this);          // Notify observers after saving the effect
}

string Command::getCommandText() const {
    return *commandText;  // Dereference to access the actual string value
}

string Command::stringToLog() {
    return "Command: " + *commandText + "\nCommand's Effect: " + *effect;
}

std::ostream& operator<<(std::ostream& os, const Command& cmd) {
    os << "Command: " << *cmd.commandText;
    if (cmd.effect) os << ", Effect: " << *cmd.effect;
    return os;
}

// CommandProcessor methods
CommandProcessor::CommandProcessor() {}

CommandProcessor::~CommandProcessor() {
    for (Command* cmd : commands) delete cmd;
}

void CommandProcessor::readCommand() {
    string commandText;
    std::cout << "Enter command:";
    std::getline(std::cin, commandText);
    saveCommand(commandText);
}

void CommandProcessor::saveCommand(const string& commandText) {
    Command* command = new Command(commandText);
    commands.push_back(command);
    validate(command);
    notify(this);
}

vector<Command*>* CommandProcessor::getCommands() {
    return &commands;
}

Command* CommandProcessor::getCommand() {
    readCommand();
    return commands.back();
}

bool CommandProcessor::validate(Command* command, string& state) {
    string commandText = command->getCommandText();
    //    std::cout << commandText << std::endl;
    bool isValid = false;

    if (commandText.substr(0,7) == "loadmap" && (state == "start" || state == "maploaded")) {
        //        string fileName = commandText.substr(9);
        isValid = true;
        //std::cout << "Loaded map at " << commandText << std::endl;
        command->saveEffect("Loads a map");
    } else if (commandText == "validatemap" && state == "maploaded" ) {
        isValid = true;
        //std::cout << "Validated Map" << std::endl;
        command->saveEffect("Validates a map");
    } else if (commandText.substr(0,9) == "addplayer" && (state == "mapvalidated" || state == "playersadded")) {
        //        string playerName = commandText.substr(11);
        isValid = true;
        //std::cout << "Added Player" << std::endl;
        command->saveEffect("Adds a player");
    } else if (commandText == "gamestart" && state == "playersadded") {
        isValid = true;
        //std::cout << "Game Start" << std::endl;
        command->saveEffect("Starts the game");
    } else if (commandText == "replay" && state == "win") {
        isValid = true;
        command->saveEffect("Replays");
    } else {
        command->saveEffect("Invalid command in the current state.");
    }

    return isValid;
}

bool CommandProcessor::validate(Command* command) {
    string commandText = command->getCommandText();
//    std::cout << commandText << std::endl;
    bool isValid = false;

    if (commandText.substr(0,7) == "loadmap") {
//        string fileName = commandText.substr(9);
        std::cout << "Loaded map at " << commandText << std::endl;
        isValid = true;

        command->saveEffect("Loads a map");
    } else if (commandText == "validatemap") {
        isValid = true;
        std::cout << "Validated Map" << std::endl;
        command->saveEffect("Validates a map");
    } else if (commandText.substr(0,9) == "addplayer") {
//        string playerName = commandText.substr(11);
        std::cout << "Added Player" << std::endl;
        isValid = true;
        command->saveEffect("Adds a player");
    } else if (commandText == "gamestart") {
        std::cout << "Game Start" << std::endl;
        isValid = true;
        command->saveEffect("Starts the game");
    } else {
        command->saveEffect("Invalid command in the current state.");
    }

    return isValid;
}

/*
std::string CommandProcessor::nextGameState(const std::string& currentState, const std::string& commandText) {
    // Define your state transition logic here
    if (commandText.substr(0,7) == "loadmap") return "maploaded";
    if (commandText == "validatemap") return "mapvalidated";
    if (commandText.substr(0,9) == "addplayer") return "playersadded";
    if (commandText == "gamestart") return "endOfStartUp (type \"end\" to finish startUp)";
    return currentState;
}*/

string CommandProcessor::stringToLog() {
    return commands.back()->stringToLog();
}

std::ostream& operator<<(std::ostream& os, const CommandProcessor& cp) {
    os << "CommandProcessor with " << cp.commands.size() << " commands:\n";
    for (const Command* cmd : cp.commands) {
        os << *cmd << "\n";
    }
    return os;
}

// FileCommandProcessorAdapter methods
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const string& filename) {
    fileStream.open(filename);
    if (!fileStream.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
    if (fileStream.is_open()) {
        fileStream.close();
    }
}

void FileCommandProcessorAdapter::readCommand() {
    if (fileStream.is_open()) {
        string commandText;
        if (std::getline(fileStream, commandText)) {
            saveCommand(commandText);
        } else {
            std::cerr << "End of command file reached or read error occurred." << std::endl;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const FileCommandProcessorAdapter& fcp) {
    os << "FileCommandProcessorAdapter reading from file:\n";
    os << static_cast<const CommandProcessor&>(fcp);  // Reuse base class operator<<
    return os;
}



