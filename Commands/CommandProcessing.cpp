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
    return "Command: " + *commandText + ", Effect: " + *effect;
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
}

vector<Command*>* CommandProcessor::getCommands() {
    return &commands;
}

void CommandProcessor::validate(Command* command) {
    string commandText = command->getCommandText();
    std::cout << commandText << std::endl;
    bool isValid = false;

    if (commandText.substr(0,7) == "loadmap") {
        string fileName = commandText.substr(9);
        isValid = true;
        command->saveEffect("Map loaded successfully.");
    } else if (commandText == "validatemap") {
        isValid = true;
        command->saveEffect("Map validated successfully.");
    } else if (commandText.substr(0,9) == "addplayer") {
        string playerName = commandText.substr(11);
        isValid = true;
        command->saveEffect("Player added successfully.");
    } else if (commandText == "gamestart") {
        isValid = true;
        command->saveEffect("Game started successfully.");
    } else {
        command->saveEffect("Invalid command in the current state.");
    }

    if (!isValid) {
        notify(this);  // Notify about invalid command
    }
}

string CommandProcessor::stringToLog() {
    return commands.empty() ? "No commands processed yet." : commands.back()->stringToLog();
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