#include "CommandProcessing.h"

// CommandProcessor methods
void CommandProcessor::readCommand() {
    string commandText;
    std::cout << "Enter command: ";
    std::getline(std::cin, commandText);
    saveCommand(commandText);
}

void CommandProcessor::saveCommand(const string& commandText) {
    Command* command = new Command(commandText);
    commands.push_back(command);
    validate(command);
}

Command* CommandProcessor::getCommand() {
    return commands.empty() ? nullptr : commands.back();
}

void CommandProcessor::validate(Command* command) {
    string commandText = command->getCommandText();
    bool isValid = false;

    // Basic validation
    if (commandText == "loadmap") {
        isValid = true;
        command->saveEffect("Map loaded successfully.");
    } else if (commandText == "validatemap") {
        isValid = true;
        command->saveEffect("Map validated successfully.");
    } else if (commandText == "addplayer") {
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

string CommandProcessor::stringToLog() const {
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

// Driver free function
void testCommandProcessor() {
    LogObserver logObserver;
    CommandProcessor consoleProcessor;
    consoleProcessor.attach(&logObserver);

    // Simulating reading commands from console
    consoleProcessor.saveCommand("loadmap");
    consoleProcessor.saveCommand("invalidcommand");
    consoleProcessor.saveCommand("addplayer");

    std::cout << "\nReading commands from file...\n";
    try {
        FileCommandProcessorAdapter fileProcessor("commands.txt");
        fileProcessor.attach(&logObserver);

        fileProcessor.processFileCommands();  // Reads first command from file
        fileProcessor.processFileCommands();  // Reads second command from file
        fileProcessor.processFileCommands();  // Reads third command from file
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
}
