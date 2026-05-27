//
// Created by shiva on 19-05-2026.
//
// main.cpp
#include <iostream>
#include <string>
#include "include/models/User.h"
#include "include/models/Restaurant.h"
#include "include/models/MenuItem.h"
#include "include/models/Order.h"
#include "include/patterns/CreditCard.h"
#include "include/patterns/NetBanking.h"
#include "include/patterns/UPI.h"
#include "include/patterns/NowOrderFactory.h"
#include "include/patterns/ScheduleOrderFactory.h"
#include "include/services/RestaurantManager.h"
#include "include/services/OrderManager.h"
#include "include/services/NotificationService.h"
// (1) Tomato — main orchestration class
class Tomato {
public:
    void run() {
        std::cout << "Welcome to Tomato!" << std::endl;

        // (2) Setup restaurants using Singleton
        setupRestaurants();

        // (3) Create a user
        User user(1, "SHIVAM", "MUMBAI");



        // (4) Search restaurants by location
        std::cout << "\nRestaurants in Ahmedabad:" << std::endl;
        auto restaurants = RestaurantManager::getInstance()
                               ->searchByLoc("Ahmedabad");

        if (restaurants.empty()) {
            std::cout << "No restaurants found!" << std::endl;
            return;
        }

        // (5) Show restaurants
        for (int i = 0; i < restaurants.size(); i++) {
            std::cout << i << ". " << restaurants[i].getName() << std::endl;
        }

        // (6) User selects restaurant
        int choice;
        std::cout << "Select restaurant: ";
        std::cin >> choice;
        Restaurant& selectedRest = restaurants[choice];

        // (7) Show menu
        std::cout << "\nMenu:" << std::endl;
        auto menu = selectedRest.getMenu();
        for (int i = 0; i < menu.size(); i++) {
            std::cout << i << ". "
                      << menu[i].getName()
                      << " - Rs." << menu[i].getPrice()
                      << std::endl;
        }

        // (8) Add items to cart
        user.getCart().setRestaurant(&selectedRest);
        int itemChoice;
        std::cout << "Select item (0-" << menu.size()-1 << "): ";
        std::cin >> itemChoice;
        user.getCart().addToCart(menu[itemChoice]);

        // (9) Choose factory — Now or Scheduled
        std::cout << "\n1. Order Now" << std::endl;
        std::cout << "2. Schedule Order" << std::endl;
        std::cout << "Choose: ";
        int orderType;
        std::cin >> orderType;

        // (10) Create factory based on choice
        IOrderFactory* factory = nullptr;
        if (orderType == 1) {
            factory = new NowOrderFactory();
        } else {
            std::string time;
            std::cout << "Enter schedule time: ";
            std::cin >> time;
            factory = new ScheduleOrderFactory(time);
        }

        // (11) Create order using factory
        Order* order = factory->createOrder(1, user, &selectedRest);
        if (order == nullptr) {
            std::cout << "Invalid order type!" << std::endl;
            return;
        }

        // (12) Add cart items to order
        for (const auto& item : user.getCart().getItems()) {
            order->addItem(item);
        }

        // (13) Choose payment strategy
        std::cout << "\n1. Credit Card" << std::endl;
        std::cout << "2. Net Banking" << std::endl;
        std::cout << "3. UPI" << std::endl;
        std::cout << "Choose payment: ";
        int payChoice;
        std::cin >> payChoice;

        // (14) Set payment strategy
        IPaymentStrategy* payment = nullptr;
        if (payChoice == 1)      payment = new CreditCard();
        else if (payChoice == 2) payment = new NetBanking();
        else                     payment = new UPI();

        order->setPaymentStrategy(payment);

        // (15) Process payment
        order->pay();

        // (16) Save order in OrderManager singleton
        OrderManager::getInstance()->addOrder(order);

        // (17) Notify user
        NotificationService notification(order);
        notification.notifyUser();

        // (18) List all orders
        std::cout << "\nAll Orders:" << std::endl;
        OrderManager::getInstance()->listOrders();

        // (19) cleanup
        delete factory;
        delete payment;
    }

private:
    void setupRestaurants() {
        // (20) Create restaurants
        Restaurant r1(1, "Pizza Hut", "Ahmedabad");
        r1.addMenuItem(MenuItem("P001", "Margherita", 299));
        r1.addMenuItem(MenuItem("P002", "Pepperoni",  499));

        Restaurant r2(2, "Burger King", "Ahmedabad");
        r2.addMenuItem(MenuItem("B001", "Whopper",    349));
        r2.addMenuItem(MenuItem("B002", "Veg Burger", 199));

        // (21) Add to singleton
        RestaurantManager::getInstance()->addRestaurant(r1);
        RestaurantManager::getInstance()->addRestaurant(r2);
    }
};

// (22) Entry point
int main() {
    Tomato app;
    app.run();
    return 0;
}