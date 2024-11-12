//
// Created by gregl on 11/10/2024.
//
#include "CommandProcessing.h"
#include "GameEngine.h"
void testCommandProcessor() {
    LogObserver logObserver;
    CommandProcessor consoleProcessor;
    consoleProcessor.attach(&logObserver);

    string choice;
    std::cout << "Choose between accepting the commands from the console (console) or from a file (file)" << std::endl;
    std::cout << "Enter choice:";
    std::getline(std::cin, choice);

    GameEngine gm;
    if (choice == "console") {
        while(consoleProcessor.getCommands()->empty() || consoleProcessor.getCommands()->back()->getCommandText() != "quit") {
            consoleProcessor.processCommands();
        }
    } else if (choice == "file") {
        try {
            string fileName;
            std::cout << "Write the File Name:";
            std::cin >> fileName;
            FileCommandProcessorAdapter fileProcessor("../" + fileName);
            fileProcessor.attach(&logObserver);

            fileProcessor.processCommands();
            fileProcessor.processCommands();
            fileProcessor.processCommands();

            // Begin the StartUpPhase
            //testStartUpPhase(fileName);

        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
        }
    } else {
        std::cout << "Invalid choice" << std::endl;
    }
}
