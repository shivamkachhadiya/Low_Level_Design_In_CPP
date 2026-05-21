//
// Created by shiva on 21-05-2026.
//
#pragma once
#include <vector>
#include <iostream>
#include "../models/Order.h"
#ifndef LOW_LEVEL_DESIGN_CPP_ORDERMANAGER_H
#define LOW_LEVEL_DESIGN_CPP_ORDERMANAGER_H

#endif //LOW_LEVEL_DESIGN_CPP_ORDERMANAGER_H

class OrderManager {
private:
    // (1) Same Singleton pattern as RestaurantManager
    OrderManager() {}
    OrderManager(const OrderManager&) = delete;
    OrderManager& operator=(const OrderManager&) = delete;

    static OrderManager* instance;

    // (2) storing ORDER POINTERS — not values!
    std::vector<Order*> orders;

public:
    static OrderManager* getInstance() {
        if (instance == nullptr) {
            instance = new OrderManager();
        }
        return instance;
    }

    // (3) Add order
    void addOrder(Order* order) {
        orders.push_back(order);
    }

    // (4) List all orders
    void listOrders() const {
        if (orders.empty()) {
            std::cout << "No orders yet!" << std::endl;
            return;
        }
        for (const auto& order : orders) {
            std::cout << "Order ID: " << order->getId()        // (5) arrow operator
                      << " | Type: "  << order->getType()
                      << " | User: "  << order->getUser().getName()
                      << std::endl;
        }
    }

    const std::vector<Order*>& getOrders() const { return orders; }
};

// (6) static member definition
OrderManager* OrderManager::instance = nullptr;