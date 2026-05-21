//
// Created by shiva on 21-05-2026.
//
#pragma once

#ifndef LOW_LEVEL_DESIGN_CPP_SCHEDULEORDERFACTORY_H
#define LOW_LEVEL_DESIGN_CPP_SCHEDULEORDERFACTORY_H

#endif //LOW_LEVEL_DESIGN_CPP_SCHEDULEORDERFACTORY_H
#include "IOrderFactory.h"
#include "../models/DeliveryOrder.h"
#include "../models/PickupOrder.h"

class ScheduleOrderFactory:public IOrderFactory {
private:
    std::string scheduleTime;
public:
    ScheduleOrderFactory(std::string time):scheduleTime(time){}
    Order* createOrder(int id, User user, Restaurant *rest) override {
        std::string type;
        std::string address;
        std::cout<<"Scheduled Order For : "<<scheduleTime<<std::endl;
        std::cout << "Enter order type (DELIVERY/PICKUP): ";
        std::cin >> type;
        if (type == "DELIVERY") {
            std::cout << "Enter delivery address: ";
            std::cin >> address;
            return new DeliveryOrder(id, user, rest, address);
        }
        else if (type == "PICKUP") {
            std::cout << "Enter pickup address: ";
            std::cin >> address;
            return new PickupOrder(id, user, rest, address);
        }

        return nullptr;
    }

    // (5) getter for scheduleTime
    const std::string& getScheduleTime() const { return scheduleTime; }
};