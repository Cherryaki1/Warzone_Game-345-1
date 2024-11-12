#include "LoggingObserver.h"
#include "Orders.h"
#include "Player.h"
#include "GameEngine.h"
#include "Commands/CommandProcessing.h"
#include "fstream"

void testLoggingObserver(){
    //demonstrates that (1) The
    //Command, CommandProcessor (see Part 1), Order, OrderList, and
    // GameEngine classes are all a subclass of the
    //Subject and ILoggable classes

    std::ofstream file; //Clear the game log file
    file.open("../gamelog.txt", std::ios::trunc);
    file.flush();
    file.close();

    auto player1 = new Player("John");
    auto player2 = new Player("Bob");

    LogObserver observer; //The observer for this function

    // Show that Order and OrderList are subclasses of Subject and ILoggable
    OrdersList ordersList;
    ordersList.attach(&observer);

    auto testTerritory1 = new Territory("territory1", player1->getPlayerName(), "0", 0);
    auto testTerritory2 = new Territory("territory2", player2->getPlayerName(), "0", 0);

    auto one = new DeployOrder(player1, testTerritory1, 1);
    auto two = new BombOrder(player1, testTerritory2);
    auto three = new NegotiateOrder(player1, player2);

    ordersList.addOrder(one); //This will create log entries
    ordersList.addOrder(two);
    ordersList.addOrder(three);

    for(Order *order : ordersList.getOrders()){
        order->attach(&observer);
        order->execute(); //This will create log entries
    }

    auto processor = new CommandProcessor();
    processor->attach(&observer);
    while (true){
        std::cout << "Enter any command for the log - invalid commands will have no effects\n Write STOP to stop logging commands" <<std::endl;
        Command *command = processor->getCommand(); //This will create log entries. Note that getCommand calls Command::saveEffect() and CommandProcessor::saveCommand()
        if (command->getCommandText() == "stop") break;
    }
    GameEngine *engine = new GameEngine();
    engine->attach(&observer);
    engine->startUpPhase(); //This calls the GameEngine::transition() after every state.
}