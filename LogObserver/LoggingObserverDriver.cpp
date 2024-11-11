#include "LoggingObserver.h"
#include "Orders.h"
#include "Player.h"
#include "fstream";

void testLoggingObserver(){
    //demonstrates that (1) The
    //Command, CommandProcessor (see Part 1), Order, OrderList, and
    // GameEngine classes are all a subclass of the
    //Subject and ILoggable classes

    std::ofstream file; //Clear the game log file
    file.open("../gamelog.txt", std::ios::trunc);
    file.flush();
    file.close();



    auto john = new Player("John");
    LogObserver observer; //The observer for this function

    // Show that Order and OrderList are subclasses of Subject and ILoggable
    OrdersList ordersList;
    ordersList.attach(&observer);

    auto one = new DeployOrder();
    auto two = new BombOrder();
    auto three = new AirliftOrder();

    one->attach(&observer);
    two->attach(&observer);
    three->attach(&observer);

    ordersList.addOrder(one);
    ordersList.addOrder(two);
    ordersList.addOrder(three);

    for(Order *order : ordersList.getOrders()){
        order->execute();
    }
};