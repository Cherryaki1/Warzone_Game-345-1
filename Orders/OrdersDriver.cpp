#include <iostream>
#include "Orders.h"
#include "Player.h"
#include "fstream"




void testOrderExecution(){
//    (1) each order is validated before being executed according to the above descriptions;
    auto player1 = new Player("John");
    auto player2 = new Player("Bob");
    auto testTerritory1 = new Territory("territory1", player1->getPlayerName(), "0", 10);
    auto testTerritory2 = new Territory("territory2", player2->getPlayerName(), "0", 20);

    //3 valid orders
    auto one = new DeployOrder(player1, testTerritory1, 1);
    auto two = new BombOrder(player1, testTerritory2);
    auto three = new NegotiateOrder(player1, player2);

    //1 invalid order
    auto four = new DeployOrder(player1, testTerritory2, 1);

    std::cout<<"Three valid orders being executed"<<std::endl;
    one->execute();
    two->execute();
    three->execute();
    std::cout<<"One invalid order being executed"<<std::endl;
    four->execute();


//    (2) ownership of a territory is transferred to the attacking player if a territory is conquered as a result of an advance order;
//    (3) one card is given to a player if they conquer at least one territory in a turn (not more than one card per turn);
//    (4) the negotiate order prevents attacks between the two players involved;
//    (5) the blockade order transfers ownership to the Neutral player;
//    (6) all the orders described above can be issued by a player and executed by the game engine
    delete player1;
    delete player2;
    delete testTerritory2;
    delete testTerritory1;
}




void testOrdersLists() {
    OrdersList ordersList;
    std::cout << "Orders List created." << std::endl;
    LogObserver observer;
    ordersList.attach(&observer);
    // Adding 8 orders
    ordersList.addOrder(new DeployOrder());
    ordersList.addOrder(new BombOrder());
    ordersList.addOrder(new AirliftOrder());
    ordersList.addOrder(new AdvanceOrder());
    ordersList.addOrder(new BlockadeOrder());
    ordersList.addOrder(new NegotiateOrder());
    ordersList.addOrder(new DeployOrder());
    ordersList.addOrder(new BombOrder());



    std::cout << "Initial Orders List: " << std::endl;
    std::cout << ordersList;

    // Moving some orders around
    std::cout << "\nSwapping orders in the list..." << std::endl;
    ordersList.move(0, 5);  // Move the first order to position 5
    ordersList.move(7, 2);  // Move the last order to position 2
    ordersList.move(3, 0);  // Move an order from the middle to the start
    std::cout << "Orders List after moving: " << std::endl;
    std::cout << ordersList;

    // Removing 3 orders from the list
    std::cout << "\nRemoving 3 orders from the list..." << std::endl;
    ordersList.remove(1);  // Remove the order at position 1
    ordersList.remove(4);  // Remove the order at position 4
    ordersList.remove(0);  // Remove the order at position 0
    std::cout << "Orders List after removing 3 orders: " << std::endl;
    std::cout << ordersList;

    // Executing remaining orders
    std::cout << "\nExecuting remaining orders..." << std::endl;
    for (auto it = ordersList.getOrders().begin(); it != ordersList.getOrders().end(); ++it) {
        (*it)->execute();
    }
  
    std::cout << "\nFinal Orders List (should show executed orders): " << std::endl;
    std::cout << ordersList;
}
