//
// Created by shiva on 21-05-2026.
//
#pragma once
#include <iostream>
#include "../models/Order.h"
#ifndef LOW_LEVEL_DESIGN_CPP_NOTIFICATIONSERVICE_H
#define LOW_LEVEL_DESIGN_CPP_NOTIFICATIONSERVICE_H

#endif //LOW_LEVEL_DESIGN_CPP_NOTIFICATIONSERVICE_H

class NotificationService {
private:
    Order* order;           // (1) pointer to order — not owned by us

public:
    // (2) Constructor — takes order pointer
    NotificationService(Order* o) : order(o) {}

    // (3) Notify user about their order
    void notifyUser() const {
        if (order == nullptr) {
            std::cout << "No order to notify!" << std::endl;
            return;
        }

        std::cout << "------------ NOTIFICATION ------------" << std::endl;
        std::cout << "Hey " << order->getUser().getName() << "!" << std::endl;
        std::cout << "Your " << order->getType() << " order #"
                  << order->getId() << " has been placed!" << std::endl;
        std::cout << "Restaurant: "
                  << order->getRestaurant()->getName() << std::endl;
        std::cout << "Total Items: "
                  << order->getItems().size() << std::endl;
        std::cout << "--------------------------------------" << std::endl;
    }
};