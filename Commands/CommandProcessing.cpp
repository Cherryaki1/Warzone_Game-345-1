/**
 * @file CommandProcessing.cpp
 * @brief This file contains the class and function implementations for Command, CommandProcessor, and FileCommandProcessorAdapter.
 * 
 * This file is part of the Warzone Game Team Project for COMP 345 - D (Advanced Program Design, C++).
 * It includes the implementation of the Command class, which represents commands in the game,
 * as well as the CommandProcessor and FileCommandProcessorAdapter classes for processing commands.
 * 
 * Team Members (Team 36):
 * - Amir Vala Khalilzadeh (40253211)
 * - Abdulah Ghulam Ali (40281857)
 * - Arturo Sanchez Escobar (40283236)
 * - Gregory Lajoie (40276231)
 * - Botao Yang (40213554)
 */

#include "CommandProcessing.h"
#include <sstream>
#include <algorithm>
#include <iterator>
#include <map>


vector<string> split(string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;
    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }
    res.push_back(s.substr(pos_start));
    return res;
}


//**************************COMMAND**************************

/**
 * @brief Constructs a Command object with the given command text.
 * @param commandText The text of the command.
 */
Command::Command(const string& commandText)
    : commandText(new string(commandText)), effect(new string("")) {}

/**
 * @brief Destructor for the Command class.
 */
Command::~Command() {
    delete commandText;  // Clean up allocated memory for commandText
    delete effect;       // Clean up allocated memory for effect
}

/**
 * @brief Saves the effect of the command.
 * @param effectText The effect text to save.
 */
void Command::saveEffect(const string& effectText) {
    *effect = effectText;  // Set the effect value
    notify(this);          // Notify observers after saving the effect
}

/**
 * @brief Gets the text of the command.
 * @return The text of the command.
 */
string Command::getCommandText() const {
    return *commandText;  // Dereference to access the actual string value
}

/**
 * @brief Converts the command to a loggable string.
 * @return The loggable string representation of the command.
 */
string Command::stringToLog() {
    return "Command: " + *commandText + "\nCommand's Effect: " + *effect;
}

/**
 * @brief Stream insertion operator for displaying a command.
 * @param os The output stream.
 * @param cmd The command to display.
 * @return The output stream.
 */
std::ostream& operator<<(std::ostream& os, const Command& cmd) {
    os << "Command: " << *cmd.commandText;
    if (cmd.effect) os << ", Effect: " << *cmd.effect;
    return os;
}

//**************************COMMAND PROCESSOR**************************

/**
 * @brief Constructs a CommandProcessor object.
 */
CommandProcessor::CommandProcessor() {}

/**
 * @brief Destructor for the CommandProcessor class.
 */
CommandProcessor::~CommandProcessor() {
    for (Command* cmd : commands) delete cmd;
}

/**
 * @brief Reads a command from the input.
 */
void CommandProcessor::readCommand() {
    string commandText;
    std::cout << "Enter command: ";
    std::getline(std::cin, commandText);
    saveCommand(commandText);
}

/**
 * @brief Saves a command with the given text.
 * @param commandText The text of the command to save.
 */
void CommandProcessor::saveCommand(const string& commandText) {
    Command* command = new Command(commandText);
    commands.push_back(command);
    validate(command);
    notify(this);
}

/**
 * @brief Gets the list of commands.
 * @return A pointer to the vector of commands.
 */
vector<Command*>* CommandProcessor::getCommands() {
    return &commands;
}

/**
 * @brief Gets the most recent command.
 * @return A pointer to the most recent command.
 */
Command* CommandProcessor::getCommand() {
    readCommand();
    return commands.back();
}

/**
 * @brief Validates a command based on the current state.
 * @param command The command to validate.
 * @param state The current state of the game.
 * @return True if the command is valid, false otherwise.
 */
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
    } else if (commandText.substr(0,commandText.find(' ')) == "tournament" && state == "start") {
        isValid = true;
        command->saveEffect("Sets tournament mode");
    }else {
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
//        std::cout << "Loaded map at " << commandText << std::endl;
        isValid = true;

        command->saveEffect("Loads a map");
    } else if (commandText == "validatemap") {
        isValid = true;
//        std::cout << "Validated Map" << std::endl;
        command->saveEffect("Validates a map");
    } else if (commandText.substr(0,9) == "addplayer") {
//        string playerName = commandText.substr(11);
//        std::cout << "Added Player" << std::endl;
        isValid = true;
        command->saveEffect("Adds a player");
    } else if (commandText == "gamestart") {
//        std::cout << "Game Start" << std::endl;
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
    if (commandText == "gamestart") return "playersadded";
    return currentState;
}*/

/**
 * @brief Converts the CommandProcessor to a loggable string.
 * @return The loggable string representation of the CommandProcessor.
 */
string CommandProcessor::stringToLog() {
    return commands.back()->stringToLog();
}

void CommandProcessor::parseTournamentCommand(const std::string& input) {
    // Initialize parsing variables
    std::vector<std::string> maps;
    std::vector<std::string> players;
    int numGames = 0, numRounds = 0;

    // Tokenize the input string
    std::istringstream iss(input);
    std::string token;
    std::string currentFlag;

    // Check and skip the "tournament" token if it exists
    iss >> token;
    if (token == "tournament") {
        std::cout << "Skipping 'tournament' token." << std::endl;
    } else {
        // Put the token back into the stream if it's not "tournament"
        iss.clear();
        iss.str(input);
        iss.seekg(0);
    }

    // Process the remaining tokens
    while (iss >> token) {
        if (token == "-M" || token == "-P" || token == "-G" || token == "-D") {
            // Update the current flag
            currentFlag = token;
        } else if (currentFlag == "-M") {
            // Split maps by commas
            std::istringstream mapStream(token);
            std::string map;
            while (std::getline(mapStream, map, ',')) {
                // Trim leading and trailing spaces
                map.erase(map.begin(), std::find_if(map.begin(), map.end(), [](unsigned char ch) { return !std::isspace(ch); }));
                map.erase(std::find_if(map.rbegin(), map.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), map.end());
                maps.push_back(map);
            }
        } else if (currentFlag == "-P") {
            // Add player strategies (space-separated)
            players.push_back(token);
        } else if (currentFlag == "-G") {
            // Number of games
            try {
                numGames = std::stoi(token);
                if (numGames < 1 || numGames > 5) throw std::out_of_range("Invalid number of games");
            } catch (...) {
                std::cerr << "Error: Invalid number of games (must be 1-5).\n";
                return;
            }
        } else if (currentFlag == "-D") {
            // Number of rounds
            try {
                numRounds = std::stoi(token);
                if (numRounds < 10 || numRounds > 50) throw std::out_of_range("Invalid number of rounds");
            } catch (...) {
                std::cerr << "Error: Invalid number of rounds (must be 10-50).\n";
                return;
            }
        } else {
            std::cerr << "Error: Unexpected token '" << token << "'\n";
            return;
        }
    }

    // Validate parsed data
    if (maps.empty()) {
        std::cerr << "Error: No maps provided.\n";
        return;
    }
    if (players.size() < 2 || players.size() > 4) {
        std::cerr << "Error: Invalid number of player strategies (must be 2-4).\n";
        return;
    }

    // Save commands for each game
    for (int game = 1; game <= numGames; ++game) {
        for (const std::string& map : maps) {
            saveCommand("loadmap " + map);
            saveCommand("validatemap");

            // Add players with their strategies
            for (const std::string& strategy : players) {
                saveCommand("addplayer " + strategy);
            }

            // End player addition
            saveCommand("Y");

            // Start the game
            saveCommand("gamestart");
        }
    }

    std::cout << "Tournament commands parsed and saved.\n";
}


/**
 * @brief Stream insertion operator for displaying a CommandProcessor.
 * @param os The output stream.
 * @param cp The CommandProcessor to display.
 * @return The output stream.
 */
std::ostream& operator<<(std::ostream& os, const CommandProcessor& cp) {
    os << "CommandProcessor with " << cp.commands.size() << " commands:\n";
    for (const Command* cmd : cp.commands) {
        os << *cmd << "\n";
    }
    return os;
}

//**************************FILE COMMAND PROCESSOR ADAPTER**************************

/**
 * @brief Constructs a FileCommandProcessorAdapter object with the given filename.
 * @param filename The name of the file to read commands from.
 */
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const string& filename) {
    fileStream.open(filename);
    if (!fileStream.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
}

/**
 * @brief Destructor for the FileCommandProcessorAdapter class.
 */
FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
    if (fileStream.is_open()) {
        fileStream.close();
    }
}

/**
 * @brief Reads a command from the file.
 */
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

/**
 * @brief Stream insertion operator for displaying a FileCommandProcessorAdapter.
 * @param os The output stream.
 * @param fcp The FileCommandProcessorAdapter to display.
 * @return The output stream.
 */
std::ostream& operator<<(std::ostream& os, const FileCommandProcessorAdapter& fcp) {
    os << "FileCommandProcessorAdapter reading from file:\n";
    os << static_cast<const CommandProcessor&>(fcp);  // Reuse base class operator<<
    return os;
}



