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
#include <map>
#include <sstream>
#include <algorithm>
#include <iterator>

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
CommandProcessor::CommandProcessor() {
    tournamentMode = false;
}

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
    if(tournamentMode){
        std::cout << "\033[31m" <<commands.front()->getCommandText() << "\033[0m" << std::endl;
        Command* toReturn = commands.front();
        commands.erase(commands.begin());
        return toReturn;
    } else {
        readCommand();
        return commands.back();
    }

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


void CommandProcessor::parseTournamentCommand(const string input) {
    tournamentMode = true;
    vector<Command*> blank;
    commands = blank;
    vector<string> maps;
    vector<string> players;
    int numGames = 0, numRounds = 0;

    std::istringstream iss(input);
    string token;
    string currentFlag;
    string buffer;

    std::map<string, int> strategyMap = {
            {"human", 1},
            {"cheater", 2},
            {"aggressive", 3},
            {"neutral", 4},
            {"benevolent", 5}
    };

    // Check and skip the "tournament" token if it exists
    iss >> token;
    if (token == "tournament") {
        std::cout << "Skipping 'tournament' token." << std::endl;
    } else {
        iss.clear();
        iss.str(input);
        iss.seekg(0);
    }

    while (iss >> token) {
        if (token == "-M" || token == "-P" || token == "-G" || token == "-D") {
            if (currentFlag == "-M" && !buffer.empty()) {
                std::istringstream mapStream(buffer);
                string map;
                while (std::getline(mapStream, map, ',')) {
                    map.erase(map.begin(), std::find_if(map.begin(), map.end(), [](unsigned char ch) { return !std::isspace(ch); }));
                    map.erase(std::find_if(map.rbegin(), map.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), map.end());
                    maps.push_back(map);
                }
                if (maps.size() < 1 || maps.size() > 5) {
                    std::cerr << "Error: Invalid number of maps (must be between 1 and 5).\n";
                    return;
                }
                buffer.clear();
            }
            currentFlag = token;
        } else if (currentFlag == "-M") {
            if (!buffer.empty()) buffer += " ";
            buffer += token;
        } else if (currentFlag == "-P") {
            players.push_back(token);
            if (players.size() > 4) {
                std::cerr << "Error: Invalid number of players (must be between 2 and 4).\n";
                return;
            }
        }
        else if (currentFlag == "-G") {
            try {
                numGames = std::stoi(token);
                if (numGames < 1 || numGames > 5) throw std::out_of_range("Invalid number of games");
//                saveCommand("setgames " + std::to_string(numGames));  // Save the number of games
            } catch (...) {
                std::cerr << "Error: Invalid number of games (must be 1-5).\n";
                return;
            }
        } else if (currentFlag == "-D") {
            try {
                numRounds = std::stoi(token);
                if (numRounds < 10 || numRounds > 50) throw std::out_of_range("Invalid number of rounds");
//                saveCommand("setrounds " + std::to_string(numRounds));  // Save the number of rounds
            } catch (...) {
                std::cerr << "Error: Invalid number of rounds (must be 10-50).\n";
                return;
            }
        } else {
            std::cerr << "Error: Unexpected token '" << token << "'\n";
            return;
        }
    }

    if (currentFlag == "-M" && !buffer.empty()) {
        std::istringstream mapStream(buffer);
        string map;
        while (std::getline(mapStream, map, ',')) {
            map.erase(map.begin(), std::find_if(map.begin(), map.end(), [](unsigned char ch) { return !std::isspace(ch); }));
            map.erase(std::find_if(map.rbegin(), map.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), map.end());
            maps.push_back(map);
        }
    }

    if (maps.empty()) {
        std::cerr << "Error: No maps provided.\n";
        return;
    }
    if (players.size() < 2 || players.size() > 4) {
        std::cerr << "Error: Invalid number of player strategies (must be 2-4).\n";
        return;
    }

    saveCommand(std::to_string(maps.size()));
    saveCommand(std::to_string(numGames));
    saveCommand(std::to_string(numRounds));

    for(int j = 0; j<numGames; j++){
        for (const auto& map : maps) {
            saveCommand("loadmap " + map);
            saveCommand("validatemap");

            for (int i = 0; i<players.size(); i++){
                string strategy = players.at(i);
                saveCommand("addplayer P"+ std::to_string(i + 1));
                saveCommand(std::to_string(strategyMap[players[i]]));
            }
            saveCommand("Y");
            saveCommand("gamestart");
        }
    }

    std::cout << "Tournament commands parsed and saved.\n";
}


/*
string CommandProcessor::nextGameState(const string& currentState, const string& commandText) {
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

bool CommandProcessor::inTournamentMode() {
    return tournamentMode;
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



