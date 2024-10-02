#include <iostream>
#include "Orders.h"
using namespace std;

void testOrdersLists() {
    // Creating an OrdersList object
    OrdersList ordersList;
    cout << "Orders List created." << endl;

    // Adding different types of orders
    cout << "Adding Deploy and Advance orders." << std::endl;
    ordersList.addOrder(new DeployOrder());
    ordersList.addOrder(new AdvanceOrder());

    // Displaying the list of orders
    cout << "Initial Orders List: " << std::endl;
    cout << ordersList;

    // Moving orders in the list
    cout << "Moving orders in the list..." << std::endl;
    ordersList.move(0, 1);
    cout << "Orders List after moving: " << std::endl;
    cout << ordersList;

    // Executing and removing orders
    cout << "Executing and removing orders..." << std::endl;
    ordersList.remove(0); // Removes first order
    ordersList.remove(0); // Removes second order

    // Final state of the OrdersList
    cout << "Final Orders List (should be empty): " << std::endl;
    cout << ordersList;
}

int main() {
    // Call the test function for Orders List
    testOrdersLists();
    return 0;
}
