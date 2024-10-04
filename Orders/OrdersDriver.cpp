#include <iostream>
#include "Orders.h"

void testOrdersLists() {
    OrdersList ordersList;
    std::cout << "Orders List created." << std::endl;

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
